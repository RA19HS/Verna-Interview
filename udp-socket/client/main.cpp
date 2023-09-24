#include <QTimer>
#include <QUdpSocket>
#include <QCoreApplication>

struct data {
    int m_value1;
    int m_value2;
    QString m_string;
};

class Client: public QObject {
public:
    Client(): udp_socket(new QUdpSocket(this)), timer_1sec(new QTimer(this)) {
        connect(timer_1sec, &QTimer::timeout, this, &Client::send_datagram);
    }
    void begin_sending_data() {
        timer_1sec->start(1000);
    }
private:
    const char *data = "SALAM!";
    QUdpSocket *udp_socket;
    QTimer *timer_1sec;
private slots:
    void send_datagram() {
        udp_socket->writeDatagram(data, sizeof(data), QHostAddress::LocalHost, 4321);
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    Client client;
    client.begin_sending_data();
    return a.exec();
}
