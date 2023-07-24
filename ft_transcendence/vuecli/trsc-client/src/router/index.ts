import { createRouter, createWebHistory } from 'vue-router'
import HomeView from '@/views/HomeView.vue'
import { authToken, hostname, nick } from '@/globalProperties'

const router = createRouter({
  history: createWebHistory(),
  routes: [
    {
      path: '/',
      name: 'home',
      component: HomeView,
      meta: {
        requireAuth: true,
      },
    },
    {
      path: '/play',
      name: 'play',
      component: () => import('@/views/PlayView.vue'),
      meta: {
        requireAuth: true,
      },
    },
    {
      path: '/pong',
      name: 'pong',
      component: () => import('../views/PongView.vue'),
      meta: {
        requireAuth: true,
      },
    },
    {
      path: '/login',
      name: 'login',
      component: () => import('@/views/LoginView.vue'),
    },
    {
      path: '/unnamed',
      name: 'unnamed',
      component: () => import('../views/UnnamedView.vue'),
    },
    {
      path: '/g-res/:plrA/:plrB/:scA/:scB/:stc',
      name: 'g-res',
      component: () => import('../views/GameResultView.vue'),
      meta: {
        requireAuth: true,
      },
    },
    {
      path: '/account',
      name: 'account',
      component: () => import('../views/AccountView.vue'),
      meta: {
        requireAuth: true,
      },
    },
    {
      path: '/profile/:username',
      name: 'profile',
      component: () => import('../views/ProfileView.vue'),
      meta: {
        requireAuth: true,
      },
    },
    {
      path: '/oauth',
      name: 'oauth',
      component: () => import('../views/OauthView.vue'),
    },
	{
		path: '/ladder',
		name: 'ladder',
		component: () => import('../views/LadderView.vue'),
      meta: {
        requireAuth: true,
      },
	},
	{
		path: '/friends',
		name: 'friends',
		component: () => import('../views/FriendsView.vue'),
      meta: {
        requireAuth: true,
      },
	},
  {
    path: '/:pathMatch(.*)*',
    redirect: '/'
  },
  {
    path: '/profile',
    redirect: '/profile/>self<'
  }
  ]
})

router.beforeEach(async (to, form, next) => {
  if (to.name === 'login' && authToken.value != '') {
    next('/');
  }
  if (to.meta.requireAuth && authToken.value != '') {
    const requestOption = {
      method: 'GET',
      headers: {
        'Authorization': `Bearer ${authToken.value}`,
        'accept': 'application/json',
      }
    }
    await fetch(`${hostname.value}/auth/validate`, requestOption)
      .then(response => {
        if (response.status === 200) {
          return response.text();
        }
        else if (response.status === 418) {
          return 'guest';
        }
        else {
          sessionStorage.removeItem('authToken');
          authToken.value = '';
          return 'invalideToken';
        }
      })
      .then(data => {
        nick.value = data;
      })
      .catch(error => {
        //console.error(error); 
      });
  }
  if (to.meta.requireAuth && nick.value === 'guest') {
    next('/unnamed');
  }
  else if (to.meta.requireAuth && authToken.value === '') {
    next('/login');
  }
  else {
    next();
  }

})

export default router
