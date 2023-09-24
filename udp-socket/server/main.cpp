#include <QUdpSocket>
#include <QCoreApplication>
#include <iostream>

struct data {
    int m_value1;
    int m_value2;
    QString m_string;
};

class Server: public QObject {
public:
    Server(): udp_socket(new QUdpSocket(this)) {
        udp_socket->bind(QHostAddress::LocalHost, 4321);
        connect(udp_socket, &QUdpSocket::readyRead, this, &Server::read_data);
    }
private:
    char buffer[100'000];
    QUdpSocket *udp_socket;
private slots:
    void read_data() {
        if (!udp_socket->hasPendingDatagrams())
            return;
        udp_socket->readDatagram(buffer, 100'000);
        std::cerr << "Read data: {" << ((data *)buffer)->m_value1 << ", "
                  << ((data *)buffer)->m_value2 << ", "
                  << ((data *)buffer)->m_string.toStdString() << "}\n";
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    Server server;
    return a.exec();
}
