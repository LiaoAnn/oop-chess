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
              :class="`rel bg:${
                (index + i) % 2 == 1 ? primaryColor : secondaryColor
              } w:${boardCellWidth}px h:${boardCellWidth}px flex justify:center items:center`"
            >
              <div
                v-if="i == 0"
                :class="`abs font:16px top:0px left:4px f:${
                  (index + i) % 2 == 0 ? primaryColor : secondaryColor
                } font-weight:500`"
              >
                {{ 8 - index }}
              </div>
              <div
                v-if="index == 7"
                :class="`abs font:16px bottom:0px right:4px f:${
                  (index + i) % 2 == 0 ? primaryColor : secondaryColor
                } font-weight:500`"
              >
                {{ engPositions[i] }}
              </div>
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
      <div :class="`bg:${secondaryColor} p:1em`"></div>
    </div>
  </n-layout-content>
</template>

<script setup lang="ts">
import { NLayoutContent } from 'naive-ui';
import { computed, ref } from 'vue';

import useTheme from '@/common/useTheme';
import ChessElement from '@/components/ChessElement.vue';

const { primaryColor, secondaryColor } = useTheme();
const boardCellWidth = ref(85);
const boardCellWidthPx = computed(() => `${boardCellWidth.value}px`);
const engPositions = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'];
const eightElementArray = [...Array.from({ length: 8 }).keys()].map(
  (_, i) => i
);

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
  const chess = board.value.find((chess) => chess.position === chessPos);
  if (!chess) return;
  // Do something
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
</script>
