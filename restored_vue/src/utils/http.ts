import axios from 'axios'

const http = axios.create({
  timeout: 30000
})

// 请求拦截器 - 添加 auth token
http.interceptors.request.use((config) => {
  const token = localStorage.getItem('auth_token')
  if (token) {
    config.headers['X-Auth-Token'] = token
  }
  return config
})

// 响应拦截器 - 处理 401
http.interceptors.response.use(
  (response) => response,
  (error) => {
    if (error.response?.status === 401) {
      localStorage.removeItem('auth_token')
      localStorage.removeItem('auth_expires')
      window.location.replace('/login')
    }
    return Promise.reject(error)
  }
)

export default http
