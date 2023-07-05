/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : seriall_Port.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/26 
*********************************************************************
*********
*/
//

#ifndef TEMPLATEDEVELOPMENT_SERIALL_PORT_H
#define TEMPLATEDEVELOPMENT_SERIALL_PORT_H
#include "main.h"
#include "stdio.h"
#include "usart.h"
#define RELENTH 256
#include "string.h"
void ReceiveInit();
void Send(uint8_t * sendBuf,UART_HandleTypeDef *huart);
void SendString(uint8_t * stringBuf,uint16_t Length,UART_HandleTypeDef *huart);
void SendOneInt(uint16_t IntBuf,UART_HandleTypeDef *huart);
void SendInt(uint16_t* IntBuf,uint16_t Length,UART_HandleTypeDef *huart);
void SendOneFloat(float FloatBuf,UART_HandleTypeDef *huart);
void SendFloat(float * FloatBuf,uint16_t Length,UART_HandleTypeDef *huart);
void ReceiveDataCallBack(DMA_HandleTypeDef * hdma_usart1_rx);
void SendReceive(UART_HandleTypeDef *huart);
#endif //TEMPLATEDEVELOPMENT_SERIALL_PORT_H
