
#include "wirish.h"

/*
D5     PB6         -      TIM4_CH1       I2C1_SCL   -           -           Y
D6     PA8         -      TIM1_CH1       -          USART1_CK   -           Y
D7     PA9         -      TIM1_CH2       -          USART1_TX   -           Y
D8     PA10        -      TIM1_CH3       -          USART1_RX   -           Y
D9     PB7         -      TIM4_CH2       I2C1_SDA   -           -           Y
*/

//gpio_write_bit(GPIOB_BASE, 6, 1); // VGA_R
//gpio_write_bit(GPIOB_BASE, 6, 0); 

//(GPIOA_BASE)->BSRR = BIT(8);
//asm volatile("nop");
//(GPIOA_BASE)->BRR = BIT(8);
/*
    gpio_write_bit(GPIOB_BASE, 6, 1); // VGA_R
    gpio_write_bit(GPIOB_BASE, 6, 0); 
    gpio_write_bit(GPIOA_BASE, 8, 1); // VGA_G
    gpio_write_bit(GPIOA_BASE, 8, 0); 
    gpio_write_bit(GPIOA_BASE, 9, 1); // VGA_B
    gpio_write_bit(GPIOA_BASE, 9, 0); 
    gpio_write_bit(GPIOA_BASE, 10, 1); // VGA_V
    gpio_write_bit(GPIOA_BASE, 10, 0); 
    gpio_write_bit(GPIOB_BASE, 7, 1); // VGA_H
    gpio_write_bit(GPIOB_BASE, 7, 0); 
*/

#define LED_PIN 13
#define VGA_R 5 // B6
#define VGA_G 6 // A8
#define VGA_B 7 // A9
#define VGA_V 11 // A6
#define VGA_H 12 // A7
#define VGA_R_HIGH (GPIOB_BASE)->BSRR = BIT(6)
#define VGA_R_LOW  (GPIOB_BASE)->BRR  = BIT(6)
#define VGA_G_HIGH (GPIOA_BASE)->BSRR = BIT(8)
#define VGA_G_LOW  (GPIOA_BASE)->BRR  = BIT(8)
#define VGA_B_HIGH (GPIOA_BASE)->BSRR = BIT(9)
#define VGA_B_LOW  (GPIOA_BASE)->BRR  = BIT(9)
#define VGA_V_HIGH (GPIOA_BASE)->BSRR = BIT(6)
#define VGA_V_LOW  (GPIOA_BASE)->BRR  = BIT(6)
#define VGA_H_HIGH (GPIOA_BASE)->BSRR = BIT(7)
#define VGA_H_LOW  (GPIOA_BASE)->BRR  = BIT(7)

void isr_porch(void);
void isr_start(void);
void isr_stop(void);
void isr_update(void);

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, 1);
    pinMode(VGA_R, OUTPUT);
    pinMode(VGA_G, OUTPUT);
    pinMode(VGA_B, OUTPUT);
    pinMode(VGA_V, OUTPUT);
    pinMode(VGA_H, OUTPUT);

    /* Send a message out USART2  */
    Serial2.begin(9600);
    Serial2.println("Video time...");

    
    digitalWrite(VGA_R, 0);
    digitalWrite(VGA_G, 0);
    digitalWrite(VGA_B, 0);
    digitalWrite(VGA_H,1);
    digitalWrite(VGA_V,1);

    timer_set_prescaler(4,0);
    timer_set_mode(4, 1, TIMER_OUTPUTCOMPARE);
    timer_set_mode(4, 2, TIMER_OUTPUTCOMPARE);
    timer_set_mode(4, 3, TIMER_OUTPUTCOMPARE);
    timer_set_mode(4, 4, TIMER_OUTPUTCOMPARE);
    timer_set_reload(4, 2287);
    timer_set_compare_value(4,1,200);
    timer_set_compare_value(4,2,300);
    timer_set_compare_value(4,3,2170);  // 2219 max...
    timer_set_compare_value(4,4,1);
    timer_attach_interrupt(4,1,isr_porch);
    timer_attach_interrupt(4,2,isr_start);
    timer_attach_interrupt(4,3,isr_stop);
    timer_attach_interrupt(4,4,isr_update);

    timer_set_count(4,0);
}

