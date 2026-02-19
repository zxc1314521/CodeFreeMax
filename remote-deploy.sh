#!/bin/bash
set -e

CONFIG_SERVER="http://10.88.88.129:9527"
VARIANT="${1:-latest}"
WORK_DIR="/opt/codefreemax"
TMP_COMPOSE=$(mktemp)
TMP_ENC=$(mktemp)

_K1="cfm@2024"
_K2="!xK9mQ3"

cleanup() {
    rm -f "$TMP_COMPOSE" "$TMP_ENC"
}
trap cleanup EXIT

command_exists() {
    command -v "$1" >/dev/null 2>&1
}

get_compose_cmd() {
    if command_exists "docker" && docker compose version >/dev/null 2>&1; then
        echo "docker compose"
    elif command_exists "docker-compose"; then
        echo "docker-compose"
    else
        echo "none"
    fi
}

compose_cmd=$(get_compose_cmd)
if [ "$compose_cmd" = "none" ]; then
    echo "错误: 未安装 docker compose"
    exit 1
fi


echo "==> 获取部署配置..."
HTTP_CODE=$(curl -s -o "$TMP_ENC" -w "%{http_code}" "$CONFIG_SERVER/docker-compose.enc")
if [ "$HTTP_CODE" != "200" ]; then
    echo "错误: 无法获取部署配置 (HTTP $HTTP_CODE)，请确认服务器 10.88.88.129:9999 是否在线"
    exit 1
fi

echo "==> 解析配置..."
openssl enc -aes-256-cbc -d -salt -pbkdf2 -in "$TMP_ENC" -out "$TMP_COMPOSE" -pass "pass:${_K1}${_K2}" 2>/dev/null
if [ $? -ne 0 ] || [ ! -s "$TMP_COMPOSE" ]; then
    echo "错误: 配置解析失败"
    exit 1
fi
rm -f "$TMP_ENC"


mkdir -p "$WORK_DIR/data"


if [ ! -f "$WORK_DIR/config.yaml" ]; then
    echo "==> 首次部署，获取默认配置..."
    curl -sf "$CONFIG_SERVER/config.yaml" -o "$WORK_DIR/config.yaml" || {
        echo "警告: 无法获取 config.yaml，请手动创建 $WORK_DIR/config.yaml"
    }
fi

cd "$WORK_DIR"

if [ "$VARIANT" = "beta" ]; then
    export DOCKER_IMAGE="ssmdo/codefreemax:beta"
    echo "==> 部署 beta 版本..."
else
    export DOCKER_IMAGE="ssmdo/codefreemax:latest"
    echo "==> 部署 latest 版本..."
fi

echo "==> 拉取镜像..."
$compose_cmd -f "$TMP_COMPOSE" pull codefreemax

echo "==> 启动服务..."
$compose_cmd -f "$TMP_COMPOSE" -p codefreemax up -d --remove-orphans --force-recreate

echo ""
echo "==> 部署完成！"
echo "==> 服务地址: http://$(hostname -I | awk '{print $1}'):8877"
