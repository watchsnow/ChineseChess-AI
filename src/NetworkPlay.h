#ifndef NETWORKPLAY_H
#define NETWORKPLAY_H

#include "Board.h"
#include <QTcpServer>
#include <QTcpSocket>

/*
无服务器的 既可以做服务器 又可以做客户端

可能给对方发送的消息
1. 执红方还是执黑方, 这个信息有服务器发出, 客户端接收
   组织报文结构
   第一个字节固定是1, 第二个字节1, 或者0, 1 表示接收方走红棋, 0表示走黑棋
2. 发送点击信息
   第一个字节固定为2, 第二个字节为坐标row, 第三个字节是坐标列, 第四个字节为点击的旗子ID(有可能是等于-1)
*/
class NetworkPlay : public Board
{
    Q_OBJECT
public:
    NetworkPlay(bool svr);
    ~NetworkPlay();
    void click(int id, int row, int col); // 重载一个虚函数
public:
    // 作为服务器的话连两个都要用 如果作为客户端的话 只用下面那个
    QTcpServer* _svr;
    QTcpSocket* _skt;
public  slots:
    void slotNewConnection();
    void slotRecv();
};

#endif // NETWORKPLAY_H
