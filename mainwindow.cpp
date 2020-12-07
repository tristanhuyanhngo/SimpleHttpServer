#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    m_server = new QTcpServer();
    if(m_server->listen(QHostAddress::Any, 8080)) {
        connect(this,SIGNAL(newMessage(QString)),this,SLOT(displayMessage(QString)));
        connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));
        this->ui->statusBar->showMessage("Server is listening...");
        connect(this->ui->lineEdit_message, SIGNAL(returnPressed()), this, SLOT(on_pushButton_sendMessage_clicked()));
    }
    else {
        QMessageBox::critical(this,"QTCPServer",QString("Unable to start the server: %1.").arg(m_server->errorString()));
        exit(EXIT_FAILURE);
    }
}

MainWindow::~MainWindow() {
    foreach (QTcpSocket* socket, connection_list) {
        socket->close();
        socket->deleteLater();
    }
    m_server->close();
    m_server->deleteLater();
    delete ui;
}

void MainWindow::newConnection() {
    while (m_server->hasPendingConnections()) {
        QTcpSocket* socket = m_server->nextPendingConnection();
        appendToSocketList(socket);

        QString tmp = QString("Client has joined the chatroom with IP %1 as %2").arg(socket->peerAddress().toString()).arg(socket->socketDescriptor());
        /* displayMessage(QString("INFO::Client with sockd:%1 has just entered the room").arg(socket->socketDescriptor())); */
        displayMessage(tmp);
        foreach (QTcpSocket* soc ,connection_list) {
            if (soc != socket)
                sendMessage(socket, tmp);
        }
        tmp = QString("You has joined the chatroom with %1 as %2").arg(socket->peerAddress().toString()).arg(socket->socketDescriptor());
        sendMessage(socket, tmp);
    }
}

void MainWindow::appendToSocketList(QTcpSocket* socket) {
    connection_list.append(socket);
    connect(socket, SIGNAL(readyRead()), this , SLOT(readSocket()));
    connect(socket, SIGNAL(disconnected()), this , SLOT(discardSocket()));
    this->ui->comboBox_receiver->addItem(QString::number(socket->socketDescriptor()));
    /* displayMessage(QString("INFO::Client with sockd:%1 has just entered the room").arg(socket->socketDescriptor())); */
    /* displayMessage(QString("Client has joined the chatroom with IP %1 as %2").arg(socket->peerAddress().toString(), socket->socketDescriptor())); */
}

void MainWindow::readSocket() {
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    QByteArray block = socket->readAll();
    QDataStream in(&block, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_12);

    while (!in.atEnd()) {
        QString receiveString;
        in >> receiveString;
        receiveString.prepend(QString("%1 :: ").arg(socket->socketDescriptor()));
        emit newMessage(receiveString);
        foreach (QTcpSocket* socket,connection_list) {
            sendMessage(socket, receiveString);
        }

    }
}

void MainWindow::discardSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    for (int i=0;i<connection_list.size();i++) {
        if (connection_list.at(i) == socket)
        {
            connection_list.removeAt(i);
            break;
        }
    }

    socket->deleteLater();
}

void MainWindow::on_pushButton_sendMessage_clicked() {
    QString receiver = this->ui->comboBox_receiver->currentText();
    QString str = this->ui->lineEdit_message->text();
    str = str.trimmed(); 
    this->ui->lineEdit_message->clear();
    QString com;
    for (int i = 0; str[i] != ' ' && i < str.size(); ++i) {
        com += str[i];
    }
    QString tmp;
    if (com == "s") {
        str = str.right(str.size() - 1);
        tmp = QString("Sent %1 to ").arg(str);
        str = str.prepend("s Server: ");
        if(receiver=="Broadcast") {
            foreach (QTcpSocket* socket,connection_list) {
                sendMessage(socket, str);
            }
            tmp.append(" all connected hosts.");
        }
        else {
            foreach (QTcpSocket* socket,connection_list) {
                if(socket->socketDescriptor() == receiver.toLongLong()) {
                    sendMessage(socket, str);
                    tmp.append(QString(" %1 ").arg(socket->socketDescriptor()));
                    break;
                }
            }

        }

        displayMessage(tmp);
    } else {
        displayMessage("Command not found\n");

    }
    this->ui->lineEdit_message->clear();
}

void MainWindow::sendMessage(QTcpSocket* socket, QString& message) {
    if(socket) {
        if(socket->isOpen()) {
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_12);
            out << message;
            socket->write(block);
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");
}

void MainWindow::sendMessage(QTcpSocket* socket) {
    if(socket) {
        if(socket->isOpen()) {
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_12);
            socket->write(block);
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Socket does not exist");
}

void MainWindow::displayMessage(const QString& str) {
    this->ui->textBrowser_receivedMessages->append(str);
}
