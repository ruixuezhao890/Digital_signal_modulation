/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : Mymain.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/27 
*********************************************************************
*********
*/
//
#include "Myapplication.h"
#include "IncludeALL.h"
#include "MySchedule.h"
#include <string>
#define SIZE 256


ESP esp;
MyUsart  testUsart(&huart1);
uint8_t g_wifi_data[SIZE];
uint16_t g_wifi_size=0;
wifiBottom g_wifiBottom;
//���������������ֻ�������ֲ����� ��������ȫ�ַ�����Ҳ�����ַ
static void Task1()//wifi��ʼ�����������
{
    if(esp.myUsart->GetRecv_end_flag()==1) {

        uint8_t *tempdata;
        testUsart.Myprintf("receivedata:\n");
        tempdata = esp.myUsart->Re_GetData();
        g_wifi_size = esp.myUsart->GetRecvLenth();
        testUsart.SendString(esp.myUsart->Re_GetData(), esp.myUsart->GetRecvLenth());

        for (int i = 0; i < esp.myUsart->GetRecvLenth(); ++i) {
            g_wifi_data[i] = tempdata[i];
        }
        testUsart.SendString(g_wifi_data, g_wifi_size);
        g_wifiBottom.Set_ReceiveFlag(1);
        esp.myUsart->ReceiveInit();
        testUsart.Myprintf("wifidataOK\n");
    }

}
static void Task2()//ת��Ϊ������
{

    if (g_wifiBottom.Get_ReceiveFlag()){
        g_wifiBottom.Set_ReceiveFlag(0);
        //testUsart.SendString(g_wifiBottom.GetWIFIReceive(), 20);
        g_wifiBottom.Get_after_the_colon(g_wifi_data,g_wifi_size);
#if test
        testUsart.Myprintf("Dealafter:\n");
        testUsart.SendString(g_wifiBottom.Get_WIFIReceive(), 20);
#endif
        g_wifiBottom.Decimal_to_binary();
        g_wifiBottom.Set_SendFlag(1);
    }

    HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_10);
}
static void Task3()//����
{
    if (g_wifiBottom.Get_SendFlag()) {
        g_wifiBottom.Set_SendFlag(0);
        g_wifiBottom.Signal_transmission();
        testUsart.Myprintf("sendOk\n");
    }
    HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
}
void Mymain()
{
    MySchedule mySchedule;
    MyLCD myLcd;
    myLcd.MyLCDInit();
    myLcd.MyLDshowLable();
    myLcd.MyLCDDrawCoorDinat();
    HAL_TIM_Base_Start_IT(&htim14);
    HAL_TIM_PWM_Start(&htim14,TIM_CHANNEL_1);
    //wifi��ʼ��
    testUsart.Myprintf("wificonnect\n");
    esp.ESP_Init(&huart3);
    esp.WIFIConnect();
    esp.myUsart->ReceiveInit();


    mySchedule.MyScheduleSetPeriod(100);
    mySchedule.MyTaskGreat(Task1,1,50,0);
    mySchedule.MyTaskGreat(Task2,2,50,0);
    mySchedule.MyTaskGreat(Task3,2,100,0);
    for (;;) {
        Task1();
        HAL_Delay_ms(50);
        Task2();
        HAL_Delay_ms(50);
        Task3();
        HAL_Delay_ms(50);
        //mySchedule.MyScheduleWhile();
    }

    /*MyUsart myUsart(&huart1);
    esp.ESP_Init(&huart3);
    esp.WIFIConnect();
   // WIFIDemo();
    esp.myUsart->ReceiveInit();
    for (;;) {
        if (esp.myUsart->GetRECV()==1)
        {
            myUsart.SendString(esp.myUsart->Re_GetData(),esp.myUsart->GetRecvLenth());
            esp.myUsart->ReceiveInit();
        }

    }*/


}
/***************************************************************
  *  @brief     ���ж��ļ����Ե���c++����
  *  @param     ����
  *  @note      ��ע ���˺�������it�ļ�����
  *  @Sample usage:     ������ʹ�÷��� ��ֱ�ӵ���
   * @author     wangzibo
 **************************************************************/

void ItUsart(DMA_HandleTypeDef * hdma_usartx_rx)
{
   esp.myUsart->ReceiveDataCallBack(hdma_usartx_rx);

}
void Uint8_Data_Change(uint8_t * char1,uint8_t* char2)
{
    while (*char2!='\0'){
        * char1= * char2;
        char2++;
        char1++;
    }
}