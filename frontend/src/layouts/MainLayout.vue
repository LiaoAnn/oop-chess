<template>
  <n-layout>
    <site-header />
    <router-view />
    <site-footer />
  </n-layout>
</template>

<script setup lang="ts">
import { NLayout } from 'naive-ui';

import SiteFooter from '@/components/SiteFooter.vue';
import SiteHeader from '@/components/SiteHeader.vue';
</script>
