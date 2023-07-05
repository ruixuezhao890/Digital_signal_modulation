/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MySchedule.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/5/27 
*********************************************************************
*********
*/
//

#ifndef CPROJECT_MYSCHEDULE_H
#define CPROJECT_MYSCHEDULE_H
#include <vector>
#ifdef __cplusplus
extern "C"
{
#endif

#include "Myapplication.h"
#include "MyUsart.h"
//#include "IncludeALL.h"
#define GET_NOW_TIME_MS   HAL_GetTick()//单位是毫秒
#define _MY_DEBUG_  1

#ifdef  _MY_DEBUG_
//#define    MY_DEBUG_PRINT_INFO(...)      myUsartSchedule.Myprintf( __VA_ARGS__,)//printf(__VA_ARGS__)
//#define    MY_DEBUG_PRINT_VAR(X, ...)     myUsartSchedule.Myprintf("file: " __FILE__", Line: %d:" X"\r\n",__LINE__, ##__VA_ARGS__)//printf("file: "__FILE__", Line: %d:" "\r\n",__LINE__,##__VA_ARGS__)
#else
#define    MY_DEBUG_PRINT_INFO(...)
	#define    MY_DEBUG_PRINT_VAR(X, ...)
#endif
/*______________________类的声明在这下面________________:*/
class Task{
public:
    void (*task_func)(void);   //函数指针
    uint16_t interval_ticks;   //每隔多少周期执行一次
    uint16_t max_time_micros;  //该函数运行一次的大概时间us
    uint32_t last_tick_counter;//上一次函数运行时tick
};

class MySchedule{
public:
    void MyScheduleSetPeriod( uint32_t TimePeriod);
    void MyTaskGreat( void (*task_func)(void),uint16_t interval_ticks,
                      uint16_t max_time_micros,uint32_t last_tick_counter);
    void MyScheduleRun(uint32_t TimeAvailable);
    void MyScheduleWhile();
private:

    std::vector<Task> TaskVector;
    Task task;
    uint8_t num_task=0;//任务数量
    uint32_t tick_counter = 0;//执行周期数
    uint32_t TimePeriod=5;

/* 记录当前时间差 */
    uint32_t current_time;

/* 记录上一次时间 */
    uint32_t last_time;
};
#ifdef __cplusplus
}
#endif
#endif //CPROJECT_MYSCHEDULE_H
