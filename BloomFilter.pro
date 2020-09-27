TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Bloom.cpp \
        Tests.cpp \
        UnitUniqueRandom.cpp \
        main.cpp

HEADERS += \
    Bloom.h \
    Tests.h \
    UnitUniqueRandom.h
