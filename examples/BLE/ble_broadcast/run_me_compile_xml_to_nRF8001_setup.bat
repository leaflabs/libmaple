del ..\services.c
del ..\services.h
del ..\services_lock.h
del ..\ublue_setup.gen.out.txt

"%NRFGOSTUDIOPATH%\nrfgostudio.exe" -nrf8001 -g ble_broadcast.xml -codeGenVersion 1 -o .