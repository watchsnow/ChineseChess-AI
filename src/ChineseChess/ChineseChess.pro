HEADERS += \
    Board.h \
    Step.h \
    Stone.h \
    ArtificialIntelligence.h

SOURCES += \
    Board.cpp \
    Main.cpp \
    Step.cpp \
    Stone.cpp \
    ArtificialIntelligence.cpp

QT  += widgets gui

QMAKE_CXXFLAGS += -Wno-unused-parameter
