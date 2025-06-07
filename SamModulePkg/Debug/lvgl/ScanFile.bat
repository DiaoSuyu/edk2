@echo off
setlocal enabledelayedexpansion

:: 设置要搜索的根目录
set "rootDir=%~dp0"

:: 获取时间戳（格式：YYYY-MM-DD_HHMM）
for /f "tokens=1-5 delims=/: " %%a in ("%date% %time%") do (
    set "YYYY=%%a"
    set "MM=%%b"
    set "DD=%%c"
    set "HH=%%d"
    set "MIN=%%e"
)

:: 清除前导空格和0（仅适用于某些区域设置）
set "HH=0%HH%"
set "HH=%HH:~-2%"
set "MIN=0%MIN%"
set "MIN=%MIN:~-2%"

:: 设置输出文件名
set "outputFile=c_and_h_files_%YYYY%-%MM%-%DD%_%HH%%MIN%.log"

:: 清空输出文件
> "%outputFile%" echo.

:: 调用 DFS 函数处理根目录
call :DFS "%rootDir%"

echo 文件列表已生成到 %outputFile%
pause
exit /b

:DFS
set "currentDir=%~1"

:: 检查是否存在 .c 或 .h 文件
dir /b "%currentDir%\*.c" >nul 2>&1
set hasC=%errorlevel%
dir /b "%currentDir%\*.h" >nul 2>&1
set hasH=%errorlevel%

if not %hasC%==1 (
    set hasFile=1
) else if not %hasH%==1 (
    set hasFile=1
) else (
    set hasFile=0
)

if !hasFile! equ 1 (
    echo # >> "%outputFile%"
    echo # %currentDir% >> "%outputFile%"
    echo # >> "%outputFile%"

    for %%f in ("%currentDir%\*.c") do (
        if exist "%%f" echo %%~f >> "%outputFile%"
    )
    for %%f in ("%currentDir%\*.h") do (
        if exist "%%f" echo %%~f >> "%outputFile%"
    )

    echo. >> "%outputFile%"
)

:: 递归处理所有子目录
for /d %%d in ("%currentDir%\*") do (
    call :DFS "%%d"
)
goto :eof
