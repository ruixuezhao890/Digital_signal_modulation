/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : myAdc.c
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/26 
*********************************************************************
*********
*/
//

#include "myAdc.h"
uint16_t * ADCStorageBuff;
uint16_t ADCStorageBuffSize;
uint16_t MaxValue=0;
uint16_t MinValue=5000;
void myADCInit(TIM_HandleTypeDef *htim)
{
    HAL_TIM_Base_Start(htim);
}

void myADCCollectData(ADC_HandleTypeDef *hadc,uint16_t * adcNum,uint16_t Size)
{
    ADCStorageBuff=adcNum;
    ADCStorageBuffSize=Size;
    HAL_ADC_Start_DMA(hadc,(uint32_t *)adcNum,Size);
}
void myADCDataSend()
{
    SendInt(ADCStorageBuff,ADCStorageBuffSize,&huart1);
}

void myADCCompareTheSize()
{
    for (int i = 0; i < ADCStorageBuffSize; ++i) {
        if (MaxValue < ADCStorageBuff[i]) {
            MaxValue = ADCStorageBuff[i];
        }
    }
    for (int i = 0; i < ADCStorageBuffSize; ++i){
        if (MinValue>ADCStorageBuff[i])
        {
            MinValue=ADCStorageBuff[i];
        }
    }
    SendString("Max",3,&huart1);
    SendOneInt(MaxValue,&huart1);
    SendString("Min",3,&huart1);
    SendOneInt(MinValue,&huart1);

}
