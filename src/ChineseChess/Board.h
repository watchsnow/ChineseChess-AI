#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "Chesspiece.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);

    // 定义32颗旗子 对应下棋的32颗旗子
    Chesspiece _chesspiece[32];

    int _r;     // 旗子的半径

    // 返回棋盘行列对应的像素坐标
    QPoint center(int row, int column);

    QPoint center(int id);

    void drawChesspiece(QPainter& painter, int id);

    void paintEvent(QPaintEvent *);

    ~Board();

signals:

public slots:
};

#endif // BOARD_H
