#include "segmentation.h"

segmentation::segmentation(QString fn):ImageDate(fn)
{
//    averaging_filter();
    partition();
}
void segmentation::partition()
{
    //分成6×6的小块
    int h=height/6;
    int w=width/6;
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<6;j++)
        {
            int t=otsu( j*w,i*h,w,h);
            for(int m=i*h;m<(i+1)*h;m++)
                for(int n=j*w;n<(j+1)*w;n++)
                {
                    if(buf[m*width+n]<t)
                        buf[m*width+n]=0;
                    else
                        buf[m*width+n]=255;
                }
        }
    }
}
int segmentation::otsu(int start_width,int start_height,int w,int h)
{
    float *histogram =new float[256];//小块的灰度分布直方图
    for(int i=0;i<256;i++)
        histogram[i]=0;
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            histogram[buf[(i+start_height)*width+j+start_width]]++;
        }
    }
    float mG=0;//小块整体的均值
    for(int i=0;i<256;i++)
    {
        histogram[i]=histogram[i]/(w*h);
        mG+=i*histogram[i];
    }
    int result=1;//阈值结果
    float sigmaB=0;//方差
    for(int t=1;t<256;t++)//计算最大类间方差
    {
        float p1=0;
        float m=0;
        for(int i=0;i<=t;i++)
        {
            p1+=histogram[i];
            m+=i*histogram[i];
        }
        float temp_sigmaB=(mG*p1-m)*(mG*p1-m)/(p1*(1-p1));
        if(temp_sigmaB>sigmaB)
        {
            sigmaB=temp_sigmaB;
            result=t;
        }
    }
    qDebug()<<result;
    return result;
}
void segmentation::averaging_filter()//均值滤波，经分析后未采用
{
    for(int i=1;i<height-1;i++)
    {
        for(int j=1;j<width-1;j++)//窗位3×3的均值滤波器
        {
            buf[i*width+j]=(buf[(i-1)*width+j+1]+buf[(i-1)*width+j]+buf[(i-1)*width+j-1]
                    +buf[i*width+j+1]+buf[i*width+j]+buf[i*width+j-1]
                    +buf[(i+1)*width+j+1]+buf[(i+1)*width+j]+buf[(i+1)*width+j-1])/9;
        }
    }
}
