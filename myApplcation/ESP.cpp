/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : ESP.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/5/14 
*********************************************************************
*********
*/
 //

#include "ESP.h"
#include "MyUsart.h"
MyUsart myUsart1(&huart1);
void ESP::ESP_Init(UART_HandleTypeDef *huart) {
    GPIO_InitTypeDef WIFIGPIO_Struct;
    ESP_RST_GPIO_CLK_ENABLE();
    WIFIGPIO_Struct.Pin=ESP_RST_GPIO_PIN;
    WIFIGPIO_Struct.Mode=GPIO_MODE_OUTPUT_PP;
    WIFIGPIO_Struct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ESP_RST_GPIO_PORT,&WIFIGPIO_Struct);
    this->myUsart=new MyUsart(1,huart);
}

void ESP::ESP_hw_reset(void) {
    ESP_RST(0);
    HAL_Delay(100);
    ESP_RST(1);
    HAL_Delay(500);
}

uint8_t ESP::ESP_send_at_cmd(char *cmd, char *ack, uint32_t timeout) {

    uint8_t * ret=NULL;
    myUsart->ReceiveInit();
    myUsart->SendCmdOut("%s\r\n",cmd);
    //HAL_Delay(5);
    if (ack==NULL||timeout==0)
    {
        return ESP_EOK;
    }
    else
    {
        while (timeout>0)
        {
            //myUsart->ReceiveInit();
            ret=myUsart->Re_GetData();

            if (ret!=NULL) {
                if (strstr((const char *) ret, ack) != NULL) {
                    return ESP_EOK;
                } else {
                    myUsart->ReceiveInit();
                    myUsart->SendCmdOut("%s\r\n",cmd);
                }
            }
            timeout--;
            HAL_Delay(1);
        }
        return ESP_ETIMEOUT;
    }

}

uint8_t ESP::ESP_init(uint32_t baudrate) {
    return 0;
}

uint8_t ESP::ESP_restore(void) {
    uint8_t ret;
    ret= ESP_send_at_cmd("AT+RESTORE","ready",3000);
    //myUsart1.SendString(this->myUsart->Re_GetData(),200);
    if (ret==ESP_EOK)
    {

        return ESP_EOK;
    }

    return ESP_ERROR;
}

uint8_t ESP::ESP_at_test(void) {
    uint8_t ret;
    uint8_t i;

    for (i=0; i<10; i++)
    {
        ret = ESP_send_at_cmd("AT", "OK", 500);
        if (ret == ESP_EOK)
        {
            return ESP_EOK;
        }
    }

    return ESP_ERROR;


}

/***************************************************************
  *  @brief     设置工作模式
  *  @param     mode：1 station模式 2 ap模式 3 ap+station模式
  *  @note      备注 ：无
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author     wangzibo
 **************************************************************/

uint8_t ESP::ESP_set_mode(uint8_t mode) {
    uint8_t ret;
    switch (mode) {
        case 1:
        {
            ret= ESP_send_at_cmd("AT+CWMODE=1","OK",500);//station
            break;
        }
        case 2:
        {
            ret= ESP_send_at_cmd("AT+CWMODE=2","OK",500);//ap
            break;
        }

        case 3: {
            ret= ESP_send_at_cmd("AT+CWMODE=3","OK",500);//ap+station
            break;
        }
        default:
        {
            return ESP_EINVAL;
        }
    }
    if (ret==ESP_EOK)
    {
        return ESP_EOK;
    }else
    {
        return ESP_ERROR;
    }
}

/***************************************************************
  *  @brief     软件复位
  *  @param     参数
  *  @note      备注 ：无
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author     wangzibo
 **************************************************************/

uint8_t ESP::ESP_sw_reset(void) {
    uint8_t ret;
    ret= ESP_send_at_cmd("AT+RST","OK",500);
    if (ret==ESP_EOK)
    {
        return ESP_EOK;
    }
    else
    return ESP_ERROR;
}

/***************************************************************
  *  @brief     设置回显
  *  @param     cfg：0 关闭
  *                  1 打开
  *  @note      备注 ：无
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author     wangzibo
 **************************************************************/

uint8_t ESP::ESP_ate_config(uint8_t cfg) {
    uint8_t ret;
    switch (cfg) {
        case 0:{
            ret= ESP_send_at_cmd("ATE0","OK",500);
            break;
        }
        case 1:{
            ret= ESP_send_at_cmd("ATE1","OK",500);
        }
        default:
        {
            return ESP_EINVAL;
        }
    }
    if (ret==ESP_EOK)
    {
        return ESP_EOK;
    }
    else
    {
        return ESP_ERROR;
    }

}
/***************************************************************
  *  @brief     加入WiFi
  *  @param     ssid：WiFi名称 pwd：WiFi密码
  *  @note      备注 ：无
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author     wangzibo
 **************************************************************/

