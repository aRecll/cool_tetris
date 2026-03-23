@echo off
REM Поднять весь стек: app-server + db + redis (с override)
docker compose up -d --build app-server