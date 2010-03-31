int main(void)
{
    init();
    setup();

    while (1) {
        loop();
    }
    return 0;
}

/* Required for C++ hackery */
/* TODO: This really shouldn't go here... move it later
 * */
extern "C" void __cxa_pure_virtual(void) {
  while(1)
    ;
}

/* Implemented:
 * void pinMode(pin, mode) 
 * void digitalWrite(pin, value)
 * uint32_t digitalRead(pin)
 * uint32_t analogRead(pin)
 * void randomSeed(seed)
 * long random(max)
 * long random(min, max)
 * */
