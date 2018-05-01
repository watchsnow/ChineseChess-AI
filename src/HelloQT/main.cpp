#include "MyWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //QApplication 抽象了QT的应用程序
    QApplication a(argc, argv);
    //QWidget 抽象了窗口
    MyWidget w;
    w.show();
    // 进入消息循环 等待用户输入
    return a.exec();
}
