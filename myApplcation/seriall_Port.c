/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : seriall_Port.c
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/26 
*********************************************************************
*********
*/
//

#include "seriall_Port.h"
 uint8_t    re_len=0;
 uint8_t    recv_end_flag=0;
uint8_t     re_Buff[200];
//先使用初始化
void ReceiveInit()
{
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);//使能idle中断
    HAL_UART_Receive_DMA(&huart1, re_Buff, RELENTH);
}

void SendReceive(UART_HandleTypeDef *huart)
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

    HAL_UART_Receive_DMA(&huart1, re_Buff, RELENTH);
}
void Send(uint8_t * sendBuf,UART_HandleTypeDef *huart)
{

    HAL_UART_Transmit(huart,sendBuf,sizeof(sendBuf)+1,50);

}

void SendString(uint8_t * stringBuf,uint16_t Length,UART_HandleTypeDef *huart)
{

    HAL_UART_Transmit(huart,stringBuf,Length,50);
    HAL_UART_Transmit(huart,"\n",sizeof("\n"),50);
}

void SendOneInt(uint16_t IntBuf,UART_HandleTypeDef *huart)
{
    char temp[RELENTH]={0};
    sprintf(temp,"%d\n",IntBuf);
    Send((uint8_t *)temp,huart);
//    Send("\n",huart);
}
void SendInt(uint16_t* IntBuf,uint16_t Length,UART_HandleTypeDef *huart)
{
    char temp[RELENTH]={0};
    for (int i = 0; i < Length; ++i) {
        sprintf(temp,"%d\n",IntBuf[i]);
        Send((uint8_t *)temp,huart);
//        Send("\n",huart);
    }


}
void SendOneFloat(float FloatBuf,UART_HandleTypeDef *huart)
{
    char temp[RELENTH]={0};
    sprintf(temp,"%f\n",FloatBuf);
    Send(temp,huart);
//    SendString("\n",huart);
}
void SendFloat(float * FloatBuf,uint16_t Length,UART_HandleTypeDef *huart)
{
    char temp[RELENTH]={0};
    for (int i = 0; i < Length; ++i) {
        sprintf(temp,"%f",FloatBuf[i]);
        Send(temp,huart);
        SendString("\n",2,huart);
    }
}
//放入"stm32f4xx_it.c文件中USART1_IRQHandler(void)内
void ReceiveDataCallBack(DMA_HandleTypeDef*  hdma_usart1_rx)
{
    uint32_t tmp_flag = 0;
    uint32_t temp;
    tmp_flag =__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE); //获取IDLE标志位
    if((tmp_flag != RESET))//idle标志被置位
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart1);//清除标志位
        temp = huart1.Instance->SR;  //清除状态寄存器SR,读取SR寄存器可以实现清除SR寄存器的功能
        temp = huart1.Instance->DR; //读取数据寄存器中的数据
        HAL_UART_DMAStop(&huart1); //
        temp  = __HAL_DMA_GET_COUNTER(hdma_usart1_rx); // 获取DMA中未传输的数据个数，NDTR寄存器分析见下面
        re_len = RELENTH - temp; //总计数减去未传输的数据个数，得到已经接收的数据个数
        recv_end_flag = 1;	// 接受完成标志位置1
    }
}

