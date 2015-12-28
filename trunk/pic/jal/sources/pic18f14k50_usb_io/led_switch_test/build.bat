@IF /I "%1"=="clean" GOTO clean

..\..\..\jalv24q2\bin\jalv2.exe -s ..\..\library 18f14k50_led_switch_test.jal
GOTO done



:clean 
	@del /f /q *.hex
	@del /f /q *.cod
	@del /f /q *.asm
	@goto done


:done

