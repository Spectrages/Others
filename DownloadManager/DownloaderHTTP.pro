QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DownloadHttp
TEMPLATE = app


SOURCES += main.cpp\
    downloader.cpp \
    widget.cpp
    downloader.cpp

HEADERS  += \
    downloader.h \
    downloader.h \
    widget.h

FORMS    += \
    widget.ui
