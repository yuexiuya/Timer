#include "HTimer.h"
#include <stdio.h>

/**
 * @Description: 构造函数
 * @Date: 2019/05/10
 */
HTimer::HTimer()
{

}

/**
 * @Description: 析构函数
 * @Date: 2019/05/10
 */
HTimer::~HTimer()
{
    if(m_thread.joinable()) {
        m_cv.notify_all(); // exit event loop
        m_thread.join();
    }
}

/**
 * @Description:  TODO
 * @Date: 2019/05/10
 * @Param msec :
 * @return  
 */
void HTimer::start(int msec)
{

}

/**
 * @Description: start a time
 * @Date: 2019/05/10
 */
void HTimer::start()
{
    printf("[HTime] timer start !\n");
    if(m_thread.joinable()) {
        /* if a timer's event is start, now firstly exit the loop, and then we
         * will start a new event */
        m_cv.notify_all();
        m_thread.join();
    }
    m_thread = std::thread(std::bind(&HTimer::timeLoop, this));
}

/**
 * @Description: set timer's interval
 * @Date: 2019/05/10
 * @Param msec : timer's interval
 */
void HTimer::setInterval(int msec)
{
    m_msec = msec;
}

/**
 * @Description: stop a timer
 * @Date: 2019/05/10
 */
void HTimer::stop()
{
    std::unique_lock <std::mutex> lck(m_mtx);
    printf("[HTime] timer stop !\n");
    m_cv.notify_all();
    m_isRun = false;
}

/**
 * @Description: a event loop in the other's thread
 * @Date: 2019/05/10
 */
void HTimer::timeLoop()
{
    std::unique_lock <std::mutex> lck(m_mtx);
    if(!m_isRun) {
        printf("[HTimer] timeLoop exit \n");
        return;
    }
    m_isRun = true;
    while(m_cv.wait_for(lck,std::chrono::milliseconds(m_msec))==std::cv_status::timeout) {
        if(event == nullptr) {
            break;
        }
        event();
    }
    printf("[HTimer] timeLoop exit \n");
}
