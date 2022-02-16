#ifndef SEGMENTATION_H
#define SEGMENTATION_H
#include"imagedate.h"

class segmentation:public ImageDate
{
public:
    segmentation(QString fn);
    int otsu(int start_width,int start_height,int w,int h);//大津法计算阈值
    void partition();//分块
    void averaging_filter();//均值滤波，经分析后未采用
private:

};

#endif // SEGMENTATION_H
