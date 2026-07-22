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
	src/gui/base/data/BaseExtraConverter.cpp \
	src/gui/base/data/BaseExtraList.cpp \
	src/gui/base/data/BaseSettings.cpp \
	src/gui/base/widgets/BaseButtonAdd.cpp \
	src/gui/base/widgets/BaseButtonCollapse.cpp \
	src/gui/base/widgets/BaseButtonExpand.cpp \
	src/gui/base/widgets/BaseButtonSave.cpp \
	src/gui/base/widgets/BaseButtonSettings.cpp \
	src/gui/base/widgets/BaseButtonShow.cpp \
	src/gui/base/widgets/BaseComboBox.cpp \
	src/gui/base/widgets/BaseComboEdit.cpp \
	src/gui/base/widgets/BaseWidgetChart.cpp \
	src/gui/base/widgets/BaseWidgetControl.cpp \
	src/gui/base/widgets/BaseWidgetCsvSettings.cpp \
	src/gui/base/widgets/BaseWidgetData.cpp \
	src/gui/base/widgets/BaseWidgetExtra.cpp \
	src/gui/base/widgets/BaseWidgetExtraList.cpp \
	src/gui/base/widgets/BaseWidgetMain.cpp \
	src/gui/base/widgets/BaseWidgetRating.cpp \
	src/gui/base/widgets/BaseWidgetSettings.cpp \
	src/gui/base/widgets/BaseWidgetSummary.cpp \
	src/gui/base/widgets/BaseWidgetTree.cpp \
	src/gui/base/widgets/BaseWidgetTreeItem.cpp \
	src/gui/bike/data/BikeDataConverter.cpp \
	src/gui/bike/data/BikeDataList.cpp \
	src/gui/bike/data/BikeSettings.cpp \
	src/gui/bike/data/BikeTripConverter.cpp \
	src/gui/bike/data/BikeTripList.cpp \
	src/gui/bike/widgets/BikeWidgetChart.cpp \
	src/gui/bike/widgets/BikeWidgetControl.cpp \
	src/gui/bike/widgets/BikeWidgetData.cpp \
	src/gui/bike/widgets/BikeWidgetDataList.cpp \
	src/gui/bike/widgets/BikeWidgetMain.cpp \
	src/gui/bike/widgets/BikeWidgetSettings.cpp \
	src/gui/bike/widgets/BikeWidgetSummary.cpp \
	src/gui/bike/widgets/BikeWidgetTrip.cpp \
	src/gui/bike/widgets/BikeWidgetTripList.cpp \
	src/gui/books/data/BooksDataConverter.cpp \
	src/gui/books/data/BooksDataList.cpp \
	src/gui/books/data/BooksSettings.cpp \
	src/gui/books/widgets/BooksWidgetChart.cpp \
	src/gui/books/widgets/BooksWidgetControl.cpp \
	src/gui/books/widgets/BooksWidgetData.cpp \
	src/gui/books/widgets/BooksWidgetDataList.cpp \
	src/gui/books/widgets/BooksWidgetMain.cpp \
	src/gui/books/widgets/BooksWidgetSettings.cpp \
	src/gui/books/widgets/BooksWidgetSummary.cpp \
	src/gui/flights/data/FlightsDataConverter.cpp \
	src/gui/flights/data/FlightsDataList.cpp \
	src/gui/flights/data/FlightsSettings.cpp \
	src/gui/flights/widgets/FlightsWidgetChart.cpp \
	src/gui/flights/widgets/FlightsWidgetControl.cpp \
	src/gui/flights/widgets/FlightsWidgetData.cpp \
	src/gui/flights/widgets/FlightsWidgetDataList.cpp \
	src/gui/flights/widgets/FlightsWidgetMain.cpp \
	src/gui/flights/widgets/FlightsWidgetSettings.cpp \
	src/gui/flights/widgets/FlightsWidgetSummary.cpp \
	src/gui/games/data/GamesDataConverter.cpp \
	src/gui/games/data/GamesDataList.cpp \
	src/gui/games/data/GamesSettings.cpp \
	src/gui/games/widgets/GamesWidgetChart.cpp \
	src/gui/games/widgets/GamesWidgetControl.cpp \
	src/gui/games/widgets/GamesWidgetData.cpp \
	src/gui/games/widgets/GamesWidgetDataList.cpp \
	src/gui/games/widgets/GamesWidgetMain.cpp \
	src/gui/games/widgets/GamesWidgetSettings.cpp \
	src/gui/games/widgets/GamesWidgetSummary.cpp \
	src/gui/music/data/MusicDataConverter.cpp \
	src/gui/music/data/MusicDataList.cpp \
	src/gui/music/data/MusicSettings.cpp \
	src/gui/music/widgets/MusicWidgetChart.cpp \
	src/gui/music/widgets/MusicWidgetControl.cpp \
	src/gui/music/widgets/MusicWidgetData.cpp \
	src/gui/music/widgets/MusicWidgetDataList.cpp \
	src/gui/music/widgets/MusicWidgetMain.cpp \
	src/gui/music/widgets/MusicWidgetSettings.cpp \
	src/gui/music/widgets/MusicWidgetSummary.cpp \
	src/gui/player/data/PlayerLibrary.cpp \
	src/gui/player/data/PlayerSettings.cpp \
	src/gui/player/storage/PlayerStorage.cpp \
	src/gui/player/storage/PlayerXmlParser.cpp \
	src/gui/player/widgets/PlayerWidgetChart.cpp \
	src/gui/player/widgets/PlayerWidgetControl.cpp \
	src/gui/player/widgets/PlayerWidgetDataList.cpp \
	src/gui/player/widgets/PlayerWidgetMain.cpp \
	src/gui/player/widgets/PlayerWidgetSettings.cpp \
	src/gui/player/widgets/PlayerWidgetSummary.cpp \
	src/gui/trekking/data/TrekkingDataConverter.cpp \
	src/gui/trekking/data/TrekkingDataList.cpp \
	src/gui/trekking/data/TrekkingSettings.cpp \
	src/gui/trekking/widgets/TrekkingWidgetChart.cpp \
	src/gui/trekking/widgets/TrekkingWidgetControl.cpp \
	src/gui/trekking/widgets/TrekkingWidgetData.cpp \
	src/gui/trekking/widgets/TrekkingWidgetDataList.cpp \
	src/gui/trekking/widgets/TrekkingWidgetMain.cpp \
	src/gui/trekking/widgets/TrekkingWidgetSettings.cpp \
	src/gui/trekking/widgets/TrekkingWidgetSummary.cpp \
	src/storage/Storage.cpp \
	src/storage/csv/CsvSettings.cpp \
	src/storage/csv/CsvStorage.cpp

