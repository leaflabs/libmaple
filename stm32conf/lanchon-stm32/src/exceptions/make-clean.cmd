@echo off
setlocal

set DO=del

%DO% lanchon-stm32-vector.S
%DO% lanchon-stm32-isrs.S
%DO% lanchon-stm32-names.inc
%DO% stm32exceptions.h
%DO% stm32exceptions.c
