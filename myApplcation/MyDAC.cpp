/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MyDAC.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/5/4 
*********************************************************************
*********
*/
//

#include "MyDAC.h"
MyDAC::MyDAC(DAC_HandleTypeDef* hdac, uint32_t Channel,TIM_HandleTypeDef *htim)
{
    this->hdac=hdac;
    this->Channel=Channel;
    this->DACSetValue=0;
    HAL_TIM_Base_Start(htim);
}
MyDAC::MyDAC(DAC_HandleTypeDef *hdac, uint32_t Channel) {
    this->hdac=hdac;
    this->Channel=Channel;
    this->DACSetValue=0;
}
//Ä¬ÈÏÓÒ¶ÔÆë
void MyDAC::MyDACSetValue(uint32_t Data) {

    HAL_DAC_SetValue(this->hdac, this->Channel,DAC_ALIGN_12B_R,Data);
}

void MyDAC::MyDACStart() {
    HAL_DAC_Start(this->hdac, this->Channel);
}

void MyDAC::MyDACStop() {
    HAL_DAC_Stop(this->hdac, this->Channel);
}

void MyDAC::MyDACStartDMA(uint32_t* Data,uint32_t Length) {
    HAL_DAC_Start_DMA(this->hdac,this->Channel,Data,Length,DAC_ALIGN_12B_R);
}

void MyDAC::MyDACStopDMA(uint32_t* Data,uint32_t Length) {
    HAL_DAC_Start_DMA(this->hdac,this->Channel,Data,Length,DAC_ALIGN_12B_R);
}

 uint32_t MyDAC::MyDACGetDACSetValue() {
    this->DACSetValue= HAL_DAC_GetValue(this->hdac,this->Channel);
     return this->DACSetValue;
}
