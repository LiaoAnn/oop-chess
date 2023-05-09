<template>
  <n-layout-header bordered>
    <div class="p:.5em|0">
      <div
        class="w:80% flex align-items:center justify-content:space-between margin:0|auto height:3em"
      >
        <div class="flex align-items:center">
          <div class="icon"></div>
          <n-menu
            :options="menuOptions"
            :value="currMenuValue"
            mode="horizontal"
            @update:value="currMenuValue = $event"
          />
        </div>
      </div>
    </div>
  </n-layout-header>
</template>

<script setup lang="ts">
import { MenuOption, NLayoutHeader, NMenu } from 'naive-ui';
import { h, ref } from 'vue';
import { RouterLink } from 'vue-router';

const currMenuValue = ref('home');
const classStr =
  'display:block padding:0|.5em color:inherit text-decoration:none';
const menuOptions: MenuOption[] = [
  {
    label: () =>
      h(
        RouterLink,
        {
          to: '/',
          class: classStr,
        },
        'Home'
      ),
    name: 'home',
    key: 'home',
  },
  {
    label: () =>
      h(
        RouterLink,
        {
          to: '/game',
          class: classStr,
        },
        'Game'
      ),
    name: 'game',
    key: 'game',
  },
];
</script>
