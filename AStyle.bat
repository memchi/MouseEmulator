:: ---------------------------------------------------------------------------------------
:: http://astyle.sourceforge.net/astyle.html
:: ---------------------------------------------------------------------------------------
set AStyleExe=%~dp0Tools\AStyle\AStyle.exe
set AStyleConfigTxt=%~dp0Tools\AStyle\AStyleConfig.txt

%AStyleExe% --version

%AStyleExe% --options=%AStyleConfigTxt% --recursive %~dp0Arduino/MouseEmulator/*.ino
%AStyleExe% --options=%AStyleConfigTxt% --recursive %~dp0Arduino/MouseEmulator/*.pde
%AStyleExe% --options=%AStyleConfigTxt% --recursive %~dp0Arduino/MouseEmulator/*.h
%AStyleExe% --options=%AStyleConfigTxt% --recursive %~dp0Arduino/MouseEmulator/*.c
%AStyleExe% --options=%AStyleConfigTxt% --recursive %~dp0Arduino/MouseEmulator/*.cpp

:: pause