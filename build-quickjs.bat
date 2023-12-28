@echo off

setlocal enabledelayedexpansion

cd quickjs

set CC=gcc
set AR=ar

set files=quickjs.c libregexp.c libunicode.c cutils.c libbf.c quickjs-libc.c 
set count=6
set version = ""

for /f "delims=" %%a in (VERSION) do (
    set "version=!version!%%a"
)

set version="!version!"

if not exist "build" (
    mkdir "build"
)

set current=1
for %%f in (%files%) do (
    set "file=%%f"
    set "oName=%%~nf.o"
    echo [!current!/!count!] Compiling !file!
    %CC% -g -Wall -MMD -MF build\!oName!.d -Wno-array-bounds -DCONFIG_BIGNUM -DCONFIG_VERSION=\"!version!\" -O2 -c -o build\!oName! !file!
    set /a "current+=1"
)

echo linking files (libquickjs.a)

%AR% rcs libquickjs.a build\quickjs.o build\libregexp.o build\libunicode.o build\cutils.o build\libbf.o build\quickjs-libc.o

echo building qjsc (compiler)

gcc -I. -DCONFIG_BIGNUM -DCONFIG_VERSION=\"!version!\" qjsc.c -L. -lquickjs -lpthread -o qjsc.exe

endlocal
