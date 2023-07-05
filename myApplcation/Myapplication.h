/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : Myapplication.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/27 
*********************************************************************
*********
*/
//

#ifndef TEMPLATEDEVELOPMENT_MYAPPLICATION_H
#define TEMPLATEDEVELOPMENT_MYAPPLICATION_H
#ifdef __cplusplus
extern "C"
{
#endif
    /*---------------------c-----------------*/
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "dac.h"
#include "adc.h"

#include "tim.h"

#include "string.h"
#include "stdio.h"
#include "lcd.h"
#include "touch.h"
#include "arm_math.h"
#include "arm_common_tables.h"
#include "arm_const_structs.h"
//#include "ILI93xx.h"
#define test 1
void Mymain();
void ItUsart(DMA_HandleTypeDef * hdma_usartx_rx);
void Uint8_Data_Change(uint8_t * char1,uint8_t* char2);
#ifdef __cplusplus
}
/*-------------c++-------------*/

/*#include "LED.h"
#include "MyADC_cpp.h"
#include "MyUsart.h"*/
#endif
#endif //TEMPLATEDEVELOPMENT_MYAPPLICATION_H
