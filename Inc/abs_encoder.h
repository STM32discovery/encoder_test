#ifndef _ABS_ENCODER_H_
#define _ABS_ENCODER_H_

#include "stm32f4xx_hal_gpio.h"

/*******************************************************************************
** abs_encoder.o : absolute encoder : steve ressler (ressler@vt.edu)
*******************************************************************************/

/*
    Notes:
    ------

    Usage:
    ------

*/


/* ABSENCODERx  Interface */
/*
#define ABSENCODER1_RX_PIN                GPIO_Pin_6
#define ABSENCODER1_RX_GPIO_PORT          GPIOD
#define ABSENCODER1_RX_GPIO_CLK           RCC_AHB1Periph_GPIOD

#define ABSENCODER1_CLK_PIN               GPIO_Pin_7
#define ABSENCODER1_CLK_GPIO_PORT         GPIOD
#define ABSENCODER1_CLK_GPIO_CLK          RCC_AHB1Periph_GPIOD
*/

#define ABS_ENC1_CLOCK_TOGGLE()            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_7)
#define ABS_ENC1_CLOCK_RESET()             HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET)
#define ABS_ENC1_CLOCK_SET()               HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET)
#define ABS_ENC1_READ_RX()                 HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_6)

struct slug_abs_encoder {
  uint8_t placeholder;
};


void initialize_abs_encoder(struct slug_abs_encoder *);

float abs_encoder_to_joint_position(int16_t enc_reading, int motor);


int16_t abs_encoder_read(int motor);




#endif
