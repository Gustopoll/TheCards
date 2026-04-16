QT       += core gui concurrent widgets

greaterThan(QT_MAJOR_VERSION, 4)

CONFIG += c++20

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    External/pugixml/pugixml.cpp \
    src/Drawing/Animations/animationmanager.cpp \
    src/Drawing/Animations/animationrotate.cpp \
    src/Drawing/Animations/animationscale.cpp \
    src/Drawing/Entities/drawingentity.cpp \
    src/Drawing/Widgets/drawingwidget.cpp \
    src/GameLogic/game.cpp \
    src/GameLogic/playercontroller.cpp \
    src/Screens/Dialogs/infodialog.cpp \
    src/Screens/GameScreen/gamescreen.cpp \
    src/Screens/Loadings/loadingscreen.cpp \
    src/Screens/MainScreen/mainscreen.cpp \
    src/Screens/SettingsScreen/settingsscreen.cpp \
    src/Screens/screencontroller.cpp \
    src/Screens/stylesheetcontroller.cpp \
    src/Settings/settingscontroller.cpp \
    src/Settings/settingswriter.cpp \
    src/Utils/datapreloader.cpp \
    src/Utils/eventhandler.cpp \
    src/main.cpp

HEADERS += \
    External/pugixml/pugiconfig.hpp \
    External/pugixml/pugixml.hpp \
    src/Drawing/Animations/IAnimation.h \
    src/Drawing/Animations/animationmanager.h \
    src/Drawing/Animations/animationrotate.h \
    src/Drawing/Animations/animationscale.h \
    src/Drawing/Constants.h \
    src/Drawing/Entities/drawingentity.h \
    src/Drawing/Widgets/drawingwidget.h \
    src/GameLogic/game.h \
    src/GameLogic/playercontroller.h \
    src/Screens/Dialogs/infodialog.h \
    src/Screens/GameScreen/gamescreen.h \
    src/Screens/Loadings/loadingscreen.h \
    src/Screens/MainScreen/mainscreen.h \
    src/Screens/SettingsScreen/settingsscreen.h \
    src/Screens/screencontroller.h \
    src/Screens/stylesheetcontroller.h \
    src/Settings/settingscontroller.h \
    src/Settings/settingswriter.h \
    src/Utils/datapreloader.h \
    src/Utils/eventhandler.h

FORMS += \
    src/Screens/Dialogs/infodialog.ui \
    src/Screens/GameScreen/gamescreen.ui \
    src/Screens/Loadings/loadingscreen.ui \
    src/Screens/MainScreen/mainscreen.ui \
    src/Screens/SettingsScreen/settingsscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
