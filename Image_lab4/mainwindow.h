#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"imagedate.h"
#include"segmentation.h"
#include"QFileDialog"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void openfile();
    void showimg();
    void saveimg();

private:
    Ui::MainWindow *ui;
    segmentation *b;
};

#endif // MAINWINDOW_H
