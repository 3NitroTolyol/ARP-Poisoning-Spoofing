@echo off
echo [BUILD] Checking for Npcap SDK...
if not exist "..\npcap-sdk-1.16" (
    echo [ERROR] Npcap SDK not found in parent directory!
    echo Please download it and place it according to README instructions.
    pause
    exit /b
)

echo [BUILD] Compiling ARP Spoofer...
gcc ARP.c -o ARP.exe -I ../npcap-sdk-1.16/Include -L ../npcap-sdk-1.16/Lib/x64 -lwpcap -lws2_32

if %errorlevel% equ 0 (
    echo [SUCCESS] ARP.exe compiled successfully!
) else (
    echo [ERROR] Compilation failed.
)
pause