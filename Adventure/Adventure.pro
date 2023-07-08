QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutFight.cpp \
    game_map.cpp \
    game_story_window.cpp \
    get_start.cpp \
    help_window.cpp \
    lose_window.cpp \
    m_Button.cpp \
    main.cpp \
    mainwindow.cpp \
    smallMap.cpp \
    victory_window.cpp

HEADERS += \
    aboutFight.h \
    game_map.h \
    game_story_window.h \
    get_start.h \
    help_window.h \
    lose_window.h \
    m_Button.h \
    mainwindow.h \
    smallMap.h \
    victory_window.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
