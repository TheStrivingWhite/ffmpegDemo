//
//  testc.h
//  myapp
//
//  Created by z on 2020/7/24.
//  Copyright © 2020 1. All rights reserved.
//

#ifndef testc_h
#define testc_h

#include <stdio.h>
#include "libavutil/avutil.h"
//注册设备的
#include "libavdevice/avdevice.h"
//打开设备
#include "libavformat/avformat.h"

#include "libavcodec/avcodec.h"

void record_audio(void);
void set_status(int status);

#endif /* testc_h */
