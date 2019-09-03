@echo off

set OUTPUT_DIR=deploy
set EXE_PATH=release\zzz.exe
set LIB_DIR=%QTDIR%\bin

rem Create target directory
if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%

rem Deploy DLLs
%LIB_DIR%\windeployqt.exe --force --release --dir %OUTPUT_DIR% --no-quick-import --no-translations --no-webkit2 --no-angle --no-svg --no-webkit %EXE_PATH%

rem Removing unused DLLs
rem del /q %OUTPUT_DIR%\opengl32sw.dll

rem Deploy Exe
xcopy /y %EXE_PATH% %OUTPUT_DIR%

rem Compress Exe and DLLs. Note: DLLs in platforms/ directory should not be compressed.
rem upx %OUTPUT_DIR%\*.dll %OUTPUT_DIR%\Deling.exe
