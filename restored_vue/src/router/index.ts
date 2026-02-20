import { createRouter, createWebHistory } from 'vue-router'
import { isAuthenticated } from '../utils/auth'

const router = createRouter({
  history: createWebHistory(),
  routes: [
    {
      path: '/login',
      name: 'login',
      component: () => import('../views/LoginView.vue'),
      meta: { title: '登录', public: true }
    },
    {
      path: '/',
      redirect: '/dashboard'
    },
    {
      path: '/dashboard',
      name: 'dashboard',
      component: () => import('../views/DashboardView.vue'),
      meta: { title: '仪表盘' }
    },
    {
      path: '/accounts',
      name: 'accounts',
      component: () => import('../views/AccountsView.vue'),
      meta: { title: '账号管理' }
    },
    {
      path: '/config',
      name: 'config',
      component: () => import('../views/ConfigView.vue'),
      meta: { title: '配置管理' }
    },
    {
      path: '/models',
      name: 'models',
      component: () => import('../views/ModelsView.vue'),
      meta: { title: '模型管理' }
    },
    {
      path: '/tutorial',
      name: 'tutorial',
      component: () => import('../views/TutorialView.vue'),
      meta: { title: '使用教程' }
    },
  ]
})

router.beforeEach((to, _from, next) => {
  if (to.meta.public) {
    if (to.path === '/login' && isAuthenticated()) {
      next('/dashboard')
      return
    }
    next()
    return
  }
  if (!isAuthenticated()) {
    next('/login')
    return
  }
  next()
})

export default router
