#include "downloader.h"

Downloader::Downloader(QObject* parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);
}

void Downloader::getData()
{
    QString url_str;
    url_str.append("https://ivan386.github.io/xml-site-index-test/with-xhtml-fragment.xml");
    QUrl url(url_str);
    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);
}

void Downloader::onResult(QNetworkReply* reply)
{
    if(reply->error())
    {
        qDebug() << "Error";
        qDebug() << reply->errorString();
    }
    else
    {
        QFile* file = new QFile("/home/artem/Projects/DownloaderHTTP/log.txt");
        if(file->open(QFile::WriteOnly))
        {
            file->write(reply->readAll());
            file->close();
            qDebug() << "Download is complete!";
            emit onReady();
        }
    }
}












