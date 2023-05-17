<template>
  <n-config-provider :theme-overrides="themeOverrides">
    <n-dialog-provider>
      <n-loading-bar-provider>
        <n-message-provider>
          <n-notification-provider>
            <router-view />
          </n-notification-provider>
        </n-message-provider>
      </n-loading-bar-provider>
    </n-dialog-provider>
  </n-config-provider>
</template>

<script setup lang="ts">
import '@master/css';
import 'vfonts/Inter.css';

import {
  NConfigProvider,
  NDialogProvider,
  NLoadingBarProvider,
  NMessageProvider,
  NNotificationProvider,
} from 'naive-ui';
import { useRoute } from 'vue-router';

import useTheme from './common/useTheme';

const route = useRoute();
console.log(route.params);
const { themeOverrides } = useTheme();
</script>
