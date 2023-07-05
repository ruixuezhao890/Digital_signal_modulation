/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MyADC_cpp.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/27 
*********************************************************************
*********
*/
//

#ifndef TEMPLATEDEVELOPMENT_MYADC_CPP_H
#define TEMPLATEDEVELOPMENT_MYADC_CPP_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "Myapplication.h"
//#include "IncludeALL.h"
#include "MyUsart.h"
#include "MyLCD.h"
/*______________________类的声明在这下面________________:*/
class MyADC {
public:
    MyADC(ADC_HandleTypeDef *hadc);
    MyADC( uint16_t * adcNum,uint16_t Size,TIM_HandleTypeDef *htim, ADC_HandleTypeDef *hadc);
    void myADCInit(TIM_HandleTypeDef *htim);

    void myADCCollectData();

   // void myADCDataSend();

    void myADCCompareTheSize();

    void myADCShowWaveForm();

    float myADCGetADCValue();
    ~MyADC();
    uint16_t MaxValue = 0;
    uint16_t MinValue = 5000;
private:

    ADC_HandleTypeDef *hadc;
    uint16_t *ADCStorageBuff;
    uint16_t ADCStorageBuffSize;

};
#ifdef __cplusplus
}
#endif


#endif //TEMPLATEDEVELOPMENT_MYADC_CPP_H
