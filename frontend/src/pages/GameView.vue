<template>
  <n-layout-content>
    <div
      class="w:80% height:700px margin:2em|auto grid grid-template-cols:auto|1fr gap:2em"
    >
      <div
        :class="`rel border:.5em|solid|${primaryColor} p:.5em h:calc(8*${boardCellWidthPx}+1em+1em) w:calc(8*${boardCellWidthPx}+1em+1em)`"
      >
        <div :class="`grid grid-template-rows:repeat(8,${boardCellWidth}px)`">
          <div
            v-for="index in eightElementArray"
            :key="index"
            :class="`grid grid-template-cols:repeat(8,${boardCellWidth}px)`"
          >
            <div
              v-for="i in eightElementArray"
              :key="i"
              :class="`rel flex justify:center items:center bg:${
                (index + i) % 2 == 1 ? primaryColor : secondaryColor
              } w:${boardCellWidth}px h:${boardCellWidth}px ${
                currClickPosi == getPositionString(index, i)
                  ? 'border:4px|solid|white'
                  : ''
              }`"
              @click="ElementClick(index, i)"
            >
              <div
                v-if="i == 0"
                :class="`posi-hint abs font:16px top:0px left:4px font-weight:500 f:${
                  (index + i) % 2 == 0 ? primaryColor : secondaryColor
                }`"
              >
                {{ 8 - index }}
              </div>
              <div
                v-if="index == 7"
                :class="`posi-hint abs font:16px bottom:0px right:4px font-weight:500 f:${
                  (index + i) % 2 == 0 ? primaryColor : secondaryColor
                }`"
              >
                {{ engPositions[i] }}
              </div>
              <div
                v-if="validPositions.includes(getPositionString(index, i))"
                :class="`bg:#cecece margin:auto|auto h:${
                  boardCellWidth / 3
                } w:${boardCellWidth / 3} border-radius:${boardCellWidth}`"
              ></div>
            </div>
          </div>
        </div>

        <ChessElement
          v-for="chess in board"
          :key="chess.position"
          :type="chess.type"
          :color="chess.color"
          :position="chess.position"
          :board-cell-width="boardCellWidth"
          @chess-click="ChessClick"
        />
      </div>
      <div :class="`bg:${secondaryColor} p:1em`">
        <div>
          <n-tabs
            ref="playerInst"
            v-model:value="currPlayer"
            size="large"
            animated
            justify-content="space-evenly"
            @before-leave="handleBeforeLeave"
          >
            <n-tab
              v-for="player in Object.values(Player)"
              :key="player"
              :label="player"
              :name="player"
            />
          </n-tabs>

          <n-button type="primary" class="w:100% mt:2em" @click="surrender">
            投降
          </n-button>
        </div>
      </div>
    </div>
  </n-layout-content>
</template>

<script setup lang="ts">
import anime from 'animejs';
import type { TabsInst } from 'naive-ui';
import { NButton, NLayoutContent, NTab, NTabs, useDialog } from 'naive-ui';
import { computed, nextTick, ref } from 'vue';

import blackChessSource from '@/assets/black.mp3';
import whiteChessSource from '@/assets/white.mp3';
import useTheme from '@/common/useTheme';
import type { ReceiveMsg } from '@/common/useWebSocket';
import {
  ReceiveMsgType,
  SendMsgType,
  useWebSocket,
} from '@/common/useWebSocket';
import ChessElement from '@/components/ChessElement.vue';
import router from '@/router';

const { primaryColor, secondaryColor } = useTheme();
const boardCellWidth = ref(85);
const boardCellWidthPx = computed(() => `${boardCellWidth.value}px`);
const engPositions = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'];
const eightElementArray = [...Array.from({ length: 8 }).keys()].map(
  (_, i) => i
);
const canPlay = ref(false);
const dialog = useDialog();
const currClickPosi = ref<string | null>(null);
const validPositions = ref<string[]>([]);

//#region Loading animation
nextTick(() => {
  anime
    .timeline()
    .add({
      // Game board loading animation
      targets: '.rel.flex',
      scale: [
        { value: 0.2, easing: 'easeInOutQuad', duration: 300 },
        { value: 1, easing: 'easeInOutQuad', duration: 500 },
      ],
      delay: anime.stagger(50, { grid: [8, 8], from: 'first' }),
    })
    .add({
      // Chess loading animation
      targets: 'i.abs',
      opacity: [0, 1],
      easing: 'linear',
      duration: 300,
      delay: function (el, i, l) {
        const half = l / 2;
        return i < half ? i * 50 : (l - i - 1) * 50;
      },
    })
    .add({
      // Position hint loading animation
      targets: '.posi-hint',
      opacity: [0, 1],
      easing: 'linear',
      duration: 300,
    });
});

const animationFinished = async () => {
  const totalTime = 50 * 64 - 750;
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(true);
    }, totalTime);
  });
};
//#endregion

//#region WebSocket
const onMsg = (e: MessageEvent) => {
  const { data } = e;
  const msg = JSON.parse(data) as ReceiveMsg;

  switch (msg.type) {
    case ReceiveMsgType.Move:
      const { from, to } = msg;
      const chess = board.value.find((chess) => chess.position === from);
      if (!chess) return;
      board.value.find((chess) => chess.position === from)!.position = to!;
      currClickPosi.value = null;
      validPositions.value = [];
      switchPlayer();
      break;

    case ReceiveMsgType.FirstClick:
      currClickPosi.value = msg.position!;
      break;

    case ReceiveMsgType.Win:
      dialog.success({
        title: '遊戲結束',
        content: `${msg.player == 'White' ? '白方' : '黑方'}獲勝！`,
        positiveText: '在玩一局',
        negativeText: '回首頁',
        onPositiveClick: () => {
          location.reload();
        },
        onNegativeClick() {
          router.push('/');
        },
      });
      canPlay.value = false;
      break;

    case ReceiveMsgType.Surrender:
      dialog.success({
        title: '遊戲結束',
        content: `${msg.player == 'Black' ? '白方' : '黑方'}獲勝！`,
        positiveText: '在玩一局',
        negativeText: '回首頁',
        onPositiveClick: () => {
          location.reload();
        },
        onNegativeClick() {
          router.push('/');
        },
      });
      break;

    case ReceiveMsgType.ValidMoves:
      const { validMoves } = msg;
      validPositions.value =
        validMoves?.map((move) => `${engPositions[move.x]}${move.y + 1}`) ?? [];
      break;

    case ReceiveMsgType.Take:
      const { takeout } = msg;
      board.value = board.value.filter((chess) => chess.position !== takeout);
      break;

    case ReceiveMsgType.ProMotion:
      const { position } = msg;
      board.value[
        board.value.findIndex((chess) => chess.position === position)
      ].type = ChessType.Queen;
      break;
  }
};
const { openWs, sendMsg } = useWebSocket(onMsg);
//#endregion

//#region Chess
enum ChessType {
  Pawn,
  Rook,
  Knight,
  Bishop,
  Queen,
  King,
}
//#endregion

const ChessClick = (chessPos: string) => {
  if (!canPlay.value) return;
  if (whiteChessAudio.played.length == 0) whiteChessAudio.play();
  if (blackChessAudio.played.length == 0) blackChessAudio.play();

  const chess = board.value.find((chess) => chess.position === chessPos);
  if (!chess) return;
  sendMsg({ type: SendMsgType.Click, position: chessPos });
};

//#region Board
type Chess = {
  type: ChessType;
  color: 'black' | 'white';
  position: string;
};
const board = ref<Chess[]>([
  {
    type: ChessType.Rook,
    color: 'white',
    position: 'a1',
  },
  {
    type: ChessType.Knight,
    color: 'white',
    position: 'b1',
  },
  {
    type: ChessType.Bishop,
    color: 'white',
    position: 'c1',
  },
  {
    type: ChessType.Queen,
    color: 'white',
    position: 'd1',
  },
  {
    type: ChessType.King,
    color: 'white',
    position: 'e1',
  },
  {
    type: ChessType.Bishop,
    color: 'white',
    position: 'f1',
  },
  {
    type: ChessType.Knight,
    color: 'white',
    position: 'g1',
  },
  {
    type: ChessType.Rook,
    color: 'white',
    position: 'h1',
  },
  {
    type: ChessType.Pawn,
    color: 'white',
    position: 'a2',
  },
  {
    type: ChessType.Pawn,
    color: 'white',
    position: 'b2',
  },
  {
    type: ChessType.Pawn,
    color: 'white',
    position: 'c2',
  },
  {
    type: ChessType.Pawn,
    color: 'white',
    position: 'd2',
  },
  {
    type: ChessType.Pawn,
    color: 'white',
    position: 'e2',
  },
  {
    type: ChessType.Pawn,
    color: 'white',
    position: 'f2',
  },
  {
    type: ChessType.Pawn,
    color: 'white',
    position: 'g2',
  },
  {
    type: ChessType.Pawn,
    color: 'white',
    position: 'h2',
  },
  {
    type: ChessType.Pawn,
    color: 'black',
    position: 'a7',
  },
  {
    type: ChessType.Pawn,
    color: 'black',
    position: 'b7',
  },
  {
    type: ChessType.Pawn,
    color: 'black',
    position: 'c7',
  },
  {
    type: ChessType.Pawn,
    color: 'black',
    position: 'd7',
  },
  {
    type: ChessType.Pawn,
    color: 'black',
    position: 'e7',
  },
  {
    type: ChessType.Pawn,
    color: 'black',
    position: 'f7',
  },
  {
    type: ChessType.Pawn,
    color: 'black',
    position: 'g7',
  },
  {
    type: ChessType.Pawn,
    color: 'black',
    position: 'h7',
  },
  {
    type: ChessType.Rook,
    color: 'black',
    position: 'a8',
  },
  {
    type: ChessType.Knight,
    color: 'black',
    position: 'b8',
  },
  {
    type: ChessType.Bishop,
    color: 'black',
    position: 'c8',
  },
  {
    type: ChessType.Queen,
    color: 'black',
    position: 'd8',
  },
  {
    type: ChessType.King,
    color: 'black',
    position: 'e8',
  },
  {
    type: ChessType.Bishop,
    color: 'black',
    position: 'f8',
  },
  {
    type: ChessType.Knight,
    color: 'black',
    position: 'g8',
  },
  {
    type: ChessType.Rook,
    color: 'black',
    position: 'h8',
  },
]);
//#endregion

//#region Menu
enum Player {
  White = '白方',
  Black = '黑方',
}
const playerInst = ref<TabsInst | null>(null);
const currPlayer = ref<Player>(Player.White);
const handleBeforeLeave = () => {
  return false;
};

// Music
const blackChessAudio = new Audio(blackChessSource);
const whiteChessAudio = new Audio(whiteChessSource);
blackChessAudio.volume = 0;
whiteChessAudio.volume = 0.5;
blackChessAudio.loop = true;
whiteChessAudio.loop = true;

const switchPlayer = () => {
  currPlayer.value =
    currPlayer.value == Player.White ? Player.Black : Player.White;
  if (currPlayer.value == Player.White) {
    blackChessAudio.volume = 0;
    whiteChessAudio.volume = 0.5;
  } else {
    blackChessAudio.volume = 0.5;
    whiteChessAudio.volume = 0;
  }
  nextTick(() => playerInst.value?.syncBarPosition());
};

const surrender = () => {
  if (!canPlay.value) return;

  sendMsg({ type: SendMsgType.Surrender });
  canPlay.value = false;
};
//#endregion

const getPositionString = (row: number, col: number) => {
  return `${engPositions[col]}${8 - row}`;
};

const ElementClick = (row: number, col: number) => {
  if (!canPlay.value) return;

  const posi = getPositionString(row, col);
  sendMsg({ type: SendMsgType.Click, position: posi });
};

(async () => {
  await Promise.all([openWs(), animationFinished()]);
  canPlay.value = true;
  sendMsg({ type: SendMsgType.Init });
})();
</script>
