/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : myAdc.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/26 
*********************************************************************
*********
*/
//

#ifndef TEMPLATEDEVELOPMENT_MYADC_H
#define TEMPLATEDEVELOPMENT_MYADC_H
#include "main.h"
#include "seriall_Port.h"
#include "adc.h"
#include "tim.h"

void myADCInit(TIM_HandleTypeDef *htim);
void myADCCollectData(ADC_HandleTypeDef *hadc,uint16_t * adcNum,uint16_t Size);
void myADCDataSend();
void myADCCompareTheSize();
#endif //TEMPLATEDEVELOPMENT_MYADC_H
