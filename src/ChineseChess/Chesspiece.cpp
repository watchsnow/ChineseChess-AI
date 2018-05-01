#include "Chesspiece.h"

Chesspiece::Chesspiece()
{

}

Chesspiece::~Chesspiece()
{

}

// 根据类型返回名字
QString Chesspiece::getText()
{
    switch (this->_type) {
    case Generals:  return "将";
    case Guards:    return "士";
    case Ministers: return "象";
    case Horses:    return "马";
    case Chariots:  return "车";
    case Cannons:   return "炮";
    case Soldiers:  return "卒";
    }
    return "错误";
}

void Chesspiece::init(int id)
{
    // 定义一张表(就是定义一个结构体)
    struct {
            int row, col;
           Chesspiece::TYPE type;
    }pos[16] = {
    {0, 0, Chesspiece::Chariots},
    {0, 1, Chesspiece::Horses},
    {0, 2, Chesspiece::Ministers},
    {0, 3, Chesspiece::Guards},
    {0, 4, Chesspiece::Generals},
    {0, 5, Chesspiece::Guards},
    {0, 6, Chesspiece::Ministers},
    {0, 7, Chesspiece::Horses},
    {0, 8, Chesspiece::Chariots},

    {2, 1, Chesspiece::Cannons},
    {2, 7, Chesspiece::Cannons},
    {3, 0, Chesspiece::Soldiers},
    {3, 2, Chesspiece::Soldiers},
    {3, 4, Chesspiece::Soldiers},
    {3, 6, Chesspiece::Soldiers},
    {3, 8, Chesspiece::Soldiers},
    };
    _id = id;
    _isDead = false;
    _isRed = id < 16;  // red   black.id > (16) > red.id

    if(id < 16)
    {
        _row    = pos[id].row;
        _column = pos[id].col;
        _type   = pos[id].type;
    }
    else
    {
        _row    = 9-pos[id-16].row;
        _column = 8-pos[id-16].col;
        _type   = pos[id-16].type;
    }
}

