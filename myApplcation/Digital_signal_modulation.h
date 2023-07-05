/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : WiFiBottomLayer.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/7/2 
*********************************************************************
*********
*/
//

#ifndef CPROJECT_DIGITAL_SIGNAL_MODULATION_H
#define CPROJECT_DIGITAL_SIGNAL_MODULATION_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "Myapplication.h"
#include "IncludeALL.h"
#include "tim.h"

#define WIFI_Level_GPIO_PORT           GPIOE
#define WIFI_Level_GPIO_PIN            GPIO_PIN_1
#define WIFI_Level_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0) /* PE口时钟使能 */
#define WIFI_contorl(x)  do{x? \
                            HAL_GPIO_WritePin(WIFI_Level_GPIO_PORT, WIFI_Level_GPIO_PIN, GPIO_PIN_SET) :\
                            HAL_GPIO_WritePin(WIFI_Level_GPIO_PORT, WIFI_Level_GPIO_PIN, GPIO_PIN_RESET); \
                            }while(0)
/*______________________类的声明在这下面________________:*/
class wifiBottom{
public:
    wifiBottom();
    void Pilot_code();
    void Zero_signal();
    void One_signal();
    void Final_code();
    void Get_after_the_colon(uint8_t * Reveive,uint16_t num);
    void Set_ReceiveFlag(uint16_t flag);
    void Set_SendFlag(uint16_t flag);
    void Decimal_to_binary();
    void Signal_transmission();
    uint16_t Get_ReceiveFlag();
    uint16_t Get_SendFlag();
    uint8_t* Get_WIFIReceive();
    ~wifiBottom();
private:

//    uint16_t (*p)[8];

    MyUsart* WIFIUsrat;
    uint16_t ReceiveFlag;
    uint16_t SendFlag;
    uint8_t  WIFIReceive[200]="0";
    uint16_t WIFIReceiveSize;
};
#ifdef __cplusplus
}
#endif
#endif //CPROJECT_DIGITAL_SIGNAL_MODULATION_H
