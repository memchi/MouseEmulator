:: ---------------------------------------------------------------------------------------
:: http://astyle.sourceforge.net/astyle.html
:: ---------------------------------------------------------------------------------------
set AStyleExe=%~dp0Tools\AStyle\AStyle.exe
set AStyleConfigTxt=%~dp0Tools\AStyle\AStyleConfig.txt

%AStyleExe% --version

%AStyleExe% --options=%AStyleConfigTxt% --recursive %~dp0Arduino/MouseEmulator/*.ino,*.pde,*.h,*.c,*.cpp

:: pause