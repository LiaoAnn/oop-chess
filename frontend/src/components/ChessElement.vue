<template>
  <n-icon
    :class="`abs f:${color} bottom:${getChessBottomPos()} left:${getChessLeftPos()}`"
    :size="boardCellWidth * 0.8"
    @click="$emit('chess-click', position)"
  >
    <component :is="getChessIcon(type)" />
  </n-icon>
</template>

<script setup lang="ts">
import {
  ChessBishop,
  ChessKing,
  ChessKnight,
  ChessPawn,
  ChessQueen,
  ChessRook,
} from '@vicons/fa';
import { NIcon } from 'naive-ui';
import { defineEmits, toRefs } from 'vue';

defineEmits(['chess-click']);

enum ChessType {
  Pawn,
  Rook,
  Knight,
  Bishop,
  Queen,
  King,
}

//#region Props
interface ChessElementProps {
  type: ChessType;
  color: 'black' | 'white';
  boardCellWidth: number;
  position: string; // e.g. e4 c5
}
const props = withDefaults(defineProps<ChessElementProps>(), {
  color: 'black',
  boardCellWidth: 85,
  position: 'a1',
});
const { type, color, position, boardCellWidth } = toRefs(props);
//#endregion

function getChessIcon(type: ChessType) {
  switch (type) {
    case ChessType.Pawn:
      return ChessPawn;
    case ChessType.Rook:
      return ChessRook;
    case ChessType.Knight:
      return ChessKnight;
    case ChessType.Bishop:
      return ChessBishop;
    case ChessType.Queen:
      return ChessQueen;
    case ChessType.King:
      return ChessKing;
  }
}

function getChessBottomPos() {
  const y = position.value.split('').pop()!;
  const xIndex = '12345678'.indexOf(y);
  return `calc(${xIndex * boardCellWidth.value}px+16px)`;
}

function getChessLeftPos() {
  const x = position.value.split('').shift()!;
  const yIndex = 'abcdefgh'.indexOf(x);
  return `calc(${yIndex * boardCellWidth.value}px+16px)`;
}
</script>
