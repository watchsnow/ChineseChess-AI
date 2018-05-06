#include <QApplication>
#include "ArtificialIntelligence.h"
#include "NetworkPlay.h"
#include <QMessageBox>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    // 弹个对话框选择是作为服务器还是作为客户端
    QMessageBox::StandardButton ret;
    ret = QMessageBox::question(NULL, "Server or client", "作为服务器启动");
    bool bSvr = false;
    if(QMessageBox::Yes == ret)
    {
        // 就是服务器
        bSvr = true;
    }
//    else
//    {
//        // 客户端
//    }
    NetworkPlay board(bSvr);
    board.show();
    return app.exec();
}
