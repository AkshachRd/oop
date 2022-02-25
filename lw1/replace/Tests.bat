@echo off

set PROGRAM="%~1"

if %PROGRAM%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Simple test
%PROGRAM% simpleInput.txt "%TEMP%\simpleOutput.txt" "foo" "bar" || goto err
fc simpleOutput.txt "%TEMP%\simpleOutput.txt" > nul || goto err
echo Test 1 passed

REM Loop testing
%PROGRAM% simpleInput.txt "%TEMP%\loopingOutput.txt" "ma" "mama" || goto err
fc loopingOutput.txt "%TEMP%\loopingOutput.txt" > nul || goto err
echo Test 2 passed

REM Trying to output into an executable file
%PROGRAM% simpleInput.txt %PROGRAM% "foo" "bar" && goto err
echo Test 3 passed

REM Trying to replace an empty line
%PROGRAM% simpleInput.txt "%TEMP%\output.txt" "" "bar" || goto err
fc simpleInput.txt "%TEMP%\output.txt" > nul || goto err
echo Test 4 passed

REM Replace in an empty file
%PROGRAM% empty.txt "%TEMP%\output.txt" "foo" "bar" || goto err
fc empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 5 passed

REM Return if fails to find substr
%PROGRAM% simpleInput.txt "%TEMP%\output.txt" "1231234" "WHITE" || goto err
fc returnIfFailsOutput.txt "%TEMP%\output.txt" > nul || goto err
echo Test 6 passed

REM Тесты прошли успешно
echo All tests passed successfuly
exit /B 0

REM Сюда будем попадать в случае ошибки
:err
echo Test failed
exit /B 1