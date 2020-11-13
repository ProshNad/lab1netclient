#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTcpSocket"
#include "QTcpServer"
#include "QMessageBox"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void readyReadServer();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

     QTcpSocket *socket;
     quint16     m_nNextBlockSize;
};

#endif // MAINWINDOW_H
