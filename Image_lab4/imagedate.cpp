#include "imagedate.h"
#include"stdio.h"
ImageDate::ImageDate()
{

}
ImageDate::ImageDate(QString fn)
{
    fname=fn;
    read();
}
ImageDate::~ImageDate()
{}
void ImageDate::read()
{
    BITMAPFILEHEADER fileheader;//文件头部信息
    BITMAPINFOHEADER head;//图片头部信息
    FILE *f;
    QByteArray ba = fname.toLatin1();
    char *f_temp = ba.data();//将qstring转为char*
    f=fopen(f_temp,"rb");
    if(f==0)
        qDebug()<<"打开失败";
    fread(&fileheader,sizeof(fileheader),1,f);//读取文件头部信息
       if(fileheader.bfType!=0x4D42)  // 判断是否为BMP图片
       {
           fclose(f);
           return ;
       }
    fread(&head,sizeof(head),1,f);//读取图片头部信息
    width=head.biWidth;
    height=head.biHeight;
    qDebug()<<width<<height;
    fseek(f,fileheader.bfOffBits,SEEK_SET);//将文件流指针跳到图像data开始的地方
    linenum=(width+3)/4*4;//计算补齐后的每行的宽度，为4的倍速
    buf=new uchar[linenum*height];
    for(int i=0;i<height;i++){
        int iret = fread(buf+(height-i-1)*linenum,sizeof(BYTE),linenum,f);//读取时从最后一行的数据开始
        if(iret !=linenum)
        {
            fclose(f);
            return;
        }
        }
        fclose(f);
}
long ImageDate::getheight()
{
    return height;
}
long ImageDate::getwidth()
{
    return width;
}
uchar *ImageDate::getbuf()
{
    return buf;
}
