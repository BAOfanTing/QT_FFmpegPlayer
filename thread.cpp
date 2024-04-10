#include "demuxthread.h"

Thread::Thread() {} // 空的构造函数实现

Thread::~Thread()
{
    if(thread_)
    {
        Thread::Stop(); // 在析构函数中停止线程
    }
}

int Thread::Start()
{
    // 在此处添加启动线程的代码
    // 返回适当的值以指示启动是否成功
}

int Thread::Stop()
{
    abort_ = 1; // 设置停止标记为真
    if(thread_)
    {
        thread_->join(); // 等待线程结束
        delete thread_; // 删除线程对象
        thread_ = nullptr; // 将线程指针设置为 nullptr
    }
    // 返回适当的值以指示停止是否成功
}

int Thread::test_main()
{
    qDebug() << "测试主函数开始";
    int ret = 0;
    //1、解复用
    DemuxThread demux_thread;
    ret = demux_thread.Init("test.mp4");
    if (ret < 0)
    {
        qDebug() << "初始化失败";
        return -1;
    }

    ret = demux_thread.Start();
    if (ret < 0)
    {
        qDebug() << "启动失败";
        return -1;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10000)); // 休眠10秒
    demux_thread.Stop();
}


