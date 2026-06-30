QT += core gui widgets charts

CONFIG += c++20

QMAKE_CXXFLAGS += -Wall -Wextra -pedantic-errors

# disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

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
	src/gui/MainWindow.cpp \
	src/gui/base/data/BaseSettings.cpp \
	src/gui/base/widgets/BaseButtonCollapse.cpp \
	src/gui/base/widgets/BaseButtonExpand.cpp \
	src/gui/base/widgets/BaseButtonSave.cpp \
	src/gui/base/widgets/BaseButtonSettings.cpp \
	src/gui/base/widgets/BaseButtonShow.cpp \
	src/gui/base/widgets/BaseWidgetChart.cpp \
	src/gui/base/widgets/BaseWidgetControl.cpp \
	src/gui/base/widgets/BaseWidgetCsvSettings.cpp \
	src/gui/base/widgets/BaseWidgetMain.cpp \
	src/gui/base/widgets/BaseWidgetSettings.cpp \
	src/gui/base/widgets/BaseWidgetSummary.cpp \
	src/gui/base/widgets/BaseWidgetTree.cpp \
	src/gui/base/widgets/BaseWidgetTreeItem.cpp \
	src/gui/books/data/BooksConverter.cpp \
	src/gui/books/data/BooksDataList.cpp \
	src/gui/books/data/BooksSettings.cpp \
	src/gui/books/widgets/BooksWidgetChart.cpp \
	src/gui/books/widgets/BooksWidgetControl.cpp \
	src/gui/books/widgets/BooksWidgetList.cpp \
	src/gui/books/widgets/BooksWidgetMain.cpp \
	src/gui/books/widgets/BooksWidgetSettings.cpp \
	src/gui/books/widgets/BooksWidgetSummary.cpp \
	src/gui/games/widgets/GamesWidgetMain.cpp \
	src/storage/Storage.cpp \
	src/storage/csv/CsvSettings.cpp \
	src/storage/csv/CsvStorage.cpp

HEADERS += \
	src/HobbyTracker.h \
	src/common/Global.h \
	src/common/Helper.h \
	src/gui/MainWindow.h \
	src/gui/base/data/BaseDataList.h \
	src/gui/base/data/BaseSettings.h \
	src/gui/base/widgets/BaseButtonCollapse.h \
	src/gui/base/widgets/BaseButtonExpand.h \
	src/gui/base/widgets/BaseButtonSave.h \
	src/gui/base/widgets/BaseButtonSettings.h \
	src/gui/base/widgets/BaseButtonShow.h \
	src/gui/base/widgets/BaseWidgetChart.h \
	src/gui/base/widgets/BaseWidgetControl.h \
	src/gui/base/widgets/BaseWidgetCsvSettings.h \
	src/gui/base/widgets/BaseWidgetMain.h \
	src/gui/base/widgets/BaseWidgetSettings.h \
	src/gui/base/widgets/BaseWidgetSummary.h \
	src/gui/base/widgets/BaseWidgetTree.h \
	src/gui/base/widgets/BaseWidgetTreeItem.h \
	src/gui/books/common/BooksCommon.h \
	src/gui/books/data/BooksConverter.h \
	src/gui/books/data/BooksData.h \
	src/gui/books/data/BooksDataList.h \
	src/gui/books/data/BooksSettings.h \
	src/gui/books/widgets/BooksWidgetChart.h \
	src/gui/books/widgets/BooksWidgetControl.h \
	src/gui/books/widgets/BooksWidgetList.h \
	src/gui/books/widgets/BooksWidgetMain.h \
	src/gui/books/widgets/BooksWidgetSettings.h \
	src/gui/books/widgets/BooksWidgetSummary.h \
	src/gui/games/widgets/GamesWidgetMain.h \
	src/storage/Storage.h \
	src/storage/csv/CsvData.h \
	src/storage/csv/CsvSettings.h \
	src/storage/csv/CsvStorage.h
