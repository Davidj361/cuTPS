#include "headers/MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  serverIP = new QString("127.0.0.1");
  portno = 60001;
  connection = new ConnectionClient(serverIP, portno);

  connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
  connect(ui->runTestsButton, SIGNAL(clicked()), this, SLOT(runTests()));
  connect(ui->btnRunTest1, SIGNAL(clicked()), this, SLOT(runTest1()));
  connect(ui->btnRunTest2, SIGNAL(clicked()), this, SLOT(runTest2()));
  connect(ui->btnRunTest3, SIGNAL(clicked()), this, SLOT(runTest3()));

  s = new Serializer();

}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::runTests() {
  qDebug() << "Running tests!";
  ui->resultsListWidget->clear();

  QListWidgetItem *test1 = new QListWidgetItem;
  QListWidgetItem *test2 = new QListWidgetItem;

  test1->setText("Testing something...");
  test1->setForeground(QBrush(Qt::green));

  test2->setText("Testing something else...");
  test2->setForeground(QBrush(Qt::red));

  ui->resultsListWidget->addItem(test1);
  ui->resultsListWidget->addItem(test2);

  //    runTest1();
  //    runTest2();
  //    runTest3();
}

void MainWindow::runTest1() {
  qDebug() << "Running test 1";
  Textbook *t = new Textbook("Playboy", true, 50, "David J", "1234567890", "Graeme J", "1", "Boobs", 2014 );
  QByteArray res;
  QByteArray req;
  s->Serialize(ADD_TEXTBOOK, t, REQUEST, req);
  qDebug() << req;
  connection->request(req, res);
  qDebug() << res;
}

void MainWindow::runTest2() {
  qDebug() << "Running test 2";
}

void MainWindow::runTest3() {
  qDebug() << "Running test 3";
}

