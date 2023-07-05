/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MySchedule.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/5/27 
*********************************************************************
*********
*/
//

#include "MySchedule.h"
MyUsart myUsartSchedule(&huart1);
/***************************************************************
  *  @brief     创建任务
  *  @param     参数 void (*task_func)(void)：函数指针
  *                  uint16_t interval_ticks：多少周期执行一次
  *                   uint16_t max_time_micros：运行一次大概时间；单位ms
  *                   uint32_t last_tick_counter：上一次函数运行时的时间
  *  @note      备注 ：使用调度前先创建任务才可继续 必须interval_ticks>last_tick_counter
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author     wangzibo
 **************************************************************/

void MySchedule::MyTaskGreat(void (*task_func)(void), uint16_t interval_ticks, uint16_t max_time_micros,
                             uint32_t last_tick_counter) {
    this->num_task++;
    this->task.task_func=task_func;
    this->task.interval_ticks=interval_ticks;
    this->task.max_time_micros=max_time_micros;
    this->task.last_tick_counter=last_tick_counter;
    this->TaskVector.push_back(this->task);


}

void MySchedule::MyScheduleRun(uint32_t TimeAvailable) {
    uint64_t now;
    uint16_t dt;
    uint16_t interval_ticks;
    for (int i = 0; i < this->TaskVector.size(); ++i) {
        now = GET_NOW_TIME_MS;
        dt = tick_counter - TaskVector[i].last_tick_counter;//上一次函数运行时tick
        interval_ticks = TaskVector[i].interval_ticks;//每隔多少周期执行一次


        if (dt >= interval_ticks) {
            //调试时使用，任务长时间未运行，说明任务的运行周期太长或者shceduler_run的可运行时间太短
            if (dt >= interval_ticks * 2) {
                myUsartSchedule.SendCmdOut("Scheduler slip task[%u] (%u/%u/%u)\n",
                                   (unsigned) i,
                                   (unsigned) dt,
                                   (unsigned) interval_ticks,
                                   (unsigned) TaskVector[i].max_time_micros);//该函数运行一次的大概时间us


            }
            if (TaskVector[i].max_time_micros <= TimeAvailable) {
                //运行任务
                TaskVector[i].task_func();
                //更新last_tick_counter
                TaskVector[i].last_tick_counter = tick_counter;

#ifdef _MY_DEBUG_
                uint32_t end_time = GET_NOW_TIME_MS - now;
//如果任务运行过后发现时间超出shceduler_run的可运行时间time_available，说明任务的max_time_micros设置小了
                if (end_time > TimeAvailable) {
                    myUsartSchedule.SendCmdOut("Scheduler slip task[%u] (%u/%u)\n",
                                       (unsigned) i,
                                       (unsigned) end_time,
                                       (unsigned) TaskVector[i].max_time_micros);
                    return;

                }
#endif //debug打印
            }

        }
        TimeAvailable -= (GET_NOW_TIME_MS - now);
    }
    this->tick_counter++;
}

void MySchedule::MyScheduleWhile() {
    current_time = GET_NOW_TIME_MS- last_time;
    if(current_time >= TimePeriod)
    {
        last_time = GET_NOW_TIME_MS;
      this->MyScheduleRun(TimePeriod);
    }
}

//设置控制周期 单位是毫秒
void MySchedule::MyScheduleSetPeriod( uint32_t TimePeriod) {
    this->TimePeriod=TimePeriod;

}
