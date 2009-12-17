setlocal

set ADR=0x%~1
set TYPE=%~2
set NAME=%~3
set TEXT=%~4
set HELP=%~5

set /a NUM=%ADR%/4
if %TYPE%==x set NAME=__STM32ReservedException%NUM%
if %TYPE%==e set FULLTYPE=Exception
if %TYPE%==i set FULLTYPE=Interrupt
set FULLTEXT=%TEXT% %FULLTYPE%
if not "%HELP%"=="" set FULLHELP= (%HELP%)
set FULL=[%ADR%] %FULLTEXT%%FULLHELP%

rem echo %NAME%

echo 	.long	%NAME%>>lanchon-stm32-vector.S

echo 	.weak	%NAME%>>lanchon-stm32-isrs.S
echo 	.globl	%NAME%>>lanchon-stm32-isrs.S
echo 	.set	%NAME%, __STM32DefaultExceptionHandler>>lanchon-stm32-isrs.S

echo EXTERN (%NAME%)>>lanchon-stm32-names.inc

if %TYPE%==x goto :eof

echo /* %FULL% */>>stm32exceptions.h
echo void %NAME%(void);>>stm32exceptions.h
echo.>>stm32exceptions.h

echo 	/* %FULL% */>>stm32exceptions.c
echo 	void %NAME%(void)>>stm32exceptions.c
echo 	{>>stm32exceptions.c
echo 		DEFAULT_EXCEPTION_HANDLER(%NAME%, "%TEXT%", %NUM%, %ADR%);>>stm32exceptions.c
echo 	}>>stm32exceptions.c
echo.>>stm32exceptions.c
