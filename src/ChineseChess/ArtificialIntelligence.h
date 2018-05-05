#ifndef ARTIFICIALINTELLIGENCE_H
#define ARTIFICIALINTELLIGENCE_H

#include "Board.h"

class ArtificialIntelligence : public Board
{
public:
    virtual void click(int id, int row, int col);

    Step* getBestMove();
    void getAllPossibleSteps(QVector<Step*>& steps);
    void fakeMove(Step* step);
    void unFakeMove(Step* step);
    int calcScore();
    int getMinScore();
};

#endif // ARTIFICIALINTELLIGENCE_H
