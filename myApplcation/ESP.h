/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : ESP.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/5/14 
*********************************************************************
*********
*/
//

#ifndef CPROJECT_ESP_H
#define CPROJECT_ESP_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "Myapplication.h"
#include "MyUsart.h"

#define WIFI_SSID "LL1"
#define WIFI_PWD "123456789"
#define SERVERIP"192.168.99.178"
#define SERVERPORT  "9090"


#define ESP_RST_GPIO_PORT           GPIOF
#define ESP_RST_GPIO_PIN            GPIO_PIN_6
#define ESP_RST_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0) /* PF口时钟使能 */

    /*IO操作*/
#define ESP_RST(x)                  do{ x ?                                                                                     \
                                                HAL_GPIO_WritePin(ESP_RST_GPIO_PORT, ESP_RST_GPIO_PIN, GPIO_PIN_SET) :  \
                                                HAL_GPIO_WritePin(ESP_RST_GPIO_PORT, ESP_RST_GPIO_PIN, GPIO_PIN_RESET); \
                                            }while(0)

    /*错误代码*/
#define ESP_EOK         0   /* 没有错误 */
#define ESP_ERROR       1   /* 通用错误 */
#define ESP_ETIMEOUT    2   /* 超时错误 */
#define ESP_EINVAL      3   /* 参数错误 */
/*______________________类的声明在这下面________________:*/
      //这个类必须声明为全局变量
    /**
     * @brief 类的简单概述:一个关于WiFi的类\n
     * 类的详细概述:这个类可以兼容WiFi模块更改对应的引脚即可做到兼容
     * 例如esp8266 和esp01
     *
     */
class ESP{
public:
    void ESP_Init(UART_HandleTypeDef *huart);
    void    ESP_hw_reset(void);
    uint8_t ESP_send_at_cmd(char *cmd, char *ack, uint32_t timeout);    /* ATK-MW8266D发送AT指令 */
    uint8_t ESP_init(uint32_t baudrate);                                /* ATK-MW8266D初始化 */
    uint8_t ESP_restore(void);                                          /* ATK-MW8266D恢复出厂设置 */
    uint8_t ESP_at_test(void);                                          /* ATK-MW8266D AT指令测试 */
    uint8_t ESP_set_mode(uint8_t mode);                                 /* 设置ATK-MW8266D工作模式 */
    uint8_t ESP_sw_reset(void);                                         /* ATK-MW8266D软件复位 */
    uint8_t ESP_ate_config(uint8_t cfg);                                /* ATK-MW8266D设置回显模式 */
    uint8_t ESP_join_ap(char *ssid, char *pwd);                         /* ATK-MW8266D连接WIFI */
    uint8_t ESP_get_ip(char *buf);                                      /* ATK-MW8266D获取IP地址 */
    uint8_t ESP_connect_tcp_server(char *server_ip, char *server_port); /* ATK-MW8266D连接TCP服务器 */
    uint8_t ESP_enter_unvarnished(void);                                /* ATK-MW8266D进入透传 */
    void ESP_exit_unvarnished(void);                                    /* ATK-MW8266D退出透传 */
    uint8_t ESP_connect_atkcld(char *id, char *pwd);                    /* ATK-MW8266D连接原子云服务器 */
    uint8_t ESP_disconnect_atkcld(void);                                /* ATK-MW8266D断开原子云服务器连接 */

    void WIFIConnect();

    ~ESP();
    uint8_t ret;
    MyUsart * myUsart;



};
#ifdef __cplusplus
}
#endif
#endif //CPROJECT_ESP_H
