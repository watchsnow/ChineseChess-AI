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

    // 定义32颗棋子 对应下棋的32颗棋子
    Chesspiece _chesspiece[32];

    // 返回棋盘行列对应的像素坐标
    QPoint center(int row, int column);

    QPoint center(int id);

    void paintEvent(QPaintEvent *);

    void drawChesspiece(QPainter& painter, int id);

    // 实现棋子的走动
    // void mousePressEvent(QMouseEvent *);         // 鼠标点下
    void mouseReleaseEvent(QMouseEvent *event);     // 鼠标释放 移动象棋 用这个

    // 棋盘的像素值 要转为象棋的行列值 (效率不高应该改进)
    bool getRowColumn(QPoint boardPixelPoint,int& row, int& column);

    // 是否能移动
    bool canMoveRules(int canMoveId, int row, int column, int killId);

    // 各种棋子移动的规则
    bool generalsCanMoveRules   (int canMoveId, int row, int column, int killId);
    bool guardsCanMoveRules     (int canMoveId, int row, int column, int killId);
    bool ministersCanMoveRules  (int canMoveId, int row, int column, int killId);
    bool horsesCanMoveRules     (int canMoveId, int row, int column, int killId);
    bool chariotsCanMoveRules   (int canMoveId, int row, int column, int killId);
    bool cannonsCanMoveRules    (int canMoveId, int row, int column, int killId);
    bool soldiersCanMoveRules   (int canMoveId, int row, int column, int killId);

    // 获取关系值
    int relation(int row1, int colcolumn1, int row, int column);
    int getChesspieceId(int row, int column);
    bool isBottomSide(int id);
    void init(bool bRedSide);
    // 获取这连个坐标点之间的象棋个数
    int getChesspieceCountAtLine(int row1, int column1, int row2, int column2);
public:
    int _r;             // 棋子的半径
    int _selectedId;    // 记录被选中棋子的标记
    bool _bIsRedTurn;   // 轮到谁走了
    bool _bSide;

signals:

public slots:
};

#endif // BOARD_H