HEADERS += \
	src/HobbyTracker.h \
	src/common/Global.h \
	src/common/Helper.h \
	src/gui/MainWindow.h \
	src/gui/base/data/BaseData.h \
	src/gui/base/data/BaseDataList.h \
	src/gui/base/data/BaseExtra.h \
	src/gui/base/data/BaseExtraConverter.h \
	src/gui/base/data/BaseExtraList.h \
	src/gui/base/data/BaseSettings.h \
	src/gui/base/widgets/BaseButtonAdd.h \
	src/gui/base/widgets/BaseButtonCollapse.h \
	src/gui/base/widgets/BaseButtonExpand.h \
	src/gui/base/widgets/BaseButtonSave.h \
	src/gui/base/widgets/BaseButtonSettings.h \
	src/gui/base/widgets/BaseButtonShow.h \
	src/gui/base/widgets/BaseComboBox.h \
	src/gui/base/widgets/BaseComboEdit.h \
	src/gui/base/widgets/BaseWidgetChart.h \
	src/gui/base/widgets/BaseWidgetControl.h \
	src/gui/base/widgets/BaseWidgetCsvSettings.h \
	src/gui/base/widgets/BaseWidgetData.h \
	src/gui/base/widgets/BaseWidgetExtra.h \
	src/gui/base/widgets/BaseWidgetExtraList.h \
	src/gui/base/widgets/BaseWidgetMain.h \
	src/gui/base/widgets/BaseWidgetRating.h \
	src/gui/base/widgets/BaseWidgetSettings.h \
	src/gui/base/widgets/BaseWidgetSummary.h \
	src/gui/base/widgets/BaseWidgetTree.h \
	src/gui/base/widgets/BaseWidgetTreeItem.h \
	src/gui/bike/common/BikeCommon.h \
	src/gui/bike/data/BikeData.h \
	src/gui/bike/data/BikeDataConverter.h \
	src/gui/bike/data/BikeDataList.h \
	src/gui/bike/data/BikeSettings.h \
	src/gui/bike/data/BikeTrip.h \
	src/gui/bike/data/BikeTripConverter.h \
	src/gui/bike/data/BikeTripList.h \
	src/gui/bike/widgets/BikeWidgetChart.h \
	src/gui/bike/widgets/BikeWidgetControl.h \
	src/gui/bike/widgets/BikeWidgetData.h \
	src/gui/bike/widgets/BikeWidgetDataList.h \
	src/gui/bike/widgets/BikeWidgetMain.h \
	src/gui/bike/widgets/BikeWidgetSettings.h \
	src/gui/bike/widgets/BikeWidgetSummary.h \
	src/gui/bike/widgets/BikeWidgetTrip.h \
	src/gui/bike/widgets/BikeWidgetTripList.h \
	src/gui/books/common/BooksCommon.h \
	src/gui/books/data/BooksData.h \
	src/gui/books/data/BooksDataConverter.h \
	src/gui/books/data/BooksDataList.h \
	src/gui/books/data/BooksSettings.h \
	src/gui/books/widgets/BooksWidgetChart.h \
	src/gui/books/widgets/BooksWidgetControl.h \
	src/gui/books/widgets/BooksWidgetData.h \
	src/gui/books/widgets/BooksWidgetDataList.h \
	src/gui/books/widgets/BooksWidgetMain.h \
	src/gui/books/widgets/BooksWidgetSettings.h \
	src/gui/books/widgets/BooksWidgetSummary.h \
	src/gui/flights/common/FlightsCommon.h \
	src/gui/flights/data/FlightsData.h \
	src/gui/flights/data/FlightsDataConverter.h \
	src/gui/flights/data/FlightsDataList.h \
	src/gui/flights/data/FlightsSettings.h \
	src/gui/flights/widgets/FlightsWidgetChart.h \
	src/gui/flights/widgets/FlightsWidgetControl.h \
	src/gui/flights/widgets/FlightsWidgetData.h \
	src/gui/flights/widgets/FlightsWidgetDataList.h \
	src/gui/flights/widgets/FlightsWidgetMain.h \
	src/gui/flights/widgets/FlightsWidgetSettings.h \
	src/gui/flights/widgets/FlightsWidgetSummary.h \
	src/gui/games/common/GamesCommon.h \
	src/gui/games/data/GamesData.h \
	src/gui/games/data/GamesDataConverter.h \
	src/gui/games/data/GamesDataList.h \
	src/gui/games/data/GamesSettings.h \
	src/gui/games/widgets/GamesWidgetChart.h \
	src/gui/games/widgets/GamesWidgetControl.h \
	src/gui/games/widgets/GamesWidgetData.h \
	src/gui/games/widgets/GamesWidgetDataList.h \
	src/gui/games/widgets/GamesWidgetMain.h \
	src/gui/games/widgets/GamesWidgetSettings.h \
	src/gui/games/widgets/GamesWidgetSummary.h \
	src/gui/music/common/MusicCommon.h \
	src/gui/music/data/MusicData.h \
	src/gui/music/data/MusicDataConverter.h \
	src/gui/music/data/MusicDataList.h \
	src/gui/music/data/MusicSettings.h \
	src/gui/music/widgets/MusicWidgetChart.h \
	src/gui/music/widgets/MusicWidgetControl.h \
	src/gui/music/widgets/MusicWidgetData.h \
	src/gui/music/widgets/MusicWidgetDataList.h \
	src/gui/music/widgets/MusicWidgetMain.h \
	src/gui/music/widgets/MusicWidgetSettings.h \
	src/gui/music/widgets/MusicWidgetSummary.h \
	src/gui/player/common/PlayerCommon.h \
	src/gui/player/data/PlayerAlbum.h \
	src/gui/player/data/PlayerArtist.h \
	src/gui/player/data/PlayerLibrary.h \
	src/gui/player/data/PlayerSettings.h \
	src/gui/player/data/PlayerTrack.h \
	src/gui/player/storage/PlayerStorage.h \
	src/gui/player/storage/PlayerXmlParser.h \
	src/gui/player/widgets/PlayerWidgetChart.h \
	src/gui/player/widgets/PlayerWidgetControl.h \
	src/gui/player/widgets/PlayerWidgetDataList.h \
	src/gui/player/widgets/PlayerWidgetMain.h \
	src/gui/player/widgets/PlayerWidgetSettings.h \
	src/gui/player/widgets/PlayerWidgetSummary.h \
	src/gui/trekking/common/TrekkingCommon.h \
	src/gui/trekking/data/TrekkingData.h \
	src/gui/trekking/data/TrekkingDataConverter.h \
	src/gui/trekking/data/TrekkingDataList.h \
	src/gui/trekking/data/TrekkingSettings.h \
	src/gui/trekking/widgets/TrekkingWidgetChart.h \
	src/gui/trekking/widgets/TrekkingWidgetControl.h \
	src/gui/trekking/widgets/TrekkingWidgetData.h \
	src/gui/trekking/widgets/TrekkingWidgetDataList.h \
	src/gui/trekking/widgets/TrekkingWidgetMain.h \
	src/gui/trekking/widgets/TrekkingWidgetSettings.h \
	src/gui/trekking/widgets/TrekkingWidgetSummary.h \
	src/storage/Storage.h \
	src/storage/csv/CsvData.h \
	src/storage/csv/CsvSettings.h \
	src/storage/csv/CsvStorage.h
