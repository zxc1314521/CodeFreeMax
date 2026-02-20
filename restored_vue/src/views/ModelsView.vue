<script setup lang="ts">
import { ref, computed, onMounted } from 'vue'
import { useMessage, useDialog } from 'naive-ui'
import http from '../utils/http'
import { CHANNELS, enabledChannelIds } from '../stores/channels'

interface ModelItem {
  id: number
  model_id: string
  name: string
  owned_by: string
  is_default: boolean
  enabled: boolean
  sort_order: number
}

const message = useMessage()
const dialog = useDialog()
const loading = ref(false)
const activeChannel = ref('kiro')
const modelsData = ref<Record<string, ModelItem[]>>({})
const page = ref(1)
const pageSize = 10

// Dialog state
const showDialog = ref(false)
const editingModel = ref<Partial<ModelItem> & { channel?: string }>({})
const isEditing = ref(false)
const saving = ref(false)

const channelOptions = computed(() =>
  enabledChannelIds.map(id => ({
    label: CHANNELS[id].name,
    value: id
  }))
)

const currentModels = computed(() => modelsData.value[activeChannel.value] || [])
const totalModels = computed(() => currentModels.value.length)
const totalPages = computed(() => Math.max(1, Math.ceil(totalModels.value / pageSize)))
const pagedModels = computed(() => {
  const start = (page.value - 1) * pageSize
  return currentModels.value.slice(start, start + pageSize)
})

function switchChannel(ch: string) {
  activeChannel.value = ch
  page.value = 1
}

async function fetchModels() {
  loading.value = true
  try {
    const res = (await http.get('/api/models/list')).data
    if (res.code === 0 && res.data) {
      modelsData.value = res.data
    }
  } catch {
    message.error('获取模型列表失败')
  } finally {
    loading.value = false
  }
}

function openAdd() {
  isEditing.value = false
  editingModel.value = {
    channel: activeChannel.value,
    model_id: '',
    name: '',
    owned_by: activeChannel.value,
    is_default: false,
    enabled: true,
    sort_order: currentModels.value.length + 1
  }
  showDialog.value = true
}

function openEdit(model: ModelItem) {
  isEditing.value = true
  editingModel.value = { ...model, channel: activeChannel.value }
  showDialog.value = true
}

async function saveModel() {
  const m = editingModel.value
  if (!m.model_id?.trim()) {
    message.warning('Model ID 不能为空')
    return
  }
  saving.value = true
  try {
    const res = (await http.post('/api/models/save', {
      id: isEditing.value ? m.id : undefined,
      channel: m.channel,
      model_id: m.model_id,
      name: m.name || m.model_id,
      owned_by: m.owned_by || m.channel,
      is_default: m.is_default || false,
      enabled: m.enabled !== false,
      sort_order: m.sort_order || 0
    })).data
    if (res.code === 0) {
      message.success(isEditing.value ? '编辑成功' : '添加成功')
      showDialog.value = false
      await fetchModels()
    } else {
      message.error(res.msg || '保存失败')
    }
  } catch {
    message.error('保存失败')
  } finally {
    saving.value = false
  }
}

function confirmDelete(model: ModelItem) {
  dialog.warning({
    title: '确认删除',
    content: `确定要删除模型 "${model.model_id}" 吗？`,
    positiveText: '删除',
    negativeText: '取消',
    onPositiveClick: async () => {
      try {
        const res = (await http.post('/api/models/delete', { id: model.id })).data
        if (res.code === 0) {
          message.success('删除成功')
          await fetchModels()
        } else {
          message.error(res.msg || '删除失败')
        }
      } catch {
        message.error('删除失败')
      }
    }
  })
}

async function toggleEnabled(model: ModelItem) {
  try {
    const res = (await http.post('/api/models/toggle', {
      id: model.id,
      enabled: !model.enabled
    })).data
    if (res.code === 0) {
      model.enabled = !model.enabled
    } else {
      message.error(res.msg || '更新失败')
    }
  } catch {
    message.error('更新失败')
  }
}

onMounted(() => { fetchModels() })
</script>

