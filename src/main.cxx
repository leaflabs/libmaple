int main(void)
{
    init();
    setup();

    while (1) {
        loop();
    }
    return 0;
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
