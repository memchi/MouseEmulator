@echo off
echo --------------------------------------------------------------------------------
echo %DATE% %TIME% %~nx0 for user: "%USERNAME%" on computer: "%COMPUTERNAME%" starting
echo --------------------------------------------------------------------------------

if not exist ".\Arduino" (
    .\Tools\Junction\junction.exe .\Arduino %USERPROFILE%\Documents\Arduino
) else (
    echo .\Arduino is already here
)

:END
echo --------------------------------------------------------------------------------
echo %DATE% %TIME% %~nx0 for user: "%USERNAME%" on computer: "%COMPUTERNAME%" ended
echo --------------------------------------------------------------------------------
pause
