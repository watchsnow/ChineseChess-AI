#include "MyWidget.h"
#include <QPainter>
#include <QMouseEvent>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    _button = new QPushButton("This is button",this/*PushButton的父对象 没有的话这个Butto就自立门户了*/);
    // _button->show(); 父窗口show的时候带着这个窗口一起show
}

void MyWidget::paintEvent(QPaintEvent *)   // paintEvent 就像Windows里面的OnDraw
{
    // QPainter 绘制类
    // 还可以绘制打印机   绘制图画 也可以像QQ样拷屏(就像QQ的截屏)....

    QPainter painter(this/*绘制对象*/);
#if 0
    painter.setPen(QColor(255,0,0));
    painter.setBrush(QBrush(QColor(255,255,0)));
    painter.drawLine(QPoint(0,0),QPoint(100,100));
    painter.drawText(200,200,"HelloQT");
    painter.drawEllipse(QPoint(200,300),25,50);
#endif
    painter.drawEllipse(_ptClick,30,30);
}

void MyWidget::mousePressEvent(QMouseEvent *event) // 前置声明和include的区别
{
    // 得到鼠标点击的地方
    _ptClick = event->pos(); // 太湖鼠标点击的地方
    // 强制程序重新绘制界面
    update();
    //    QPainter p(this);
    //    p.drawEllipse(pt,30,30);
}

MyWidget::~MyWidget()
{

}

