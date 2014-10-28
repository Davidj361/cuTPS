#include "headers/MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->runTestsButton, SIGNAL(clicked()), this, SLOT(RunTests()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::RunTests() {
    qDebug() << "Running tests!";
}
