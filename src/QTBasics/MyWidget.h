#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPushButton>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);
    // 在Qt Creator中, 类中的斜体字 表示虚函数
    virtual void paintEvent(QPaintEvent *);
    // 捕获鼠标消息
    // Mouse process event
    virtual void mousePressEvent(QMouseEvent *);
    QPoint _ptClick;
    // 按钮 设个游戏就这有一个 就是悔棋
    // 定义一个按钮对象
    QPushButton* _button;
    ~MyWidget();

signals:

public slots:
};

#endif // MYWIDGET_H
