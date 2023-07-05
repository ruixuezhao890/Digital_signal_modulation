 /**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : WiFiBottomLayer.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/7/2 
*********************************************************************
*********
*/
//

#include "Digital_signal_modulation.h"
#include <deque>
std::deque<uint16_t> *wifiStack;
wifiBottom::wifiBottom() {
    GPIO_InitTypeDef  wifiBottom;
    WIFI_Level_GPIO_CLK_ENABLE();
    wifiBottom.Pull=GPIO_PULLUP;
    wifiBottom.Speed=GPIO_SPEED_FREQ_VERY_HIGH;
    wifiBottom.Mode=GPIO_MODE_OUTPUT_PP;
    wifiBottom.Pin=WIFI_Level_GPIO_PIN;
    HAL_GPIO_Init(WIFI_Level_GPIO_PORT,&wifiBottom);
	WIFI_contorl(0);

    this->WIFIUsrat=new MyUsart(&huart1);

}



wifiBottom::~wifiBottom() {
    delete this->WIFIUsrat;
}

void wifiBottom::Pilot_code() {
//    for (int i = 0; i < num; ++i) {
        WIFI_contorl(1);
        HAL_Delay_ms(40);
        WIFI_contorl(0);
        HAL_Delay_ms(10);

}
 void wifiBottom::Final_code() {
     WIFI_contorl(1);
     HAL_Delay_ms(10);
     WIFI_contorl(0);
     HAL_Delay_ms(40);
 }
void wifiBottom::Zero_signal() {
        WIFI_contorl(1);
        HAL_Delay_ms(20);
        WIFI_contorl(0);
        HAL_Delay_ms(30);

}

void wifiBottom::One_signal() {
        WIFI_contorl(1);
        HAL_Delay_ms(30);
        WIFI_contorl(0);
        HAL_Delay_ms(20);

}

void wifiBottom::Get_after_the_colon(uint8_t * Reveive,uint16_t num) {
    int k=0;
    int j=0;

    for (int i = 0; i < num; ++i) {
        if (Reveive[i]==58){
            k=i+1;
            break;
        }
    }
    if (k) {
        for (;k < num; ++k) {
            this->WIFIReceive[j] =Reveive[k];
            j++;
        }
    }
    else{
        for (j= 0; j < num; ++j) {
            this->WIFIReceive[j] =Reveive[j];
        }
    }
    this->WIFIReceiveSize= j;
//    this->p= new uint16_t [this->WIFIReceiveSize][8];

}



void wifiBottom::Set_ReceiveFlag(uint16_t flag) {
    if (flag<2)
    this->ReceiveFlag=flag;
}

uint16_t wifiBottom::Get_ReceiveFlag() {
    return this->ReceiveFlag;
}

uint8_t* wifiBottom::Get_WIFIReceive() {
    return this->WIFIReceive;
}

void wifiBottom::Decimal_to_binary() {
    int temp=0;

    wifiStack=new std::deque<uint16_t>[this->WIFIReceiveSize];
    for (int i = 0; i < this->WIFIReceiveSize; ++i) {
        temp=this->WIFIReceive[i];
        while (temp){
            wifiStack[i].push_back(temp%2);
            temp=temp/2;
        }
        if (8%wifiStack[i].size()!=0){//补零
            for (int j = 0; j <= (8 - wifiStack[i].size()); ++j) {
                wifiStack[i].push_back(0);
            }
        }
    }
//    for (int i = 0; i < this->WIFIReceiveSize; ++i) {
//        int index=0;
//        for (std::deque<uint16_t>::const_iterator it=wifiStack[i].begin();it !=wifiStack[i].end();it++) {
//          this->p[i][index]=*it;
//          index++;
//        }
//
//    }
#if test
    WIFIUsrat->Myprintf("test:\n");
    for (int i = 0; i < this->WIFIReceiveSize; ++i) {
        for (std::deque<uint16_t>::const_iterator it=wifiStack[i].begin();it !=wifiStack[i].end();it++) {
          WIFIUsrat->Myprintf("%d:%d\n",i,*it);
        }
        WIFIUsrat->Myprintf("\n");
        }
#endif
}

//信号发送
void wifiBottom::Signal_transmission() {
    int cnt=0;
    for (int i = 0; i < this->WIFIReceiveSize; ++i) {
        if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)) {
            this->Pilot_code();
            for (std::deque<uint16_t>::const_iterator it = wifiStack[i].begin(); it != wifiStack[i].end(); it++) {
                HAL_Delay_ms(1);//让系统反应一下 速度过快会丢包
                if (*it) {
                    this->One_signal();
                } else {
                    this->Zero_signal();
                }
            }
            /*for (int j = 0; j < 8; ++j) {
                HAL_Delay_ms(1);//让系统反应一下 速度过快会丢包
                if (this->p[i][j]){
                    this->One_signal();
                }
                else{
                    this->Zero_signal();
                }
            }*/
            WIFI_contorl(0);
        }
        //WIFIUsrat->Myprintf("usrat\n");
    }
    this->Final_code();
    delete []wifiStack;

}

void wifiBottom::Set_SendFlag(uint16_t flag) {
    if (flag<2)
        this->SendFlag=flag;
}

uint16_t wifiBottom::Get_SendFlag() {
    return this->SendFlag;
}


