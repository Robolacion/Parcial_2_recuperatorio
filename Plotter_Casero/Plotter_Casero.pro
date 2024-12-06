QT -= gui
TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    plotter_casero.cpp

HEADERS += \
    plotter_casero.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
LIBS += -L"C:\DLLS\QcustomPlot"
LIBS += -L"C:\DLLS\MuParser"
INCLUDEPATH +="C:\DLLS\QcustomPlot"
INCLUDEPATH +="C:\DLLS\MuParser"
LIBS += -lqcustomplotd2
LIBS += -lMuParserDLL_Make
