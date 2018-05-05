#include <QApplication>
#include "ArtificialIntelligence.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    ArtificialIntelligence board;
    board.show();
    return app.exec();
}
