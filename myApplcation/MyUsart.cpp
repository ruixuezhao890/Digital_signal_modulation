/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : myUsart.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/27 
*********************************************************************
*********
*/
//

#include <cstdarg>
#include "MyUsart.h"

MyUsart::MyUsart()
{

}
MyUsart::MyUsart(UART_HandleTypeDef *huart)
{
    this->huart=huart;
}
MyUsart::MyUsart(uint16_t Enable,UART_HandleTypeDef *huart)
{
    this->huart=huart;
    this->ReceiveInit();
}
void MyUsart::ReceiveInit()
{
    for (int i = 0; i < RELENTH; ++i) {
        re_Buff[i]=' ';
    }

    __HAL_UART_ENABLE_IT(this->huart, UART_IT_IDLE);//使能idle中断
    HAL_UART_Receive_DMA(this->huart, re_Buff, RELENTH);
}
void MyUsart::Send(uint8_t * sendBuf)
{
    HAL_UART_Transmit(huart,sendBuf,sizeof(sendBuf)+1,50);
}

void MyUsart::SendString(uint8_t * stringBuf,uint16_t Length)
{
    HAL_UART_Transmit(huart,stringBuf,Length,50);
    HAL_UART_Transmit(huart,(uint8_t *)"\n",2,50);
}
void MyUsart::SendString(const char* stringBuf,uint16_t Length)
{
    HAL_UART_Transmit(huart,(uint8_t *)stringBuf,Length,50);
    HAL_UART_Transmit(huart,(uint8_t *)"\n",2,50);
}

void MyUsart::SendOneInt(uint16_t IntBuf)
{
    char temp[RELENTH]={0};
    sprintf(temp,"%d\n",IntBuf);
    Send((uint8_t *)temp);
}
void MyUsart::SendInt(uint16_t* IntBuf,uint16_t Length)
{
    char temp[RELENTH]={0};
    for (int i = 0; i < Length; ++i) {
        sprintf(temp,"%d\n",IntBuf[i]);
        Send((uint8_t *)temp);
//        Send("\n",huart);
    }
}
void MyUsart::SendOneFloat(float FloatBuf)
{
    char temp[RELENTH]={0};
    sprintf(temp,"%f\n",FloatBuf);
    Send((uint8_t *)temp);
//    SendString("\n",huart);
}
void MyUsart::SendFloat(float* FloatBuf,uint16_t Length)
{
    char temp[RELENTH]={0};
    for (int i = 0; i < Length; ++i) {
        sprintf(temp,"%lf",FloatBuf[i]);
        Send((uint8_t *)temp);
        SendString((uint8_t *)"\n",2);
    }
}

//放入"stm32f4xx_it.c文件中USARTx_IRQHandler(void)内
void MyUsart::ReceiveDataCallBack(DMA_HandleTypeDef * hdma_usartx_rx)
{
    uint32_t tmp_flag = 0;
    uint32_t temp;
    tmp_flag =__HAL_UART_GET_FLAG(this->huart,UART_FLAG_IDLE); //获取IDLE标志位
    if((tmp_flag != RESET))//idle标志被置位
    {
        __HAL_UART_CLEAR_IDLEFLAG(this->huart);//清除标志位
        temp = huart->Instance->SR;  //清除状态寄存器SR,读取SR寄存器可以实现清除SR寄存器的功能
        temp = huart->Instance->DR; //读取数据寄存器中的数据
        HAL_UART_DMAStop(this->huart); //
        temp  = __HAL_DMA_GET_COUNTER(hdma_usartx_rx); // 获取DMA中未传输的数据个数，NDTR寄存器分析见下面
        re_len = RELENTH - temp; //总计数减去未传输的数据个数，得到已经接收的数据个数
        recv_end_flag = 1;	// 接受完成标志位置1
    }
}
void MyUsart::SendReceive()
{
    if(recv_end_flag ==1)
    {
        HAL_UART_DMAStop(huart);

        //打印接收数据
        HAL_UART_Transmit(huart, re_Buff, re_len, 50);

        for(uint8_t i=0; i < re_len; i++)
        {
            re_Buff[i]=0;//清接收缓存
        }
        re_len=0;//清除计数
        recv_end_flag=0;//清除接收结束标志位
    }

    HAL_UART_Receive_DMA(this->huart, re_Buff, RELENTH);
}
MyUsart::~MyUsart() {

}

void MyUsart::SendCmdOut(char * fmt, ...) {
    va_list ap;
    uint16_t len;

    va_start(ap, fmt);
    vsprintf((char *)tx_Buff, fmt, ap);
    va_end(ap);

    len = strlen((const char *)tx_Buff);
    HAL_UART_Transmit(this->huart, tx_Buff, len, HAL_MAX_DELAY);
}

uint8_t *MyUsart::Re_GetData() {
    if (this->recv_end_flag==1)
    {
        this->recv_end_flag=0;
        return this->re_Buff;
    }
    else
    {
        return NULL;
    }

}

uint8_t *MyUsart::ReceiveAgain() {

    HAL_UART_Receive_DMA(this->huart, re_Buff, RELENTH);
    for (int i = 0; i < RELENTH; ++i) {
        temp[i]=re_Buff[i];
        re_Buff[i]=' ';
    }
    return temp;

}

uint8_t MyUsart::GetRECV() {
    return this->recv_end_flag;
}

uint8_t MyUsart::GetRecvLenth() {
    return this->re_len;
}

void MyUsart::Myprintf(char *fmt, ...) {
    va_list ap;
    uint16_t len;

    va_start(ap, fmt);
    vsprintf((char *)tx_Buff, fmt, ap);
    va_end(ap);

    len = strlen((const char *)tx_Buff);
    HAL_UART_Transmit(this->huart, tx_Buff, len, HAL_MAX_DELAY);
}

uint8_t MyUsart::GetRecv_end_flag() {
    return this->recv_end_flag;
}