int toggle = 0;
uint16  x = 0;
uint16 y = 0;
uint8 v_active = 1;
GPIO_Port *portb = GPIOB_BASE;

void isr_porch(void) {
    VGA_H_HIGH;
    y++;
    if(y>=523) {
        y=1;
        v_active = 1;
        return;
    }
    if(y>=492) {
        VGA_V_HIGH;
        return;
    }
    if(y>=490) {
        VGA_V_LOW;
        return;
    }
    if(y>=479) {    // 479
        v_active = 0;
        return;
    }
}

uint8 logo[18][16] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,},
    {0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,},
    {0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,},
    {0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,},
    {0,0,1,0,0,1,0,1,0,1,0,0,1,0,0,0,},
    {0,1,0,0,0,0,1,1,1,0,0,0,0,1,0,0,},
    {0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,0,},
    {1,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,},
    {1,0,0,0,0,1,0,1,0,1,0,0,0,0,1,0,},
    {1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,},
    {0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,},
    {0,0,1,1,0,0,0,1,0,0,0,1,1,0,0,0,},
    {0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,},
    {0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, };

void isr_start(void) {
    if(!v_active) { return; }
    VGA_R_HIGH;
    //delayMicroseconds(2);
    //gpio_write_bit(GPIOA_BASE, 8, 1); // VGA_G
    for(x=0; x<32; x++) {
        if(logo[y/28][x/2]) {
            VGA_G_HIGH;
            VGA_B_HIGH;
        } else {
            VGA_G_LOW;
            VGA_B_LOW;
        }
    }

}
void isr_stop(void) {
    if(!v_active) { return; }
    VGA_R_LOW;
    VGA_G_LOW;
    VGA_B_LOW;
}
void isr_update(void) {
    VGA_H_LOW;
}

void loop() {
    /* 
    toggle ^= 1;
    digitalWrite(LED_PIN, toggle);
    delay(100);
    Serial2.println("HIHIHI!");
    */ 
    //for(y=0; y<480; y++) {
   /* 
    for(y=0; y<160; y++) {
        VGA_R_LOW;
        VGA_H_LOW;
        delayMicroseconds(3);
        VGA_H_HIGH;
        VGA_R_HIGH;
        delayMicroseconds(8);
        VGA_G_HIGH;
        delayMicroseconds(10);
        VGA_B_HIGH;
        delayMicroseconds(10);
        VGA_R_LOW;
        VGA_B_LOW;
        VGA_G_LOW;
        //VGA_G_HIGH;
    }
    for(y=0; y<160; y++) {
        VGA_R_LOW;
        VGA_H_LOW;
        delayMicroseconds(3);
        VGA_H_HIGH;
        VGA_G_HIGH;
        delayMicroseconds(8);
        VGA_R_HIGH;
        delayMicroseconds(10);
        VGA_B_HIGH;
        delayMicroseconds(10);
        VGA_R_LOW;
        VGA_B_LOW;
        VGA_G_LOW;
        //VGA_G_HIGH;
    }
    for(y=0; y<160; y++) {
        VGA_R_LOW;
        VGA_H_LOW;
        delayMicroseconds(3);
        VGA_H_HIGH;
        VGA_B_HIGH;
        delayMicroseconds(8);
        VGA_G_HIGH;
        delayMicroseconds(10);
        VGA_R_HIGH;
        delayMicroseconds(10);
        VGA_R_LOW;
        VGA_B_LOW;
        VGA_G_LOW;
        //VGA_G_HIGH;
    }
    for(y=0; y<11; y++) {
        VGA_R_LOW;
        VGA_H_LOW;
        delayMicroseconds(3);
        VGA_R_LOW;
        VGA_H_HIGH;
        delayMicroseconds(28);
    }
    VGA_V_LOW;
    for(y=0; y<2; y++) {
        VGA_R_LOW;
        VGA_H_LOW;
        delayMicroseconds(3);
        VGA_R_LOW;
        VGA_H_HIGH;
        delayMicroseconds(28);
    }
    VGA_V_HIGH;
    for(y=0; y<30; y++) {
        VGA_R_LOW;
        VGA_H_LOW;
        delayMicroseconds(3);
        VGA_R_LOW;
        VGA_H_HIGH;
        delayMicroseconds(28);
    }
    */

}


int main(void) {
    init();
    setup();

    while (1) {
        loop();
    }
    return 0;
}
