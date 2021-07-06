@ECHO OFF
IF NOT EXIST obj\NUL MD obj
IF EXIST obj\*.obj DEL obj\*.obj
IF EXIST obj\*.res DEL obj\*.res
IF "%1"=="clean" GOTO END
RC -I..\snippets -Foobj\slems.res slems.rc
IF ERRORLEVEL 1 GOTO END
CL @..\snippets\build-release-small.build -Foobj\ @slems.build obj\slems.res
:END