<template>
  <div class="models-page">
    <div class="page-header">
      <div>
        <h2 class="page-title">模型管理</h2>
        <p class="page-desc">管理各渠道支持的模型列表，支持添加、编辑、删除和启用/禁用</p>
      </div>
      <div class="header-actions">
        <button @click="fetchModels" :disabled="loading" class="btn btn-outline">
          {{ loading ? '刷新中...' : '刷新' }}
        </button>
        <button @click="openAdd" class="btn btn-primary">+ 添加模型</button>
      </div>
    </div>

    <!-- 渠道选择 -->
    <div class="channel-tabs">
      <button v-for="ch in channelOptions" :key="ch.value"
        @click="switchChannel(ch.value)"
        :class="['ch-tab', { active: activeChannel === ch.value }]">
        {{ ch.label }}
        <span class="ch-count">{{ (modelsData[ch.value] || []).length }}</span>
      </button>
    </div>

    <!-- 模型表格 -->
    <div class="card">
      <div v-if="loading" class="empty-state">加载中...</div>
      <div v-else-if="currentModels.length === 0" class="empty-state">暂无模型数据，点击"添加模型"开始</div>
      <table v-else class="data-table">
        <thead>
          <tr>
            <th style="width:50px">ID</th>
            <th>Model ID</th>
            <th>名称</th>
            <th style="width:70px">默认</th>
            <th style="width:70px">状态</th>
            <th style="width:60px">排序</th>
            <th style="width:130px;text-align:center">操作</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="model in pagedModels" :key="model.id" :class="{ 'row-disabled': !model.enabled }">
            <td class="text-muted">{{ model.id }}</td>
            <td>
              <code class="model-id">{{ model.model_id }}</code>
            </td>
            <td>{{ model.name || '-' }}</td>
            <td>
              <span v-if="model.is_default" class="badge badge-primary">默认</span>
              <span v-else class="text-muted">-</span>
            </td>
            <td>
              <button @click="toggleEnabled(model)" :class="['toggle-btn', model.enabled ? 'on' : 'off']">
                <span class="toggle-dot"></span>
              </button>
            </td>
            <td class="text-muted">{{ model.sort_order }}</td>
            <td class="actions-cell">
              <button @click="openEdit(model)" class="act-btn act-edit">编辑</button>
              <button @click="confirmDelete(model)" class="act-btn act-delete">删除</button>
            </td>
          </tr>
        </tbody>
      </table>
    </div>

    <!-- 分页 -->
    <div v-if="totalModels > 0" class="pagination-bar">
      <span class="page-info">共 {{ totalModels }} 个模型</span>
      <div class="page-btns">
        <button @click="page = Math.max(1, page - 1)" :disabled="page <= 1" class="page-btn">&lt;</button>
        <button v-for="p in totalPages" :key="p" @click="page = p"
          :class="['page-btn', { active: page === p }]">{{ p }}</button>
        <button @click="page = Math.min(totalPages, page + 1)" :disabled="page >= totalPages" class="page-btn">&gt;</button>
      </div>
    </div>

    <!-- 添加/编辑弹窗 -->
    <div v-if="showDialog" class="modal-overlay" @click.self="showDialog = false">
      <div class="modal">
        <div class="modal-header">
          <h3>{{ isEditing ? '编辑模型' : '添加模型' }}</h3>
          <button @click="showDialog = false" class="modal-close">&times;</button>
        </div>
        <div class="modal-body">
          <div class="form-group">
            <label>Model ID <span class="required">*</span></label>
            <input v-model="editingModel.model_id" placeholder="例如: claude-sonnet-4-5" class="form-input" />
          </div>
          <div class="form-group">
            <label>名称</label>
            <input v-model="editingModel.name" placeholder="例如: Claude Sonnet 4.5" class="form-input" />
          </div>
          <div class="form-group">
            <label>Owned By</label>
            <input v-model="editingModel.owned_by" :placeholder="activeChannel" class="form-input" />
          </div>
          <div class="form-row">
            <div class="form-group">
              <label>排序</label>
              <input v-model.number="editingModel.sort_order" type="number" class="form-input" />
            </div>
            <div class="form-group">
              <label class="checkbox-label">
                <input type="checkbox" v-model="editingModel.is_default" />
                <span>设为默认</span>
              </label>
            </div>
            <div class="form-group">
              <label class="checkbox-label">
                <input type="checkbox" v-model="editingModel.enabled" />
                <span>启用</span>
              </label>
            </div>
          </div>
        </div>
        <div class="modal-footer">
          <button @click="showDialog = false" class="btn btn-outline">取消</button>
          <button @click="saveModel" :disabled="saving" class="btn btn-primary">
            {{ saving ? '保存中...' : '保存' }}
          </button>
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped>
.models-page { padding: 20px 24px; }
.page-header { display: flex; align-items: flex-start; justify-content: space-between; margin-bottom: 20px; }
.page-title { font-size: 20px; font-weight: 600; color: var(--text-color); margin-bottom: 4px; }
.page-desc { font-size: 13px; color: var(--text-color-3); }
.header-actions { display: flex; gap: 8px; }

