HEADERS += \
    Board.h \
    Chesspiece.h

SOURCES += \
    Board.cpp \
    Main.cpp \
    Chesspiece.cpp

QT  += widgets gui

QMAKE_CXXFLAGS += -Wno-unused-parameter
