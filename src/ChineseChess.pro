HEADERS += \
    Board.h \
    Step.h \
    Stone.h \
    ArtificialIntelligence.h \
    NetworkPlay.h

SOURCES += \
    Board.cpp \
    Main.cpp \
    Step.cpp \
    Stone.cpp \
    ArtificialIntelligence.cpp \
    NetworkPlay.cpp

QT  += widgets gui network

QMAKE_CXXFLAGS += -Wno-unused-parameter
