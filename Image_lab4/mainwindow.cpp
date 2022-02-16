#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionopen,&QAction::triggered,this,&MainWindow::openfile);//打开文件
    connect(ui->actionsave,&QAction::triggered,this,&MainWindow::saveimg);//保存文件


}
void MainWindow::openfile()//打开文件
{
    QString fname=QFileDialog::getOpenFileName(this,"请选择文件");
    if(fname!="")
    {
    b=new segmentation(fname);
    showimg();
}}
void MainWindow::showimg()
{
    QImage img(b->getbuf(),b->getwidth(),b->getheight(),QImage::Format_Indexed8);
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->setScaledContents(true);//图像显示大小固定为label大小
}
void MainWindow::saveimg()
{
     QString fname = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("保存文件"),"",tr("BMP Files (*.bmp)"));
    if(fname!="")
    {
        QImage img(b->getbuf(),b->getwidth(),b->getheight(),QImage::Format_Indexed8);
        QPixmap pmp=QPixmap::fromImage(img);
        bool a=pmp.save(fname);
        qDebug()<<"是否成功保存"<<a;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
