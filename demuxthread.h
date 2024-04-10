#ifndef DEMUXTHREAD_H
#define DEMUXTHREAD_H
#include "thread.h"
#include <QDebug>
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
#ifdef __cplusplus ///
extern "C"
{
#include "libavutil/avutil.h"
#include "libavformat/avformat.h"
}
#endif

class DemuxThread : public Thread
{
public:
    DemuxThread(); // 构造函数
    ~DemuxThread();
    int Init(const char *url); // 初始化方法，使用给定的 URL
    int Start(); // 开始解复用方法
    int Stop(); // 停止解复用方法
    void Run(); // 运行解复用过程的方法

private:
    std::string url_; // 要解复用的文件名或 URL
    AVFormatContext *ifmt_ctx_ = NULL; // 用于解复用的 AVFormatContext 结构体指针

    int audio_index_ = -1;
    int video_index_ = -1;
};

#endif // DEMUXTHREAD_H
