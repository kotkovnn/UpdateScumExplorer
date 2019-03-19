#include <QCoreApplication>
#include <QtNetwork>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "Downloading update...";
    QFile localfile("Scum-LogExplorer.exe");
    //if (!localfile.open(QIODevice::Truncate)) exit(1);
    localfile.open(QIODevice::WriteOnly);

    QNetworkAccessManager manager;
    manager.setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
    QString adress = "https://drive.google.com/uc?export=download&confirm=no_antivirus&id=1g1j3Fuh-dzV5JAsuAHk3boxnbAiyVhfZ";
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(adress)));
    QEventLoop event;
    QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    QByteArray newData = response->readAll();
    localfile.write(newData);
    localfile.close();
    qDebug() << "Updated :))";

    return a.exec();
}
