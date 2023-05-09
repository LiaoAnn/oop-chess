import { createDiscreteApi } from 'naive-ui';
import { createRouter, createWebHistory } from 'vue-router';

import useTheme from '@/common/useTheme';

import routes from './routes';

const { primaryColor } = useTheme();

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes,
});
const { loadingBar } = createDiscreteApi(['loadingBar'], {
  loadingBarProviderProps: {
    loadingBarStyle: {
      loading: `background-color: ${primaryColor};`,
    },
  },
});
router.beforeEach(function (to, from, next) {
  if (!from || to.path !== from.path) {
    if (loadingBar) {
      loadingBar.start();
    }
  }
  next();
});

router.afterEach(function (to, from) {
  if (!from || to.path !== from.path) {
    if (loadingBar) {
      loadingBar.finish();
    }
  }
});

export default router;
