QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

TARGET = CombatModuleWidget
TEMPLATE = app

QMAKE_EXTRA_TARGETS += before_build makefilehook

makefilehook.target = $(MAKEFILE)
makefilehook.depends = .beforebuild

PRE_TARGETDEPS += .beforebuild

before_build.target = .beforebuild
before_build.depends = FORCE
before_build.commands = chcp 1251

SOURCES += \
    main.cpp\
    CombatModuleWidget.cpp \
    Compass.cpp

HEADERS += \
    CombatModuleWidget.h \
    Compass.h

RESOURCES += \
    resources.qrc

