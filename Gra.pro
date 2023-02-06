TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt


#WINDOWS
# put SFML file in the same location as project
LIBS += -L"..\SFML-2.5.1\lib" #change this
LIBS += -L"..\SFML-2.5.1\bin" #change this

#MAC
#LIBS += -L"/usr/local/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug  , debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

#WINDOWS
INCLUDEPATH += "..\SFML-2.5.1\include" #change this
DEPENDPATH += "..\SFML-2.5.1\include" #change this

SOURCES += \
        animation.cpp \
        enemy.cpp \
        entity.cpp \
        main.cpp \
        map.cpp \
        physics.cpp \
        player.cpp \
        projectile.cpp \
        tile.cpp

HEADERS += \
    animation.h \
    enemy.h \
    entity.h \
    map.h \
    physics.h \
    player.h \
    projectile.h \
    tile.h
