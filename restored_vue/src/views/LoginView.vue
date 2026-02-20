<template>
  <div class="login-page">
    <div class="login-card">
      <div class="login-header">
        <div class="logo-mark">C</div>
        <h1 class="login-title">CodeFreeMax</h1>
        <p class="login-subtitle">管理面板登录</p>
      </div>

      <div class="login-form">
        <label class="form-label">密码</label>
        <div class="input-wrapper">
          <input
            v-model="password"
            :type="showPassword ? 'text' : 'password'"
            class="form-input"
            placeholder="请输入管理密码"
            @keydown="onKeydown"
            autofocus
          />
          <button @click="showPassword = !showPassword" class="toggle-btn" type="button">
            <svg v-if="!showPassword" width="18" height="18" viewBox="0 0 18 18" fill="none">
              <path d="M1.5 9C1.5 9 4 4 9 4C14 4 16.5 9 16.5 9C16.5 9 14 14 9 14C4 14 1.5 9 1.5 9Z" stroke="currentColor" stroke-width="1.4" stroke-linejoin="round"/>
              <circle cx="9" cy="9" r="2.5" stroke="currentColor" stroke-width="1.4"/>
            </svg>
            <svg v-else width="18" height="18" viewBox="0 0 18 18" fill="none">
              <path d="M2 2L16 16M7.5 7.6A2.5 2.5 0 0010.4 10.5M1.5 9C1.5 9 4 4 9 4C10.2 4 11.3 4.3 12.2 4.8M16.5 9C16.5 9 15.2 11.5 12.5 13" stroke="currentColor" stroke-width="1.4" stroke-linecap="round" stroke-linejoin="round"/>
            </svg>
          </button>
        </div>

        <button class="login-btn" :disabled="loading" @click="handleLogin">
          <span v-if="loading" class="btn-loading">
            <svg class="spinner" width="16" height="16" viewBox="0 0 16 16" fill="none">
              <circle cx="8" cy="8" r="6" stroke="currentColor" stroke-width="2" opacity="0.25"/>
              <path d="M14 8A6 6 0 002 8" stroke="currentColor" stroke-width="2" stroke-linecap="round"/>
            </svg>
            登录中...
          </span>
          <span v-else>登录</span>
        </button>
      </div>

      <p class="login-hint">默认密码: admin123</p>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue'
import { useRouter } from 'vue-router'
import { useMessage } from 'naive-ui'

const router = useRouter()
const message = useMessage()

const password = ref('')
const loading = ref(false)
const showPassword = ref(false)

const handleLogin = async () => {
  if (!password.value) {
    message.warning('请输入密码')
    return
  }
  loading.value = true
  try {
    const response = await fetch('/api/auth/login', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ password: password.value })
    })
    const data = await response.json()
    if (data.code === 0) {
      localStorage.setItem('auth_token', data.data.token)
      localStorage.setItem('auth_expires', data.data.expiresAt)
      message.success('登录成功')
      router.push('/accounts')
    } else {
      message.error(data.message || '认证失败')
    }
  } catch {
    message.error('网络连接错误')
  } finally {
    loading.value = false
  }
}

const onKeydown = (e: KeyboardEvent) => {
  if (e.key === 'Enter') handleLogin()
}
</script>

<style scoped>
.login-page {
  min-height: 100vh;
  display: flex;
  align-items: center;
  justify-content: center;
  background: var(--bg-color, #f8f9fb);
  padding: 20px;
}

.login-card {
  width: 100%;
  max-width: 380px;
  background: var(--card-color, #fff);
  border: 1px solid var(--border-color, #eaedf0);
  border-radius: 14px;
  padding: 36px 32px 28px;
  box-shadow: 0 1px 3px rgba(0,0,0,.04), 0 8px 24px rgba(0,0,0,.04);
}

.login-header {
  text-align: center;
  margin-bottom: 28px;
}
.logo-mark {
  width: 44px; height: 44px;
  background: var(--primary-color, #5b6abf);
  color: #fff;
  border-radius: 11px;
  display: inline-flex; align-items: center; justify-content: center;
  font-size: 20px; font-weight: 700;
  letter-spacing: -0.5px;
  margin-bottom: 14px;
}
.login-title {
  font-size: 20px; font-weight: 700;
  color: var(--text-color, #1a1d21);
  margin: 0 0 4px;
}
.login-subtitle {
  font-size: 13px;
  color: var(--text-color-3, #9aa0a6);
  margin: 0;
}

.login-form { display: flex; flex-direction: column; gap: 16px; }
.form-label {
  font-size: 13px; font-weight: 500;
  color: var(--text-color-2, #5f6368);
  margin-bottom: -8px;
}
.input-wrapper {
  position: relative;
  display: flex;
  align-items: center;
}
.form-input {
  width: 100%;
  padding: 10px 40px 10px 14px;
  border: 1px solid var(--border-color, #eaedf0);
  border-radius: 8px;
  font-size: 14px;
  color: var(--text-color, #1a1d21);
  background: var(--card-color, #fff);
  outline: none;
  transition: border-color .15s;
  font-family: inherit;
}
.form-input::placeholder { color: var(--text-color-3, #9aa0a6); }
.form-input:focus { border-color: var(--primary-color, #5b6abf); box-shadow: 0 0 0 3px rgba(91,106,191,.1); }

.toggle-btn {
  position: absolute; right: 8px;
  background: none; border: none; cursor: pointer;
  color: var(--text-color-3, #9aa0a6);
  padding: 4px; border-radius: 4px;
  display: flex; align-items: center; justify-content: center;
  transition: color .15s;
}
.toggle-btn:hover { color: var(--text-color-2, #5f6368); }

.login-btn {
  width: 100%;
  padding: 10px;
  background: var(--primary-color, #5b6abf);
  color: #fff;
  border: none; border-radius: 8px;
  font-size: 14px; font-weight: 600;
  cursor: pointer;
  transition: opacity .15s;
  font-family: inherit;
  margin-top: 4px;
}
.login-btn:hover:not(:disabled) { opacity: .9; }
.login-btn:disabled { opacity: .6; cursor: not-allowed; }

.btn-loading {
  display: inline-flex; align-items: center; gap: 6px;
}
.spinner {
  animation: spin .8s linear infinite;
}
@keyframes spin { to { transform: rotate(360deg); } }

.login-hint {
  text-align: center;
  font-size: 12px;
  color: var(--text-color-3, #9aa0a6);
  margin: 20px 0 0;
}
</style>
