import { createRouter, createWebHistory } from 'vue-router'
import registerBeforeHooks from './before'
import { useAuthStore } from '@/stores/auth'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/login',
      name: 'login',
      meta: { template: 'auth' },
      component: () => import('../views/auth/Login.vue')
    },
    {
      path: '/logout',
      name: 'logout',
      meta: { template: 'auth' },
      component: () => import('../views/auth/Logout.vue')
    },
    {
      path: '/',
      name: 'dashboard',
      meta: { template: 'main', requiresAuth: false },
      component: () => import('../views/Dashboard.vue'),
      props () {
        return {
          id: useAuthStore().user.id
        }
      }
    },
    {
      path: '/users',
      name: 'users',
      meta: { template: 'main', requiresAuth: true, roles: ['admin'] },
      component: () => import('../views/Users.vue')
    }
  ]
})

registerBeforeHooks(router);

export default router
