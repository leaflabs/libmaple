/*
 *  test-rtc.c
 *  
 *  Example program that sets up the Real Time Clock and then blinks the
 *  LED in patterns for seconds and alarm interrupts.
 *
 *  Created by  Rod Gilchrist on 11-12-24.
 *
 */

#include "wirish.h"
#include "rtc.h"
#include "usb.h"

int globAlmCnt = 0;
int globOvCnt = 0;
int globSecCnt = 0;
int specAlmCnt = 0;
int lastGlobAlmCnt = -1;
int lastSpecAlmCnt = -1;

void rtc_sec_intr() { if (rtc_is_second()) globSecCnt++; }
void rtc_ovf_intr() { if (rtc_is_overflow()) globOvCnt++; }
void rtc_glob_alm_intr() { if (rtc_is_alarm()) globAlmCnt++; }
void rtc_spec_alm_intr() { if (rtc_is_alarm()) specAlmCnt++; }

void setup() {
    pinMode(BOARD_LED_PIN, OUTPUT);
	delay(5000);
	SerialUSB.println("begin RTC blink");
	delay(1000);	

	rtc_init(RTCSEL_LSI);
	rtc_set_prescaler_load(0x7fff);
	rtc_set_count(0);
	
	rtc_attach_interrupt(RTC_SECONDS_INTERRUPT, rtc_sec_intr);
	rtc_attach_interrupt(RTC_OVERFLOW_INTERRUPT, rtc_ovf_intr); // expected every 128000 seconds
	rtc_attach_interrupt(RTC_ALARM_GLOBAL_INTERRUPT, rtc_glob_alm_intr);
	rtc_attach_interrupt(RTC_ALARM_SPECIFIC_INTERRUPT, rtc_spec_alm_intr);
}

void loop() {
	int i,n;
	
	SerialUSB.print("Time + interrupt counts: ");
	SerialUSB.print(rtc_get_count());
	SerialUSB.print(".");
	SerialUSB.print(rtc_get_divider());
	SerialUSB.print(" (");
	SerialUSB.print(globSecCnt);
	SerialUSB.print(", ");
	SerialUSB.print(globOvCnt);
	SerialUSB.print(", ");
	SerialUSB.print(globAlmCnt);
	SerialUSB.print(", ");
	SerialUSB.print(specAlmCnt);
	SerialUSB.println(")");

	delay(1000);

	digitalWrite(BOARD_LED_PIN, 1);
	if ((lastSpecAlmCnt != specAlmCnt) || (lastGlobAlmCnt != globAlmCnt)){
		lastGlobAlmCnt = globAlmCnt;
		lastSpecAlmCnt = specAlmCnt;

		SerialUSB.println(" -- alarm -- ");
		for (i=0;i<3;i++) { digitalWrite(BOARD_LED_PIN, 0); delay(100); digitalWrite(BOARD_LED_PIN, 1); delay(100);}
		n = rtc_get_count() + 5;
		rtc_set_alarm(n);
	}
	
	delay(1000);
	digitalWrite(BOARD_LED_PIN, 0);
}

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.
__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();
	
    while (true) {
        loop();
    }
    return 0;
}
