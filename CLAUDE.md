# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

CodeFreeMax (module name: `kiro2api`) is a multi-channel AI API proxy that aggregates 7 AI service providers (Kiro/AWS Q, Orchids, Antigravity/Google, Cursor, Warp, Claude API, Grok) into a unified OpenAI-compatible API. It has a Go backend and a Vue 3 frontend admin panel, developed as separate projects.

## Development Commands

### Backend (Go)
```bash
cd restored_go
go build -o main.exe .    # Build
./main.exe                 # Run (listens on :8080)
```

### Frontend (Vue)
```bash
cd restored_vue
npm install                # Install dependencies
npm run dev                # Dev server on :5173, proxies /api and /oauth to :8080
npm run build              # Production build to dist/
```

### Docker (Production)
```bash
docker-compose up -d       # Starts app (:8877→:8000) + Redis
```

## Architecture

### Backend (`restored_go/`)

- **Framework**: GoFrame v2 (`github.com/gogf/gf/v2`) — routing, middleware, config
- **ORM**: GORM with SQLite (`glebarez/sqlite`), database at `./data/kiro2api.db`
- **Go version**: 1.22.0

**Key directories:**
- `internal/logic/{kiro,orchids,antigravity,cursor,warp,claudeapi,grok}/` — Per-channel proxy logic. Each channel has its own auth flow, upstream protocol, and token refresh mechanism
- `internal/controller/` — HTTP controllers: `auth.go`, `accounts.go`, `channel_accounts.go`, `config.go`, `model_manage.go`, `tutorial.go`, `test.go`
- `internal/dao/` — Data access layer (GORM models + migrations + seed data)
- `internal/logic/account_queue.go` — Redis-based round-robin account rotation
- `internal/gate/` — Credential encryption system (`gate:` prefix for encrypted fields)
- `internal/context/` — Context compression / token counting for upstream requests
- `main.go` — Entry point, server setup, route registration, chat completion routing

**Routing pattern**: `main.go` registers all routes. Admin API under `/api/*` uses `AuthMiddleware`. Chat completions are routed via `/{channel}/v1/messages` (Claude protocol) and `/{channel}/v1/chat/completions` (OpenAI protocol).

**Auth**: Token-based admin auth (32-byte hex, 24h expiry, `X-Auth-Token` header). Default password: `admin123`.

### Frontend (`restored_vue/`)

- **Stack**: Vue 3 (Composition API) + TypeScript + Vite 5 + Naive UI + Pinia + Axios
- **No custom components** — all views are self-contained in `src/views/`
- **State**: `src/stores/accounts.ts` (account CRUD, pagination, batch ops), `src/stores/channels.ts` (7 channel configs with colors/fields)
- **HTTP**: `src/utils/http.ts` — Axios instance with auth interceptor
- **Styling**: CSS variables defined in `src/styles/global.css` and `src/App.vue`. Uses `--primary-color`, `--text-color`, `--card-color`, `--border-color`, `--body-color`, etc. No CSS framework — hand-written scoped styles per view.
- **Icons**: Inline SVGs in templates (no icon library for nav/cards)

**Routes**: `/login`, `/dashboard`, `/accounts`, `/config`, `/models`, `/tutorial`

**Dev proxy** (`vite.config.ts`): `/api` and `/oauth` → `http://localhost:8080`

### Channel Protocols

| Channel | Upstream Protocol | Auth |
|---------|------------------|------|
| Kiro | AWS SigV4 | IAM/OAuth (PKCE) |
| Orchids | WebSocket + SSE | Clerk session token |
| Antigravity | Google Cloud REST | OAuth2 |
| Cursor | Connect RPC | WorkOS session |
| Warp | Protobuf/HTTP | Firebase auth |
| Claude API | REST | API key / session key |
| Grok | REST | Cookie-based |

### Infrastructure

- **Redis** required for account queue rotation (default `127.0.0.1:6379`)
- **SQLite** for persistent storage (accounts, config, tutorial data, models)
- **Config**: `restored_go/manifest/config/config.yaml` (dev), `./config.yaml` (Docker mount)

## Conventions

- Backend responses use `{"code": 0, "data": ...}` for success, non-zero code for errors
- Frontend uses Chinese (zh-CN) for all UI text
- Database migrations and seed data run automatically on startup in `dao/` package
- Channel-specific account fields vary — check `channels.ts` for each channel's field definitions
