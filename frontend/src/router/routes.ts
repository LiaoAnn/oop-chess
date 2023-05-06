import { RouteRecordRaw } from 'vue-router';

const childRoutes: RouteRecordRaw[] = [
  {
    path: '',
    name: 'Home',
    component: () => import('../pages/HomeView.vue'),
  },
];

const routes: RouteRecordRaw[] = [
  {
    path: '/',
    component: () => import('../layouts/MainLayout.vue'),
    children: childRoutes,
  },
  // Always leave this as last one,
  // but you can also remove it
  {
    path: '/:catchAll(.*)*',
    component: () => import('../pages/ErrorNotFound.vue'),
  },
];

export default routes;
