TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11
SOURCES += main.cpp \
    node.cpp \
    mcts.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    node.h \
    list.h \
    mcts.h

