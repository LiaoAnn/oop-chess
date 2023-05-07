<template>
  <n-config-provider :theme="theme" :theme-overrides="themeOverrdes">
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
  GlobalThemeOverrides,
  NConfigProvider,
  NDialogProvider,
  NLoadingBarProvider,
  NMessageProvider,
  NNotificationProvider,
} from 'naive-ui';
import { computed, ref } from 'vue';
import { useRoute } from 'vue-router';

const route = useRoute();
console.log(route.params);

//#region Theme
const theme = ref<(typeof NConfigProvider)['theme']>('light');
const basicThemeOverrides: GlobalThemeOverrides = {
  common: {
    primaryColor: '#632d13',
    primaryColorHover: '#632d13',
    primaryColorPressed: '#632d13',
    primaryColorSuppl: '#632d13',
    fontWeightStrong: '600',
  },
};

const themeOverrdes = computed(() => {
  return basicThemeOverrides;
});
//#endregion
</script>