uint8_t ESP::ESP_join_ap(char *ssid, char *pwd) {
    uint8_t ret;
    char cmd[128];
    ESP_send_at_cmd("AT+CWJAP","OK",100);
    sprintf(cmd,"AT+CWJAP=\"%s\",\"%s\"",ssid,pwd);

    ret= ESP_send_at_cmd(cmd,"WIFI GOT IP",10000);
    //myUsart1.SendString(this->myUsart->Re_GetData(),400);
    if (ret==ESP_EOK)
    {
        return ESP_EOK;
    }
    else
    {
        return ESP_ERROR;
    }
}

uint8_t ESP::ESP_get_ip(char *buf) {
    uint8_t ret;
    char *p_start;
    char *p_end;

    ret = ESP_send_at_cmd("AT+CIFSR", "OK", 500);
    if (ret !=ESP_EOK)
    {
        return ESP_ERROR;
    }

    p_start = strstr((const char *)this->myUsart->Re_GetData(), "\"");
    p_end = strstr(p_start + 1, "\"");
    *p_end = '\0';
    sprintf(buf, "%s", p_start + 1);

    return ESP_EOK;
}
/***************************************************************
  *  @brief     链接TCP服务器
  *  @param     server_ip：TCP服务器的IP
  *             server_port:TCP服务器的端口
  *  @note      备注 ：无
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author     wangzibo
 **************************************************************/

uint8_t ESP::ESP_connect_tcp_server(char *server_ip, char *server_port) {
    uint8_t ret;
    char cmd[64];
    sprintf(cmd, "AT+CIPSTART=\"TCP\",\"%s\",%s", server_ip, server_port);
    ret= ESP_send_at_cmd(cmd,"CONNECT",5000);
    if (ret==ESP_EOK)
    {
        return ESP_EOK;
    }
    else
    {
        return ESP_ERROR;
    }

}
/***************************************************************
  *  @brief     开启透传
  *  @param     参数
  *  @note      备注 ：无
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author     wangzibo
 **************************************************************/

uint8_t ESP::ESP_enter_unvarnished(void) {
   uint8_t ret;
   ret= ESP_send_at_cmd("AT+CIPMODE=1","OK",500);
   ret= ESP_send_at_cmd("AT+CIPSEND", ">", 500);
    if (ret==ESP_EOK)
    {
        return ESP_EOK;
    }
    else
    {
        return ESP_ERROR;
    }
}
/***************************************************************
  *  @brief     退出透传
  *  @param     参数
  *  @note      备注 ：无
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author     wangzibo
 **************************************************************/

void ESP::ESP_exit_unvarnished(void) {
    this->myUsart->SendString("+++",3);
}

uint8_t ESP::ESP_connect_atkcld(char *id, char *pwd) {
    return 0;
}

uint8_t ESP::ESP_disconnect_atkcld(void) {
    return 0;
}
ESP::~ESP()
{
    delete myUsart;
}
/***************************************************************
  *  @brief     以ap模式链接WiFi
  *  @param     参数
  *  @note      wifi名称在ESP.h文件中以宏定义形式存在改变宏定义即可
  *             TCPIP 与PORT也是如此
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author    王子博
 **************************************************************/

void ESP::WIFIConnect() {
    char inputbuf[16];
    MyUsart myUsart(&huart1);
    ESP_hw_reset();
    HAL_Delay(20);
    ret=ESP_restore();
    ret=ESP_at_test();
    //myUsart.SendString(esp.myUsart->Re_GetData(),64);
    if (ret != 0)
    {
        myUsart.SendString("ESP init failed!",20);
        while (1)
        {
            HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
            HAL_Delay(500);
        }
    }
    myUsart.SendString("Joining to AP",16);
    //ret=esp.ESP_restore();

    ret=ESP_set_mode(3);
    ret=ESP_sw_reset();
    ret=ESP_ate_config(0);
    ret=ESP_join_ap(WIFI_SSID,WIFI_PWD);
    //ret=esp.ESP_get_ip(inputbuf);
    if (ret!=0)
    {
        myUsart.SendString("Error",5);
        while (1) {
            HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_9);
            HAL_Delay(500);
        }
    }
    ret=ESP_enter_unvarnished();
    ret=ESP_connect_tcp_server(SERVERIP,SERVERPORT);
    if (ret!=0)
    {
        myUsart.SendString("TCPError",9);
        while (1) {
            HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_9);
            HAL_Delay(500);
        }
    }
    myUsart.SendString("Success",7);
}
/***************************************************************
  *  @brief    主函数中实现串口三接收 串口一发送
  *  @param     参数
  *  @note      备注 ：无
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author     wangzibo
 **************************************************************/

/*void demo()
{
    MyUsart myUsart(&huart1);
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

    }
}*/


