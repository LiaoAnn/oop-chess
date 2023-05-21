@echo off
cd frontend
start cmd /k "yarn dev"
cd ../backend/x64/Debug
start "" backend.exe
ping 127.0.0.1 -n 2 >nul
start "" "http://localhost:5173"
