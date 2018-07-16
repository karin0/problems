@echo off
if "%1"=="" goto loop
echo Test %1
checker_win32 mine%1.in mine%1.out mine%1.ans
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
pause
:end