#include "Board.h"
#include <QPainter>
#include <QMouseEvent>

Board::Board(QWidget *parent) : QWidget(parent)
{
    // 初始化32个棋子
    for(int i=0; i<32; ++i)
    {
        _chesspiece[i].init(i);
    }
    _selectedId = -1;
}

Board::~Board()
{

}

// 把这个象棋的行和列转换旗子的中心点(棋盘的像素点坐标) (把象棋的行列值转换为棋盘的像素值)
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

// 棋盘的像素值 要转为象棋的行列值 (效率不高应该改进)
bool Board::getRowColumn(QPoint boardPixelPoint, int &row, int &column)
{
    for(row=0; row<=9; row++)
    {
        for(column=0; column<=8; column++)
        {
            QPoint centerPoint = center(row, column); // 取出这个行列对应的中心点
            // 计算距离
            int dx = centerPoint.x() - boardPixelPoint.x();
            int dy = centerPoint.y() - boardPixelPoint.y();
            int dist = dx*dx+dy*dy;
            if(dist < _r*_r)
            {
                return true;
            }
        }
    }
    return false;
}

void Board::drawChesspiece(QPainter &painter, int id)
{
    if(_chesspiece[id]._isDead)  // 这样的旗子就不应该被画出来了(已经死掉了)
    {
        return;
    }
    QPoint centralPoint = center(id);
    QRect rect = QRect(centralPoint.x()-_r, centralPoint.y()-_r, _r*2, _r*2);
    // 记录被选中的旗子背景应该不一样(要设置的画刷不一样)
    if(id == _selectedId)
    {
        painter.setBrush(QBrush(Qt::gray));
    }
    else
    {
        // 美化旗子
        // 需要有一个背景
        painter.setBrush(QBrush(Qt::yellow));
    }
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

void Board::mouseReleaseEvent(QMouseEvent *event)  // event里面有我鼠标点击的位置
{
    // 获得位置
    QPoint mouseClickPoint = event->pos(); // 得到鼠标点击的位置
    // 看 mouseClickPoint 这个点上有没有象棋被点中
    // 将 mouseClickPoint 转换为象棋的行列值
    // 然后再去判断这个行列值上有没有旗子
    // 如果有旗子 就把他选中( 好药涉及到一个转换 )
    // 棋盘的像素值 要转为象棋的行列值
    int row, column;
    bool bRet = getRowColumn(mouseClickPoint, row, column);
    if(false == bRet) // 点到棋盘外了  在棋盘外面乱戳 我是不会有反应的
    {
        return;
    }

    int i; // 外面要用
    int clickId = -1;
    // 判断行和列上有没有旗子
    for(i=0; i<32; ++i)
    {
        if(_chesspiece[i]._row == row && _chesspiece[i]._column == column && _chesspiece[i]._isDead == false) // 就是i被选中了
        {
            break;
        }
    }

    if (i<32) // 就是 i 被选中了
    {
        clickId = i;
        // 为了让selected显示出来
    }

    // 选择旗子
    if(_selectedId == -1)
    {
        if(clickId != -1)
        {
            _selectedId = clickId;
            update();
        }
    }
    // 如果有选中旗子就移动旗子
    else
    {
        _chesspiece[_selectedId]._row    = row;
        _chesspiece[_selectedId]._column = column;
        if(clickId != -1)  // 被点的地方有旗子的话 就要吃掉它
        {
            _chesspiece[clickId]._isDead = true;
        }
        _selectedId = -1;
        update();  // 重绘棋盘
    }
}
