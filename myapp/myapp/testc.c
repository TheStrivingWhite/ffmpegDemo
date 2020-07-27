//
//  testc.c
//  myapp
//
//  Created by z on 2020/7/24.
//  Copyright © 2020 1. All rights reserved.
//

#include "testc.h"

//状态值  标志是1是开始录制，0是结束录制
static int rec_status = 0;

void set_status(int status){
    rec_status = status;
}

void record_audio()
{
    //开始录制了
    rec_status = 1;
    
    av_log_set_level(AV_LOG_DEBUG);
    //1. 注册所有设备
    avdevice_register_all();
    //2. 获取格式  设置采集方式
    AVInputFormat * iformat = av_find_input_format("avfoundation");
    
    AVFormatContext *fmt_ctx = NULL;
    AVDictionary *options = NULL;
    //每次重新分配地址
    AVPacket pkt;
    //音频设备  mac上 :0 从第一个音频设备获取声音   可以到ffmpeg官网查看devicename说明
    char * devicename = ":0";
     
    
    //3.打开设备
    /*
     AVFormatContext **ps  上下文，作用：前面调用的API和后面调用的API都依赖于上下文，对一个多媒体文件进行解码、编码都依赖于上下文，操作那个文件，只需要把这个文件的上下文传过去，就知道是对那个文件操作了 。这个上下文是avformat_open_input这个API返回的指针，我们只要定义这个指针就行 AVFormatContext *fmt_ctx;
     const char *url: 可以是一个网络地址，也可以是本地的文件，
     AVInputFormat *fmt
     AVDictionary **options   打开设备的一些参数，一般解码的时候用到
     */

    // 成功==0，不成功!= 0
    int ret = avformat_open_input(&fmt_ctx, devicename, iformat, &options);
    if (ret < 0) {
        /*
        int    enum         错误码
        char   errbuf       错误信息输出到哪
        size_t errbuf_size
         */
        char errors[1024];
        
        av_strerror(ret, errors, 1024);
        printf(stderr,"Failed to open audio device,[%d]%s\n",ret,errors);
        return;
    }
    
    //1-1.创建文件
    /*
     fopen 创建文件函数
     const char *restrict __filename：路径
     const char *restrict __mode：模式     w写数据 r是读数据     b是byte二进制数据，+号是这个文件不存在，你就去创建它
     FILE 返回值
     */
    char * out = "/Users/yangyazhuo/Desktop/audio/av_base/audio.pcm";
    FILE * outFile = fopen(out, "wb+");
    
    //初始化
    av_init_packet(&pkt);
    while ((av_read_frame(fmt_ctx, &pkt) == 0)&& rec_status) {
        //1-2.写入文件
        /*
         const void *restrict __ptr： 要写入的数据
         size_t __size：大小
         size_t __nitems：数据的个数
         FILE *restrict __stream：文件存入地址
         */
        fwrite(pkt.data, pkt.size, 1, outFile);
        //
        fflush(outFile);
        //1-3 关闭文件
        fclose(outFile);
        
        //释放掉pkt
        av_packet_unref(&pkt);
    }
    //释放上下文
    avformat_close_input(&fmt_ctx);
    av_log(NULL, AV_LOG_DEBUG, "Finished\n");
    return;
};


