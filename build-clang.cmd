@echo off
set args=-std=c99 -ffreestanding -nostdlib -Os
set args=%args% -fno-stack-check -fno-stack-protector -mno-stack-arg-probe
set args=%args% "-Wl,-entry:entry" -lkernel32 -luser32
md bin 2>nul

set "vs2019=C:\Program Files (x86)\Microsoft Visual Studio\2019"
set vsedition=Community
if exist "%vs2019%\Enterprise" set vsedition=Enterprise

set "PATH=%vs2019%\%vsedition%\VC\Tools\Llvm\bin;%PATH%"
call "%vs2019%\%vsedition%\VC\Auxiliary\Build\vcvars32.bat"
clang -m32 -o bin/DisplayGetTopology.exe DisplayGetTopology.c "-Wl,-subsystem:console" %args% || exit /b