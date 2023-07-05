/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MyADC_cpp.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/27 
*********************************************************************
*********
*/
//


#include "MyADC_cpp.h"
MyADC::MyADC(ADC_HandleTypeDef *hadc) {
    this->hadc=hadc;
}
MyADC::MyADC( uint16_t * adcNum,uint16_t Size,TIM_HandleTypeDef *htim, ADC_HandleTypeDef *hadc) {
    ADCStorageBuff=adcNum;
    ADCStorageBuffSize=Size;
    this->hadc=hadc;
    this->myADCInit(htim);

}
void MyADC::myADCInit(TIM_HandleTypeDef *htim)
{
    HAL_TIM_Base_Start(htim);
}

void MyADC::myADCCollectData()
{

    HAL_ADC_Start_DMA(hadc,(uint32_t *)ADCStorageBuff,ADCStorageBuffSize);

}
//void MyADC::myADCDataSend()
//{
//    usart->SendInt(ADCStorageBuff,ADCStorageBuffSize);
//}

//需要在调用前延迟100
void MyADC::myADCCompareTheSize()
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
    float vmax=MaxValue*3.3/4096;
    float vmin=MinValue*3.3/4096;
    float vpp=(MaxValue-MinValue)*3.3/4096;
    lcd_show_float(60, 88, vpp,16,0,RED);//VPP峰峰值
    lcd_show_float(60, 48, vmax,  16, 0, RED);//最大值
    lcd_show_float(60, 68, vmin,  16, 0, RED);//最小值


}

void MyADC::myADCShowWaveForm() {

    uint16_t past_vol1 = 0, pre_vol1 = 0;
    uint16_t past_vol = 0, pre_vol = 0;
    for (uint16_t x = 0,sum=0; x < 799; x=x+8,sum++)
    {
        if (sum<ADCStorageBuffSize) {
            pre_vol = ADCStorageBuff[sum] * (3.3 / 4096) * 60;
            //pre_vol1 = adcBuff2[x] * (3.3 / 4096) * 60;
            lcd_draw_line(x, 250, x, 480, WHITE);//刷新背景
            lcd_draw_bline(x, past_vol + 260, x +8, pre_vol + 260, 1, RED);
            //lcd_draw_bline(x, past_vol1 + 280, x + 1, pre_vol1 + 280, 1, RED);
            //past_vol1 = pre_vol1;
            past_vol = pre_vol;
        }
    }
}
MyADC::~MyADC()
{

}

float MyADC::myADCGetADCValue() {
    HAL_ADC_Start(this->hadc);  //开启ADC（阻塞模式）
    HAL_ADC_PollForConversion(this->hadc,50);   //查看规则通道组是否完成转换
    if(HAL_IS_BIT_SET(HAL_ADC_GetState(this->hadc),HAL_ADC_STATE_REG_EOC)){  //查看ADC状态是否为EOC
        return (float)HAL_ADC_GetValue(this->hadc)/4096.0*3.3;  //读取并处理数据
    }
    else return 0;

}


