#include <QCoreApplication>
#include "serverhttp.h"
#include "serverweb.h"

// Example of a request response function
void requestHandler(QTcpSocket *socket, const QString &method, const QString &path,
                    const QStringList &cookies, const QByteArray &requestData)
{
    qDebug() << Q_FUNC_INFO
             << "\n method:" << method          // GET, POST, PUT, OPTIONS, etc...
             << "\n path:" << path              // File name
             << "\n cookies:" << cookies
             << "\n request:" << requestData;   // Data embedded in the request

    // Response data
    QByteArray data("<h1> Hello World! </h1>");

    // Response header
    QByteArray response = ServerHttp::createHeader(path, data.size(), cookies);
    response.append(data);

    // Send response
    if (!socket) return;
    socket->write(response);
    socket->waitForBytesWritten(1000);
    socket->disconnectFromHost();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Create simple http-server
    ServerHttp serverHttp;
    serverHttp.setPort(8080);   // URL: http://127.0.0.1:8080
    serverHttp.setPath(":/");   // Path to the folder with the site files
    serverHttp.start();         // Opening a port for incoming requests

    // Set an incoming request handler
    // !!! If you need to send files from the set folder, comment out this line !!!
    QObject::connect(&serverHttp, &ServerHttp::request, requestHandler);

    // Create simple web-sockets-server
    ServerWeb serverWeb;
    serverWeb.initServer(8081);
    QObject::connect(&serverWeb,SIGNAL(textFromSocket(QString)),&serverWeb,SLOT(sendText(QString)));

    return a.exec();
}
