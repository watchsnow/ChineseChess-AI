#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QString>

class Chesspiece
{
public:
    Chesspiece();
    ~Chesspiece();
    // 给棋子添加一些属性
    typedef enum tagType{
        Generals, // 将
        Guards,   // 士
        Ministers,// 象
        Horses,   // 马
        Chariots, // 车
        Cannons,  // 炮
        Soldiers  // 卒
    }TYPE;
    // 变换最大的
    int _row;
    int _column;
    TYPE _type;

    // 下面三个都是固定的
    int _id;
    bool _isDead;
    bool _isRed;

    QString getText();
    void init(int id);
    void rotate();
};

#endif // CHESSPIECE_H
