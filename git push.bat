@echo off
setlocal EnableDelayedExpansion

:: 强制使用 UTF-8 代码页，避免中文乱码
chcp 65001 >nul

echo ==========================================
echo        Git 自动提交与推送工具
echo ==========================================
echo.

:: 切换到当前脚本所在目录
cd /d "%~dp0"

:: 检查是否为 git 仓库
git rev-parse --is-inside-work-tree >nul 2>&1
if errorlevel 1 (
    echo [错误] 当前目录不是 Git 仓库！
    pause
    exit /b 1
)

:: 输入提交信息
set /p commitMsg=请输入提交信息后按回车： 

if "!commitMsg!"=="" (
    echo [错误] 提交信息不能为空！
    pause
    exit /b 1
)

echo.
echo 正在执行 git add ...
git add .
if errorlevel 1 goto :error

echo 正在执行 git commit ...
git commit -m "!commitMsg!"
if errorlevel 1 goto :error

echo 正在执行 git push ...
git push
if errorlevel 1 goto :error

echo.
echo ==========================================
echo            推送成功完成！
echo ==========================================
timeout /t 20 >nul
exit /b 0


:error
echo.
echo ==========================================
echo        操作失败，请检查错误信息
echo ==========================================
pause
exit /b 1