/* Buttons */
.btn {
  padding: 7px 16px;
  font-size: 13px;
  font-weight: 500;
  border-radius: 8px;
  border: none;
  cursor: pointer;
  transition: all .15s;
  white-space: nowrap;
}
.btn:disabled { opacity: .5; cursor: not-allowed; }
.btn-primary { background: var(--primary-color); color: #fff; }
.btn-primary:hover:not(:disabled) { opacity: .85; }
.btn-outline { background: var(--card-color); color: var(--text-color-2); border: 1px solid var(--border-color); }
.btn-outline:hover:not(:disabled) { border-color: var(--primary-color); color: var(--primary-color); }

/* Channel tabs */
.channel-tabs { display: flex; gap: 6px; margin-bottom: 16px; overflow-x: auto; padding-bottom: 4px; }
.ch-tab {
  padding: 6px 14px;
  font-size: 13px;
  font-weight: 500;
  border-radius: 8px;
  border: 1px solid var(--border-color);
  background: var(--card-color);
  color: var(--text-color-3);
  cursor: pointer;
  transition: all .15s;
  white-space: nowrap;
  display: flex;
  align-items: center;
  gap: 6px;
}
.ch-tab:hover { border-color: var(--primary-color); color: var(--text-color); }
.ch-tab.active { background: rgba(91,106,191,.1); color: var(--primary-color); border-color: rgba(91,106,191,.3); }
.ch-count {
  font-size: 11px;
  background: var(--body-color);
  padding: 1px 6px;
  border-radius: 10px;
  color: var(--text-color-3);
}
.ch-tab.active .ch-count { background: rgba(91,106,191,.15); color: var(--primary-color); }

/* Card & Table */
.card { background: var(--card-color); border: 1px solid var(--border-color); border-radius: 12px; overflow: hidden; }
.empty-state { padding: 40px 20px; text-align: center; font-size: 13px; color: var(--text-color-3); }

.data-table { width: 100%; border-collapse: collapse; font-size: 13px; }
.data-table th {
  background: var(--body-color);
  color: var(--text-color-3);
  font-weight: 500;
  padding: 10px 14px;
  text-align: left;
  border-bottom: 1px solid var(--border-color);
  font-size: 12px;
}
.data-table td {
  padding: 10px 14px;
  border-bottom: 1px solid var(--border-color);
  color: var(--text-color);
}
.data-table tr:last-child td { border-bottom: none; }
.data-table tr:hover td { background: var(--hover-color); }
.row-disabled td { opacity: .5; }

.model-id {
  font-family: 'Menlo','Monaco','Courier New',monospace;
  font-size: 12px;
  color: var(--primary-color);
  background: rgba(91,106,191,.08);
  padding: 2px 8px;
  border-radius: 4px;
}
.text-muted { color: var(--text-color-3); }

/* Badge */
.badge { display: inline-block; padding: 2px 8px; font-size: 11px; font-weight: 500; border-radius: 10px; }
.badge-primary { background: rgba(91,106,191,.12); color: var(--primary-color); }

/* Toggle */
.toggle-btn {
  width: 36px;
  height: 20px;
  border-radius: 10px;
  border: none;
  cursor: pointer;
  position: relative;
  transition: background .2s;
  padding: 0;
}
.toggle-btn.on { background: #10b981; }
.toggle-btn.off { background: #d1d5db; }
.toggle-dot {
  display: block;
  width: 16px;
  height: 16px;
  border-radius: 50%;
  background: #fff;
  position: absolute;
  top: 2px;
  transition: left .2s;
}
.toggle-btn.on .toggle-dot { left: 18px; }
.toggle-btn.off .toggle-dot { left: 2px; }

/* Action buttons */
.actions-cell { text-align: center; }
.act-btn {
  padding: 3px 10px;
  font-size: 12px;
  border-radius: 6px;
  border: 1px solid var(--border-color);
  background: var(--card-color);
  cursor: pointer;
  transition: all .15s;
  margin: 0 2px;
}
.act-edit { color: var(--primary-color); }
.act-edit:hover { border-color: var(--primary-color); background: rgba(91,106,191,.06); }
.act-delete { color: #ef4444; }
.act-delete:hover { border-color: #ef4444; background: rgba(239,68,68,.06); }

/* Pagination */
.pagination-bar {
  display: flex;
  align-items: center;
  justify-content: space-between;
  margin-top: 14px;
  font-size: 13px;
}
.page-info { color: var(--text-color-3); font-size: 12px; }
.page-btns { display: flex; gap: 4px; }
.page-btn {
  min-width: 30px;
  height: 30px;
  border-radius: 6px;
  border: 1px solid var(--border-color);
  background: var(--card-color);
  color: var(--text-color-3);
  font-size: 12px;
  cursor: pointer;
  transition: all .15s;
  display: flex;
  align-items: center;
  justify-content: center;
}
.page-btn:hover:not(:disabled) { border-color: var(--primary-color); color: var(--primary-color); }
.page-btn.active { background: var(--primary-color); color: #fff; border-color: var(--primary-color); }
.page-btn:disabled { opacity: .4; cursor: not-allowed; }

/* Modal */
.modal-overlay {
  position: fixed;
  inset: 0;
  background: rgba(0,0,0,.45);
  display: flex;
  align-items: center;
  justify-content: center;
  z-index: 1000;
}
.modal {
  background: var(--card-color);
  border-radius: 14px;
  width: 480px;
  max-width: 90vw;
  box-shadow: 0 20px 60px rgba(0,0,0,.2);
}
.modal-header {
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding: 18px 22px;
  border-bottom: 1px solid var(--border-color);
}
.modal-header h3 { font-size: 16px; font-weight: 600; color: var(--text-color); margin: 0; }
.modal-close {
  width: 28px;
  height: 28px;
  border-radius: 6px;
  border: none;
  background: transparent;
  font-size: 18px;
  color: var(--text-color-3);
  cursor: pointer;
  display: flex;
  align-items: center;
  justify-content: center;
}
.modal-close:hover { background: var(--hover-color); color: var(--text-color); }
.modal-body { padding: 18px 22px; }
.modal-footer {
  display: flex;
  justify-content: flex-end;
  gap: 8px;
  padding: 14px 22px;
  border-top: 1px solid var(--border-color);
}

/* Form */
.form-group { margin-bottom: 14px; }
.form-group label { display: block; font-size: 12px; font-weight: 500; color: var(--text-color-2); margin-bottom: 6px; }
.required { color: #ef4444; }
.form-input {
  width: 100%;
  padding: 8px 12px;
  font-size: 13px;
  border: 1px solid var(--border-color);
  border-radius: 8px;
  background: var(--body-color);
  color: var(--text-color);
  outline: none;
  transition: border-color .15s;
  box-sizing: border-box;
}
.form-input:focus { border-color: var(--primary-color); }
.form-row { display: flex; gap: 14px; align-items: flex-end; }
.form-row .form-group { flex: 1; }
.checkbox-label {
  display: flex !important;
  align-items: center;
  gap: 6px;
  font-size: 13px !important;
  color: var(--text-color) !important;
  cursor: pointer;
  padding-top: 8px;
}
.checkbox-label input[type="checkbox"] { width: 15px; height: 15px; accent-color: var(--primary-color); }
</style>
