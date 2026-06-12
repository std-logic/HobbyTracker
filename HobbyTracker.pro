QT += core gui widgets charts

CONFIG += c++20

QMAKE_CXXFLAGS += -Wall -Wextra -pedantic-errors

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000 # disables all the APIs deprecated before Qt 6.0.0

TARGET = HobbyTracker
DESTDIR = $$PWD/bin

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Automatic coping Qt libs into bin folder
# win32: CONFIG(release, debug|release) {
# QMAKE_POST_LINK += $$quote($$[QT_INSTALL_BINS]/windeployqt.exe --no-compiler-runtime $$DESTDIR)
# }

INCLUDEPATH += \
	src

SOURCES += \
	src/main.cpp \
	src/HobbyTracker.cpp \
	src/MainWindow.cpp

HEADERS += \
	src/HobbyTracker.h \
	src/MainWindow.h
