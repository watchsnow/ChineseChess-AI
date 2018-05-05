#include "ArtificialIntelligence.h"

void ArtificialIntelligence::click(int id, int row, int col)
{
    if(!this->_bRedTurn)
    {
        // 不是红色的走 就不要乱点 点了也不会有任何效果
        return;
    }
    Board::click(id, row, col);
    if(!this->_bRedTurn)
    {
        // 电脑走
        Step* step = getBestMove();
        moveStone(step->_moveid, step->_killid, step->_rowTo, step->_colTo);
        delete step; // 避免了内存泄漏
    }
}

Step* ArtificialIntelligence::getBestMove()
{
    /*
    1. 看看有哪些步骤可以走
    2. 试着走一下
    3. 评估走的结果
    4. 去最好的结果作为参考
    */
    // 获取可能移动的步数
    // 1. 看看有哪些步骤可以走
    QVector<Step*> steps;
    getAllPossibleSteps(steps);

    // 2. 试着走一下  通过迭代器 遍历走法
    // 3. 评估走的结果
    int maxScore = -100000;
    Step* ret = NULL;
    //for(QVector<Step*>::iterator it = steps.begin(); it!=steps.end(); ++it)
    while(steps.count())
    {
        //Step* step = *it;
        Step* step = steps.back();
        steps.removeLast();
        // 取出 steps
        // 设计一个假的Move(step);
        fakeMove(step);    // 算好了
        // 计算局面分
        //int score = calcScore(); // 越高越好
        int score = getMinScore();
        unFakeMove(step);  // 拿回来
        if(score > maxScore)
        {
            maxScore = score; // 最高Score对应的Step 就是我们需要参考的Step
            if(ret)
            {
                delete ret;
            }
            ret = step;       // 这个Step就是我们要的
        }
        else
        {
            delete step; // 不能随便丢掉
        }
    }

    // 4. 去最好的结果作为参考
    return ret;

}

void ArtificialIntelligence::getAllPossibleSteps(QVector<Step *> &steps)
{
    // 增加找红棋的
    int min=16, max=32;
    if(this->_bRedTurn)
    {
        min=0, max = 16;
    }

    // 找黑棋的
    // 遍历所有的棋子 看看哪里可以走
    for(int i = min; i< max; ++i) // 遍历黑棋
    {
        // 去掉死棋
        if(_s[i]._dead)
        {
            continue;
        }
        for(int row=0; row<=9; ++row)
        {
            for(int col=0; col<=8; ++col)
            {
                int killId = this->getStoneId(row, col); // 看看目标行列上有没有旗子
                // 判断是否颜色相同
                if(sameColor(killId, i))
                {
                    continue;  // 应为不能出现你走在一个位置上 这个位置上还是自己人的情况
                }
                if(canMove(i, killId, row, col))  // 合法的移动  存入集合
                {
                    saveStep(i, killId, row, col, steps);
                }
            }
        }
    }
}

// 挪过去
void ArtificialIntelligence::fakeMove(Step *step)
{
    //step->_killid
    killStone(step->_killid); // 杀死棋子
    moveStone(step->_moveid, step->_rowTo, step->_colTo);
}

// 挪回来
void ArtificialIntelligence::unFakeMove(Step *step)
{
    // 复活棋子
    reliveStone(step->_killid);
    moveStone(step->_moveid, step->_rowFrom, step->_colFrom);
}

// 评价局面分
int ArtificialIntelligence::calcScore()
{
    int redChessTotalScore = 0;
    int blkChessTotalScore = 0;
    // 给每种棋子定义一个分数
    // enum TYPE{CHE, MA, PAO, BING, JIANG, SHI, XIANG};
    static int chessScore[] = {100, 50, 50, 20, 1500, 10, 10};
    // 黑棋分的总数 - 红旗分的总数
    // 累加红棋
    for(int i = 0; i<16; ++i)
    {
        if(_s[i]._dead)
        {
            continue;
        }
        redChessTotalScore += chessScore[_s[i]._type];
    }

    // 累加黑棋
    for(int i = 16; i<32; ++i)
    {
        if(_s[i]._dead)
        {
            continue;
        }
        blkChessTotalScore += chessScore[_s[i]._type];
    }
    return blkChessTotalScore - redChessTotalScore;
}

int ArtificialIntelligence::getMinScore()
{
    QVector<Step*> steps;
    getAllPossibleSteps(steps); // 是红棋的possibleMove
    int minScore = 10000000;
    //for(QVector<Step*>::iterator it = steps.begin(); it!=steps.end(); ++it)
    while(steps.count())
    {
        Step* step = steps.back();
        steps.removeLast(); // 清理内存
        // 取出 steps
        // 设计一个假的Move(step);
        fakeMove(step);    // 算好了
        // 计算局面分
        int score = calcScore(); // 越高越好
        unFakeMove(step);  // 拿回来
        if(score < minScore)
        {
            minScore=score;
        }
        delete step; // 释放内存
    }
    return minScore;
}
