#!/bin/bash
#
# 加密 docker-compose.yml → docker-compose.enc
# 你在本机运行，生成加密文件后通过 HTTP 提供给朋友
#
# 用法: ./encrypt-compose.sh
#

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
SRC="$SCRIPT_DIR/docker-compose.yml"
DST="$SCRIPT_DIR/docker-compose.enc"
PASS="cfm@2024!xK9mQ3"

if [ ! -f "$SRC" ]; then
    echo "错误: 找不到 $SRC"
    exit 1
fi

openssl enc -aes-256-cbc -salt -pbkdf2 -in "$SRC" -out "$DST" -pass "pass:$PASS"
echo "==> 已加密: $DST ($(wc -c < "$DST") bytes)"
echo "==> 现在可以启动 HTTP 服务: python3 -m http.server 9527"
