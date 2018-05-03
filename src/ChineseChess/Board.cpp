#include "Board.h"
#include <QPainter>
#include <QMouseEvent>

#define GET_ROW_COLUMN_BY_ID(__row, __column, __id)\
    int __row = _chesspiece[__id]._row;\
    int __column = _chesspiece[__id]._column

Board::Board(QWidget *parent) : QWidget(parent)
{
    init(true);
}

Board::~Board()
{

}

// 把这个象棋的行和列转换棋子的中心点(棋盘的像素点坐标) (把象棋的行列值转换为棋盘的像素值)
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
    if(_chesspiece[id]._isDead)  // 这样的棋子就不应该被画出来了(已经死掉了)
    {
        return;
    }
    QPoint centralPoint = center(id);
    QRect rect = QRect(centralPoint.x()-_r, centralPoint.y()-_r, _r*2, _r*2);
    // 记录被选中的棋子背景应该不一样(要设置的画刷不一样)
    if(id == _selectedId)
    {
        painter.setBrush(QBrush(Qt::gray));
    }
    else
    {
        // 美化棋子
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

    // 绘制32颗棋子
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
    // 然后再去判断这个行列值上有没有棋子
    // 如果有棋子 就把他选中( 好药涉及到一个转换 )
    // 棋盘的像素值 要转为象棋的行列值
    int row, column;
    bool bRet = getRowColumn(mouseClickPoint, row, column);
    if(false == bRet) // 点到棋盘外了  在棋盘外面乱戳 我是不会有反应的
    {
        return;
    }

    // 获得这次点击的棋子的ID {{{
    int i; // 外面要用
    int clickId = -1;
    // 判断行和列上有没有棋子
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
    // }}}

    // 选择棋子
    if(_selectedId == -1)
    {
        if(clickId != -1)
        {
            // 判断该谁走了
            if(_bIsRedTurn == _chesspiece[clickId]._isRed)
            {
                _selectedId = clickId;
                update();
            }
        }
    }
    // 如果有选中棋子就移动棋子
    else
    {
        if (canMoveRules(_selectedId, row, column, clickId/*有没有吃棋 有些棋子走棋和吃棋是不一样的 比如炮*/)) // 判断是不是能走
        {
            /*走棋*/
            _chesspiece[_selectedId]._row    = row;
            _chesspiece[_selectedId]._column = column;
            if(clickId != -1)  // 被点的地方有棋子的话 就要吃掉它
            {
                _chesspiece[clickId]._isDead = true;
            }
            _selectedId = -1;
            _bIsRedTurn = !_bIsRedTurn;
            update();  // 重绘棋盘
        }
    }
}

bool Board::canMoveRules(int canMoveId, int row, int column, int killId)
{
    if(_chesspiece[canMoveId]._isRed == _chesspiece[killId]._isRed)//moveId和killId颜色相同) // 就不可以移动
    {
        // 换选择
        _selectedId = killId;  // 这样就不会出现非常矬的问题(自己吃自己)
        update();
        return false; // 除了return false之外 还要换选择
    }

    // 各个棋子的走法 (发复杂的问题简单化) (把一个复杂的canMoveRules函数分解七个简单的函数依次实现 就可以了)
    switch(_chesspiece[canMoveId]._type)
    {
    case Chesspiece::Generals:
        return generalsCanMoveRules(canMoveId, row,  column, killId);

    case Chesspiece::Guards:
        return guardsCanMoveRules(canMoveId, row,  column, killId);

    case Chesspiece::Ministers:
        return ministersCanMoveRules(canMoveId, row,  column, killId);

    case Chesspiece::Horses:
        return horsesCanMoveRules(canMoveId, row,  column, killId);

    case Chesspiece::Chariots:
        return chariotsCanMoveRules(canMoveId, row,  column, killId);

    case Chesspiece::Cannons:
        return cannonsCanMoveRules(canMoveId, row,  column, killId);

    case Chesspiece::Soldiers:
        return soldiersCanMoveRules(canMoveId, row,  column, killId);
    }

    return true;
}

// 将
bool Board::generalsCanMoveRules(int canMoveId, int row, int column, int killId)
{
    Q_UNUSED(killId)
    /*
        1. 目标位置在九宫内( 行和列只可以在九宫范围之内 )
        2. 移动的步长是一个格子
    */
    // 判断目标在九宫内
    if(_chesspiece[canMoveId]._isRed)
    {
        if(row > 2)
        {
            return false;
        }
    }
    else
    {
        if(row < 7)
        {
            return false;
        }
    }
    if (column < 3)
    {
        return false;
    }
    if (column >5 )
    {
        return false;
    }
    // 计算移动步长是一个格子
    // 行和列必须有一个等于0 (这样他们才是同一个直线上)  (一个等于0 的情况下 另外一个不是等于1 就是等于-1)
    int distRow     = _chesspiece[canMoveId]._row - row;
    int distColumn  = _chesspiece[canMoveId]._column - column;
    int dist        = abs(distRow)*10 + abs(distColumn);  // 地址: 将 1或者10 马 12或者21 象 22 兵 10或者1
    if(dist == 1 || dist == 10)
    {
        return true;
    }
    return false;
}

// 士
bool Board::guardsCanMoveRules(int canMoveId, int row, int column, int killId)
{
    Q_UNUSED(killId);
    if(_chesspiece[canMoveId]._isRed)
    {
        if(row > 2)
        {
            return false;
        }
    }
    else
    {
        if(row < 7)
        {
            return false;
        }
    }
    if (column < 3)
    {
        return false;
    }
    if (column >5 )
    {
        return false;
    }
    // 计算移动步长是一个格子
    // 行和列必须有一个等于0 (这样他们才是同一个直线上)  (一个等于0 的情况下 另外一个不是等于1 就是等于-1)
    int distRow     = _chesspiece[canMoveId]._row - row;
    int distColumn  = _chesspiece[canMoveId]._column - column;
    int dist        = abs(distRow)*10 + abs(distColumn);  // 地址: 将 1或者10 马 12或者21 象 22 兵 10或者1 士11
    if(dist == 11)
    {
        return true;
    }
    return false;
}

