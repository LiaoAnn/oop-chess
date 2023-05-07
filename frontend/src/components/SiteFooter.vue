<template>
  <n-layout-footer>
    <div class="bg:#764e30 p:2em|0">
      <div class="w:60% margin:0|auto grid-cols:2 justify-content:center">
        <div class="f:white font:2em font-weight:500">
          <n-icon>
            <Chess />
          </n-icon>
          OOP Project 2 | Chess
        </div>
        <div>
          <div class="f:#d9a669 font-weight:400 font:1em">組員</div>

          <div class="flex">
            <div class="f:white font:1.5em p:4px">
              <n-icon>
                <ChessQueen />
              </n-icon>
              廖廷安
            </div>
            <div class="f:#d9a669 font:1.5em p:4px">| B11130237</div>
          </div>

          <div class="flex">
            <div class="f:white font:1.5em p:4px">
              <n-icon>
                <ChessKing />
              </n-icon>
              劉耀恩
            </div>
            <div class="f:#d9a669 font:1.5em p:4px">| B11115039</div>
          </div>

          <div class="flex">
            <div class="f:white font:1.5em p:4px">
              <n-icon>
                <ChessPawn />
              </n-icon>
              劉沛安
            </div>
            <div class="f:#d9a669 font:1.5em p:4px">| B11115034</div>
          </div>

          <div class="flex">
            <div class="f:white font:1.5em p:4px">
              <n-icon>
                <ChessPawn />
              </n-icon>
              譚秉家
            </div>
            <div class="f:#d9a669 font:1.5em p:4px">| B11115001</div>
          </div>
        </div>
      </div>

      <div class="text-align:center f:white mt:16px">
        Made with ❤️ by Group 23
      </div>
    </div>
  </n-layout-footer>
</template>

<script setup lang="ts">
import { Chess, ChessKing, ChessPawn, ChessQueen } from '@vicons/fa';
import { NIcon, NLayoutFooter } from 'naive-ui';
</script>
