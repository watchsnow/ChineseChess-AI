#ifndef ARTIFICIALINTELLIGENCE_H
#define ARTIFICIALINTELLIGENCE_H

#include "Board.h"

class ArtificialIntelligence : public Board
{
    Q_OBJECT // 使用槽函数 加上这个宏
public:
    ArtificialIntelligence()
    {
         _level = 1; // 考虑的层次
    }

    virtual void click(int id, int row, int col);
    Step* getBestMove();
    void getAllPossibleSteps(QVector<Step*>& steps);  // 这是可以优化一下(是一个优化的方向)
    void fakeMove(Step* step);
    void unFakeMove(Step* step);
    int calcScore();       // 局面分也太粗糙 可以继续优化  其实每个棋子在每个位置上分值是不一样的
    int getMinScore(int level, int curMaxScore);
    int getMaxScore(int level, int curMinScore);

    /*
    数据结构也是优化的方向 比如 象棋都是用得整形(就要优化)
    还有canmove 也可优化 都会被调用多次
    */
public slots:
    void computerMove();

public:
    int _level;
};

#endif // ARTIFICIALINTELLIGENCE_H
