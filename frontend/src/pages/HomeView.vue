<template>
  <n-layout-content>
    <div class="w:75% margin:2em|auto">
      <div class="grid-cols:2 h:100%">
        <div class="p:2em">
          <div class="font:3em mt:1.5em font-weight:900">
            OOP Project 2 | Chess
          </div>
          <div class="font:1.2em mt:1em line-height:2em font-weight:500 f:#aaa">
            在棋局的舞台上，智慧與謀略交織成華麗的樂章。<br />
            每一步，都是經過深思熟慮的決策，描繪出勝利的藍圖。<br />
            展現你的棋力，挑戰對手，獲得無盡的榮耀與成就。<br />
            讓西洋棋的魅力，在網頁中綻放出獨特的光芒。
          </div>
          <div class="mt:8em flex gap:8px">
            <n-button class="p:1em|2em font:2em font-weight:500" type="primary">
              <n-icon class="mr:16px" size="32px">
                <Chess />
              </n-icon>
              Play
            </n-button>
            <n-button
              class="p:1em|2em font:2em font-weight:500"
              tag="a"
              href="https://github.com/LiaoAnn/oop-chess"
              target="_blank"
            >
              <template #icon>
                <n-icon class="mr:16px" size="32px">
                  <Github />
                </n-icon>
              </template>
              Github
            </n-button>
          </div>
        </div>
        <div
          :class="`bg:url('${chessBg}') height:600px background-size:100% bg:no-repeat background-position:50%|50%`"
        ></div>
      </div>
    </div>
  </n-layout-content>
</template>

<script setup lang="ts">
import { Chess, Github } from '@vicons/fa';
import { NButton, NIcon, NLayoutContent } from 'naive-ui';

import chessBg from '@/assets/chess-bg.jpg';
</script>
