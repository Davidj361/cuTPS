#include "headers/MainWindow.h"
#include "ui_mainwindow.h"
#include "headers/ConnectionClient.h"
#include "../common/headers/Definitions.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->runTestsButton, SIGNAL(clicked()), this, SLOT(runTests()));
    connect(ui->btnRunTest1, SIGNAL(clicked()), this, SLOT(runTest1()));
    connect(ui->btnRunTest2, SIGNAL(clicked()), this, SLOT(runTest2()));
    connect(ui->btnRunTest3, SIGNAL(clicked()), this, SLOT(runTest3()));

    serverIP = new QString("192.168.28.100");
    portno = 60001;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::runTests() {
    qDebug() << "Running tests!";
    runTest1();
    runTest2();
    runTest3();

}

void MainWindow::runTest1(){
    qDebug() << "Running test 1";
    ConnectionClient *connection;
    connection = new ConnectionClient(serverIP, portno);
    QByteArray *req = new QByteArray("{command:'2',userType:'0', username:'Graeme'}");
    QByteArray *res;
    connection->request(req, res);
    qDebug()<<res;

}

void MainWindow::runTest2(){
    qDebug() << "Running test 2";
}

void MainWindow::runTest3(){
    qDebug() << "Running test 3";
}

