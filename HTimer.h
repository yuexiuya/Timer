#ifndef HTIMER_H
#define HTIMER_H

#include <thread>
#include <mutex>
#include <condition_variable>

typedef std::function<void ()> CallBackEvent;

class HTimer
{
public:
    HTimer();
    ~HTimer();

    void start(int msec);
    void start();
    void setInterval(int msec);
    void stop();

    /// call back
    CallBackEvent event;
private:
    bool m_isRun = false;
    int m_msec = 0;
    std::thread m_thread;
    std::mutex m_mtx;
    std::condition_variable m_cv;
    void timeLoop();
};

#endif // HTIMER_H
