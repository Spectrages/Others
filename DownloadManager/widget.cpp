#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    downloader = new Downloader();
    connect(ui->pushButton, &QPushButton::clicked, downloader, &Downloader::getData);
    connect(downloader, &Downloader::onReady, this, &Widget::readFile);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::readFile()
{
    QFile file("/home/artem/Projects/DownloaderHTTP/log.txt");
    if(!file.open(QIODevice::ReadOnly))
        return;
    ui->textEdit->setText(file.readAll());
}