// 象
bool Board::ministersCanMoveRules(int canMoveId, int row, int column, int killId)
{
    Q_UNUSED(killId)
    GET_ROW_COLUMN_BY_ID(row1, column1, canMoveId);
    int dist = relation(row1, column1, row, column);
    if(dist != 22)
    {
        return false;
    }

    // 找象眼
    int ministersEyeRow     = (row+row1)/2;
    int ministersEyeColumn  = (column+column1)/2;

    // 在去找有没有棋子
    if(getChesspieceId(ministersEyeRow, ministersEyeColumn) != -1)
    {
        // 象眼有棋子
        return false;
    }

    // 判断这个象是不是在棋盘的下方(就是不可以过河)  (以前是用红色和黑色来判断这个是不全面的)
    if(isBottomSide(canMoveId))
    {
        if(row < 4)
        {
            return false;
        }
    }
    else
    {
        if(row > 5)
        {
            return false;
        }
    }
    return true;
}

// 马
bool Board::horsesCanMoveRules(int canMoveId, int row, int column, int killId)
{
    Q_UNUSED(killId)
    GET_ROW_COLUMN_BY_ID(row1, column1, canMoveId);
    // 得到关系值
    int dist = relation(row1, column1, row, column);

    // 寻找马腿
    if(dist != 12 && dist != 21)
    {
        return false;
    }

    if(dist == 12)
    {
        if(getChesspieceId(row1, (column + column1)/2) != -1)
        {
            return false;
        }
    }
    else
    {
        if(getChesspieceId((row+row1)/2, column1) != -1)
        {
            return false;
        }
    }

    return true;
}

// 车
bool Board::chariotsCanMoveRules(int canMoveId, int row, int column, int killId)
{
    Q_UNUSED(killId)
    GET_ROW_COLUMN_BY_ID(row1, column1, canMoveId);
    int ret = getChesspieceCountAtLine(row1, column1, row, column); // 返回-1 表示这两个点不在一条直线上面 如果在一条直线上面 就不用走了 就会返回这连个坐标点之间 有多少个棋子
    if(ret == 0)
    {
        return true;
    }
    return false;
}

// 炮
bool Board::cannonsCanMoveRules(int canMoveId, int row, int column, int killId)
{
    GET_ROW_COLUMN_BY_ID(row1, column1, canMoveId);
    int ret = getChesspieceCountAtLine(row, column, row1, column1);
    if(killId != -1)  // 这个炮吃了别人的子
    {
        if(ret == 1) // 这条线上必须要有一个棋子
        {
            return true;
        }
    }
    else // 如果KillID == -1 就是移动 移动的话 就和车是一样的
    {
        if(ret == 0)
        {
            return true;
        }
    }
    return false;
}

// 兵
bool Board::soldiersCanMoveRules(int canMoveId, int row, int column, int killId)
{
    Q_UNUSED(killId)
    // 要复杂一些 需要看看过不过河
    GET_ROW_COLUMN_BY_ID(row1, column1, canMoveId);
    int dist = relation(row1, column1, row, column);
    if(dist != 1 && dist != 10) // 跟将一样
    {
        return false;
    }

    // 看看兵是不是在下面
    if(isBottomSide(canMoveId))
    {
        if(row > row1) // 目标行大于原来的行   就是往前走  这就是 后退的情况
        {
            return false;
        }
        if(row1 >= 5 && row == row1)  // 还没有过河就平着走  过了河 才可以平着走
        {
            return false;
        }
    }
    else
    {
        if(row < row1)
        {
            return false;
        }
        if(row1 <= 4 && row == row1)
        {
            return false;
        }
    }

    return true;
}

int Board::relation(int row1, int column1, int row, int column)
{
    return qAbs(row1-row)*10+qAbs(column1-column);
}

int Board::getChesspieceId(int row, int column)
{
    for(int i=0; i<32; i++)
    {
        if(_chesspiece[i]._row == row && _chesspiece[i]._column == column)
        {
            return i;
        }
    }
    return -1;
}

bool Board::isBottomSide(int id)
{
    return _bSide = _chesspiece[id]._isRed;
}

void Board::init(bool bRedSide)
{
    // 初始化32个棋子
    for(int i=0; i<32; ++i)
    {
        _chesspiece[i].init(i);
    }
    if(bRedSide)
    {
        for(int i=0; i<32; ++i)
        {
            _chesspiece[i].rotate();
        }
    }
    _selectedId = -1;
    _bIsRedTurn = true;
    _bSide = bRedSide;
    update();
}

int Board::getChesspieceCountAtLine(int row1, int column1, int row2, int column2)
{
    int ret = 0;
    if(row1 != row2 && column1 != column2)
    {
        return -1;
    }

    if(row1 == row2 && column1 == column2)
    {
        return -1;
    }
    if(row1 == row2)
    {
        int min = column1 < column2 ? column1 : column2;
        int max = column1 < column2 ? column2 : column1;
        for(int column = min+1; column < max; ++column)
        {
            if(getChesspieceId(row1, column) != -1)
            {
                ++ret;
            }
        }
    }
    else
    {
        int min = row1 < row2 ? row1 : row2;
        int max = row1 < row2 ? row2 : row1;
        for(int row = min +1; row < max; ++row)
        {
            if(getChesspieceId(row,column1) != -1)
            {
                ++ret;
            }
        }
    }
    return ret;
}
