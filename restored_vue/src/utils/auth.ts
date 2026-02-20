export function getAuthToken(): string | null {
  return localStorage.getItem('auth_token')
}

export function clearAuth() {
  localStorage.removeItem('auth_token')
  localStorage.removeItem('auth_expires')
}

export function isAuthenticated(): boolean {
  return !!getAuthToken()
}

export async function logout() {
  const token = getAuthToken()
  if (token) {
    try {
      await fetch('/api/auth/logout', {
        method: 'POST',
        headers: { 'X-Auth-Token': token }
      })
    } catch {}
  }
  clearAuth()
  window.location.replace('/login')
}
