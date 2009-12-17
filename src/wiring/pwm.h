#ifndef _PWM_H
#define _PWM_H

#ifdef __cplusplus
extern "C"{
#endif

#define PWM           GPIO_MODE_AF_OUTPUT_PP

void pwmWrite(uint8_t, uint16_t);

#ifdef __cplusplus
}
#endif


#endif

