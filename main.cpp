#include <QCoreApplication>
#include "serverhttp.h"
#include "serverweb.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ServerHttp serverHttp;
    serverHttp.setPort(8080);
    serverHttp.setPath(":/");
    serverHttp.start();

    ServerWeb serverWeb;
    serverWeb.initServer(8081);
    QObject::connect(&serverWeb,SIGNAL(textFromSocket(QString)),&serverWeb,SLOT(sendText(QString)));

    return a.exec();
}
