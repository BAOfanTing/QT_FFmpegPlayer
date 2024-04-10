#ifndef THREAD_H
#define THREAD_H
#include <QDebug>


#include <thread>
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
#ifdef __cplusplus ///
extern "C"
{
#include "libavutil/avutil.h"
}
#endif


class Thread
{
public:
    Thread(); // 构造函数
    ~Thread(); // 析构函数
    int Start(); // 启动线程
    int Stop(); // 停止线程
    int test_main();
    virtual void Run() = 0;
protected:
    int abort_ = 0; // 标记线程是否应该停止
    std::thread *thread_ = nullptr; // 线程对象指针，默认为 nullptr
};



#endif // THREAD_H
