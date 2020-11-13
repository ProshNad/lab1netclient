#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTcpSocket"
#include "QTcpServer"
#include "QMessageBox"
#include "QTime"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    if(socket->state() == QAbstractSocket::ConnectedState)
        {
        QByteArray  arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);

            out << quint16(0) << QTime::currentTime() <<ui->spinBox->value()<<ui->spinBox_2->value();

            out.device()->seek(0);
            out << quint16(arrBlock.size() - sizeof(quint16));
            socket->write(arrBlock); //write the data itself
            socket->waitForBytesWritten();
    }
}

void MainWindow::readyReadServer()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_2);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (socket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (socket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        QTime   time;
        QString str;
        in >> time >> str;

        qDebug()<<time.toString() + " " + str;
        ui->label_3->setText(str);
        m_nNextBlockSize = 0;
    }
}

void MainWindow::on_pushButton_clicked()
{
socket = new QTcpSocket(this);
socket->connectToHost("localhost", 1024);
socket->waitForConnected();
connect(socket, SIGNAL(readyRead()), SLOT(readyReadServer()));
connect(socket, SIGNAL(disconnected()), SLOT(deleteLater()));
qDebug()<<"connected";
m_nNextBlockSize = 0;

}
