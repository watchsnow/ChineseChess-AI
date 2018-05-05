#ifndef ARTIFICIALINTELLIGENCE_H
#define ARTIFICIALINTELLIGENCE_H

#include "Board.h"

class ArtificialIntelligence : public Board
{
    Q_OBJECT // 使用槽函数 加上这个宏
public:
    ArtificialIntelligence()
    {
         _level = 4; // 考虑的层次
    }

    virtual void click(int id, int row, int col);
    Step* getBestMove();
    void getAllPossibleSteps(QVector<Step*>& steps);
    void fakeMove(Step* step);
    void unFakeMove(Step* step);
    int calcScore();
    int getMinScore(int level);
    int getMaxScore(int level);

public slots:
    void computerMove();

public:
    int _level;
};

#endif // ARTIFICIALINTELLIGENCE_H
