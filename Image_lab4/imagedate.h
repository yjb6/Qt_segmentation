#ifndef IMAGEDATE_H
#define IMAGEDATE_H
#include"QImage"
#include"QString"
#include"QDataStream"
#include"stdio.h"
#include<windef.h>
#include"wingdi.h"
#include"QFile"
#include<QDebug>
class ImageDate
{
    friend class MainWindow;
public:
    ImageDate();
    ~ImageDate();
    ImageDate(QString fn);//根据文件名构建图像
    void read();
    long getwidth();
    long getheight();
    uchar* getbuf();
protected:
    QString fname;
    uchar *buf;//默认灰度级为0-255 大小为：linenum*height;
    long height;
    long width;
    long linenum;//由于图像每一行字节数必须为4的倍数，所以需要补0，此为实际每一行字节数
};



#endif // IMAGEDATE_H
