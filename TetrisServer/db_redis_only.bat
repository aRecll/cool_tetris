@echo off
REM Поднять только Postgres и Redis (для локальной отладки сервера)
docker compose up -d db redis