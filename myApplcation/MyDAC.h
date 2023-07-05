/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MyDAC.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/5/4 
*********************************************************************
*********
*/
//

#ifndef CPROJECT_MYDAC_H
#define CPROJECT_MYDAC_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "Myapplication.h"
/*______________________类的声明在这下面________________:*/
class MyDAC{
public:
    MyDAC(DAC_HandleTypeDef* hdac, uint32_t Channel,TIM_HandleTypeDef *htim);
    MyDAC(DAC_HandleTypeDef* hdac, uint32_t Channel);
    void MyDACSetValue(uint32_t Data);
    void MyDACStart();
    void MyDACStop();
    void MyDACStartDMA(uint32_t* Data,uint32_t Length);
    void MyDACStopDMA(uint32_t* Data,uint32_t Length);
    uint32_t MyDACGetDACSetValue();
private:
    uint32_t DACSetValue;
    DAC_HandleTypeDef* hdac;
    uint32_t Channel;
};
#ifdef __cplusplus
}
#endif
#endif //CPROJECT_MYDAC_H
