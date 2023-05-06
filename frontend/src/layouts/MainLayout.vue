<template>
  <n-layout>
    <site-header />
    <router-view />
  </n-layout>
</template>

<script setup lang="ts">
import { NLayout } from 'naive-ui';

import SiteHeader from '@/components/SiteHeader.vue';
</script>
