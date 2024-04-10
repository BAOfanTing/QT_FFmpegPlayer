#include "demuxthread.h"

DemuxThread::DemuxThread() {}

DemuxThread::~DemuxThread()
{
    qDebug()<<"~DemuxThread()";
    if(thread_)
    {
        Stop();
    }
}

int DemuxThread::Init(const char *url)
{
    qDebug() << "初始化："<< url; // 打印初始化的URL
    int ret = 0;
    url_ = url;

    ifmt_ctx_ = avformat_alloc_context(); // 分配 AVFormatContext 结构体内存

    ret = avformat_open_input(&ifmt_ctx_, url_.c_str(), NULL, NULL); // 打开输入流

    if (ret != 0)
    {
        char errbuf[AV_ERROR_MAX_STRING_SIZE]; // 用于存储错误信息的缓冲区
        av_strerror(ret, errbuf, sizeof(errbuf)); // 将错误码转换为错误消息字符串
        qDebug() << "打开输入时发生错误：" <<  errbuf; // 输出错误信息
        return -1; // 返回错误码表示初始化失败
    }

    ret = avformat_find_stream_info(ifmt_ctx_, NULL); // 查找流信息
    if (ret != 0)
    {
        char errbuf[AV_ERROR_MAX_STRING_SIZE]; // 用于存储错误信息的缓冲区
        av_strerror(ret, errbuf, sizeof(errbuf)); // 将错误码转换为错误消息字符串
        qDebug() << "查找流信息时发生错误：" <<  errbuf; // 输出错误信息
        return -1; // 返回错误码表示初始化失败
    }
    av_dump_format(ifmt_ctx_, 0, url_.c_str(), 0); // 打印输入格式信息

    audio_index_ = av_find_best_stream(ifmt_ctx_, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0); // 查找最佳音频流索引
    video_index_ = av_find_best_stream(ifmt_ctx_, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0); // 查找最佳视频流索引
    qDebug() << QString("音频流索引：%1，视频流索引：%2").arg(audio_index_).arg(video_index_);
    if (audio_index_ < 0 || video_index_ < 0)
    {
        return -1; // 如果找不到音频或视频流，返回错误码表示初始化失败
    }
}

int DemuxThread::Start()
{
    // 创建新线程来运行 Run 方法
    thread_ = new std::thread(&DemuxThread::Run, this);
    if (!thread_)
    {
        qDebug() << "创建线程失败";
        return -1; // 返回错误码表示启动失败
    }
    return 0; // 返回成功码表示启动成功
}

int DemuxThread::Stop()
{
    Thread::Stop(); // 调用基类 Thread 的停止方法
    avformat_close_input(&ifmt_ctx_); // 关闭输入流
}

void DemuxThread::Run()
{
    int ret = 0;
    AVPacket pkt;
    qDebug()<<"Run Start";
    // 循环读取数据包直到终止信号被设置
    while (abort_ != 1)
    {
        // 读取一个数据包
        ret = av_read_frame(ifmt_ctx_, &pkt);
        if (ret < 0)
        {
            char errbuf[AV_ERROR_MAX_STRING_SIZE]; // 用于存储错误信息的缓冲区
            av_strerror(ret, errbuf, sizeof(errbuf)); // 将错误码转换为错误消息字符串
            qDebug() << "读取数据包时发生错误：" <<  errbuf; // 输出错误信息
            break; // 如果读取失败，退出循环
        }
        if(pkt.stream_index == audio_index_)
        {
            qDebug()<<"audio pkt";
        }
        else if(pkt.stream_index == video_index_)
        {
            qDebug()<<"video pkt";
        }
        av_packet_unref(&pkt);
    }
    qDebug()<<"Run Finsh";
}
