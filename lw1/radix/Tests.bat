@echo off

set PROGRAM="%~1"

if %PROGRAM%=="" (
	echo Please specify path to program
	exit /B 1
)

set OUT="%TEMP%\output.txt"

REM Simple test
%PROGRAM% 2 10 101 > %OUT%
fc test01.txt %OUT% > nul || goto err
echo Test 1 passed

REM Zero test
%PROGRAM% 10 2 0 > %OUT%
fc test02.txt %OUT% > nul || goto err
echo Test 2 passed

REM Negative zero test
%PROGRAM% 2 10 -0 > %OUT%
fc test03.txt %OUT% > nul || goto err
echo Test 3 passed

REM Invalid value digit test
%PROGRAM% 2 10 10* > %OUT%
fc test04.txt %OUT% > nul || goto err
echo Test 4 passed

REM Invalid source notation value digit test
%PROGRAM% 2 10 1K > %OUT%
fc test05.txt %OUT% > nul || goto err
echo Test 5 passed

REM Max positive border number  
%PROGRAM% 10 16 2147483647 > %OUT%
fc test06.txt %OUT% > nul || goto err
echo Test 6 passed

REM Max positive border number + 1  
%PROGRAM% 10 16 2147483648 > %OUT%
fc test07.txt %OUT% > nul || goto err
echo Test 7 passed

REM Max negative border number 
%PROGRAM% 10 16 -2147483647 > %OUT%
fc test08.txt %OUT% > nul || goto err
echo Test 8 passed

REM Max negative border number - 1  
%PROGRAM% 10 16 -2147483648 > %OUT%
fc test09.txt %OUT% > nul || goto err
echo Test 9 passed

REM Invalid radix value  
%PROGRAM% 1 16 1 > %OUT%
fc test10.txt %OUT% > nul || goto err
echo Test 10 passed

REM Тесты прошли успешно
echo All tests passed successfuly
exit /B 0

REM Сюда будем попадать в случае ошибки
:err
echo Test failed
exit /B 1