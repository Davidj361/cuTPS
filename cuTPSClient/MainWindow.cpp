#include "headers/MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->runTestsButton, SIGNAL(clicked()), this, SLOT(RunTests()));
    connect(ui->btnRunTest1, SIGNAL(clicked()), this, SLOT(RunTest1()));
    connect(ui->btnRunTest2, SIGNAL(clicked()), this, SLOT(RunTest2()));
    connect(ui->btnRunTest3, SIGNAL(clicked()), this, SLOT(RunTest3()));

    serverIP = new QString("127.0.0.1");
    portno = 60001;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::RunTests() {
    qDebug() << "Running tests!";
    RunTest1();
    RunTest2();
    RunTest3();
}

void MainWindow::RunTest1(){
    qDebug() << "Running test 1";
    //ConnectionClient connection = new ConnectionClient();

}

void MainWindow::RunTest2(){
    qDebug() << "Running test 2";
}

void MainWindow::RunTest3(){
    qDebug() << "Running test 3";
}

