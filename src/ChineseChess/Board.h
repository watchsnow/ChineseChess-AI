#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "Chesspiece.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);

    ~Board();

    // 定义32颗旗子 对应下棋的32颗旗子
    Chesspiece _chesspiece[32];

    // 返回棋盘行列对应的像素坐标
    QPoint center(int row, int column);

    QPoint center(int id);

    void paintEvent(QPaintEvent *);

    void drawChesspiece(QPainter& painter, int id);

    // 实现旗子的走动
    // void mousePressEvent(QMouseEvent *);         // 鼠标点下
    void mouseReleaseEvent(QMouseEvent *event);     // 鼠标释放 移动象棋 用这个

    // 棋盘的像素值 要转为象棋的行列值 (效率不高应该改进)
    bool getRowColumn(QPoint boardPixelPoint,int& row, int& column);

public:
    int _r;             // 旗子的半径
    int _selectedId;    // 记录被选中旗子的标记

signals:

public slots:
};

#endif // BOARD_H
