#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#include "stdint.h"
#include "abs_encoder.h"
#include "stdio.h"
#include "math.h"

/*******************************************************************************
** abs_encoder.o : absolute encoder : steve ressler (ressler@vt.edu)
*******************************************************************************/

volatile int abs_read_interrupted;

//void initialize_abs_encoder(struct slug_abs_encoder *abs_encoder)
//{

//  GPIO_InitTypeDef        GPIO_InitStructure;
  
//  /* Enable GPIO clocks */
//  RCC_AHB1PeriphClockCmd(ABSENCODER1_RX_GPIO_CLK | ABSENCODER1_CLK_GPIO_CLK , ENABLE);
//  RCC_AHB1PeriphClockCmd(ABSENCODER0_RX_GPIO_CLK | ABSENCODER0_CLK_GPIO_CLK , ENABLE);

//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;

  /* ABS Enc RX pin configuration */
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//  GPIO_InitStructure.GPIO_Pin = ABSENCODER1_RX_PIN;
//  GPIO_Init(ABSENCODER1_RX_GPIO_PORT, &GPIO_InitStructure);
  
//  GPIO_InitStructure.GPIO_Pin = ABSENCODER0_RX_PIN;
//  GPIO_Init(ABSENCODER0_RX_GPIO_PORT, &GPIO_InitStructure);
  
  /* ABS Enc CLK configuration */
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_Pin =  ABSENCODER1_CLK_PIN;
//  GPIO_Init(ABSENCODER1_CLK_GPIO_PORT, &GPIO_InitStructure);
  
//  GPIO_InitStructure.GPIO_Pin =  ABSENCODER0_CLK_PIN;
//  GPIO_Init(ABSENCODER0_CLK_GPIO_PORT, &GPIO_InitStructure);
 
  
//}

#define PI 3.1415927

void delay(uint32_t value)
{
  uint32_t i = 0;
  
  while(i<value)
  {
    i++;
    asm (""); // keeps this code from being optimized away
  }
  
  
}



int16_t abs_encoder_read(int motor)
{
  uint32_t i = 0;
  int16_t position = 0;
  
  abs_read_interrupted = 0;
  
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);//ABS_ENC1_CLOCK_SET();

    
  delay(2);
  
  for(i=0; i<15; i++)
  {
	  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_7);//ABS_ENC1_CLOCK_TOGGLE();
      
    delay(22);
    
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_7);//ABS_ENC1_CLOCK_TOGGLE();

      
    delay(22);

    //position |= (ABS_ENC1_READ_RX() << (14-i));
    position |= (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_6) << (14-i));
    
  }

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);//ABS_ENC1_CLOCK_SET();

  if(abs_read_interrupted == 1)
    return 0xFFFF;
  else
    return position;
}

float abs_encoder_to_joint_position(int16_t enc_reading, int motor)
{
  //float gain = od_get_joint_position_sensor_gain(motor);
  int16_t position = enc_reading;// - od_get_joint_position_sensor_offset(motor);
  float joint_position = position;//*gain - od_get_joint_position_sensor_bias(motor);

  joint_position = fmod(joint_position, (2*PI));
  if(joint_position > PI)
  {
    joint_position -= 2*PI;
  }
  else if(joint_position < -PI)
  {
    joint_position += 2*PI;
  }
  return joint_position;
}




