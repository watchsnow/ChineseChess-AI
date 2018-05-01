#include "Board.h"
#include <QPainter>

Board::Board(QWidget *parent) : QWidget(parent)
{
    // 初始化32个棋子
    for(int i=0; i<32; ++i)
    {
        _chesspiece[i].init(i);
    }
}

// 把这个象棋的行和列转换旗子的中心点(棋盘的像素点坐标)
QPoint Board::center(int row, int column)
{
    QPoint point;
    point.rx() = (column+1)*_r*2;
    point.ry() = (row+1)   *_r*2;
    return point;
}

QPoint Board::center(int id)
{
    return center(_chesspiece[id]._row, _chesspiece[id]._column);
}

void Board::drawChesspiece(QPainter &painter, int id)
{
    QPoint centralPoint = center(id);
    QRect rect = QRect(centralPoint.x()-_r, centralPoint.y()-_r, _r*2, _r*2);
    // 美化旗子
    // 需要有一个背景
    painter.setBrush(QBrush(QColor(255, 255, 0)));
    painter.setPen(Qt::black);
    painter.drawEllipse(center(id), _r, _r);
    // 区别字是红的还是黑的
    if(_chesspiece[id]._isRed)
    {
        painter.setPen(Qt::red);
    }
    //    else
    //    {
    //        painter.setPen(Qt::black);
    //    }
    // 设置字体的大小
    painter.setFont(QFont("system", _r, 700));
    painter.drawText(rect,_chesspiece[id].getText(),QTextOption(Qt::AlignCenter));

}

// Drawing board
void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int d = 44; // Diameter of block
    _r = d/2;
    // 画10条横线
    for(int i = 1; i <= 10; ++i)
    {
        painter.drawLine(QPoint(d, i*d), QPoint(9 *d, i*d));
    }

    // 画9条竖线
    for(int i = 1; i <= 9; ++i)
    {
        if(i==1 || i==9)
        {
            painter.drawLine(QPoint(i*d, d), QPoint(i*d, 10*d));
        }
        else
        {
            painter.drawLine(QPoint(i*d, d), QPoint(i*d, 5*d));
            painter.drawLine(QPoint(i*d, 6*d), QPoint(i*d, 10*d));
        }

    }

    // 九宫格
    painter.drawLine(QPoint(4*d, 1*d), QPoint(6*d, 3*d));
    painter.drawLine(QPoint(6*d, 1*d), QPoint(4*d, 3*d));

    painter.drawLine(QPoint(4*d, 8*d), QPoint(6*d, 10*d));
    painter.drawLine(QPoint(6*d, 8*d), QPoint(4*d, 10*d));

    // 绘制32颗旗子
    for(int i=0; i<32; ++i)
    {
        drawChesspiece(painter, i);
    }
}

Board::~Board()
{

}
