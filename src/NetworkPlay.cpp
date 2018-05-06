#include "NetworkPlay.h"

NetworkPlay::NetworkPlay(bool svr)
{
    _svr = NULL;
    _skt = NULL;
    if(svr) // 服务器
    {
        _svr = new QTcpServer(this);
        _svr->listen(QHostAddress::Any, 9999);
        connect(_svr, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));


    }
    // 客户端
    else
    {
        _skt = new QTcpSocket(this);
        _skt->connectToHost(QHostAddress("127.0.0.1"), 9999);
        connect(_skt, SIGNAL(readyRead()), this, SLOT(slotRecv()));
    }
}

NetworkPlay::~NetworkPlay()
{

}

void NetworkPlay::click(int id, int row, int col)
{
    if(_selectid == -1 && id != -1)
    {
        if(_s[id]._red != _bSide) // 点击的棋子必须要和你的边相同
        {
            return;
        }
    }
    Board::click(id, row, col);
    // 把信息发送给对方
    char sendClickEventBuf[4];
    sendClickEventBuf[0] = 2;
    // 实现对称关系 这样才是对方的行和列
    sendClickEventBuf[1] = 9 - row;
    sendClickEventBuf[2] = 8 - col;
    sendClickEventBuf[3] = id;
    _skt->write(sendClickEventBuf, 4);
}

void NetworkPlay::slotNewConnection()
{
    if(_skt) // 避免小三打扰
    {
        return;
    }
    // 建立一个通信的Socket
    _skt = _svr->nextPendingConnection(); // 返回一个QTcpSocket  // 类似于Accept函数
    connect(_skt, SIGNAL(readyRead()), this, SLOT(slotRecv()));
    // 给对方发送数据 合计一下
    char useRedOrBlackBuf[2];
    useRedOrBlackBuf[0] = 1;    // 第一个字节固定是1
    useRedOrBlackBuf[1] = 0;    // 第二个字节1, 或者0, 1 表示接收方走红棋, 0表示走黑棋
    // 通过Socket发送给对方
    _skt->write(useRedOrBlackBuf, 2); // 发送后等待客户端处理
    // 重新init
    init(useRedOrBlackBuf[1] == 0);
}

void NetworkPlay::slotRecv()
{
    QByteArray readArray = _skt->readAll();
    char cmd =  readArray[0];
    if(cmd == 1)
    {
        // 初始化
        char data = readArray[1];
        // 走黑色 旋转一下
        init(data == 1);
    }
    else if(cmd == 2)
    {
        int row = readArray[1];
        int col = readArray[2];
        int id  = readArray[3];
        Board::click(id, row, col);
    }
}
