#include "headers/MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  serverIP = new QString("127.0.0.1");
  portno = 60001;

  connection = new ConnectionClient(serverIP, portno);
  serializer = new Serializer();

  connect(ui->actionQuit,     SIGNAL(triggered()), this, SLOT(close()));
  connect(ui->runTestsButton, SIGNAL(clicked()),   this, SLOT(runTests()));
  connect(ui->btnRunTest1,    SIGNAL(clicked()),   this, SLOT(runTest1()));
  connect(ui->btnRunTest2,    SIGNAL(clicked()),   this, SLOT(runTest2()));
  connect(ui->btnRunTest3,    SIGNAL(clicked()),   this, SLOT(runTest3()));
}

MainWindow::~MainWindow() {
  delete ui;
  delete connection;
  delete serverIP;
  delete serializer;
}

void MainWindow::runTests() {
  qDebug() << "Running all tests!";
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

// Add Content test
void MainWindow::runTest1() {
  qDebug() << "Running test 1 - Adding Content";

  Textbook *t = new Textbook("Learning NodeJS", true, 50, "David J", "1234567891", "Graeme J", "1", "Everything you need to know about NodeJS", 2014);
  Chapter  *c = new Chapter("V8 Engine", true, 15, 1, "More horsepower!", t);
  Section  *s = new Section("Many ponies", true, 5, 1, "Ponies are funny looking", t, c);

  QByteArray res;
  QByteArray req;

  qDebug() << "=========================";
  serializer->Serialize(ADD_TEXTBOOK, t, REQUEST, req);
  qDebug() << req;
  connection->request(req, res);
  qDebug() << res;

  qDebug() << "=========================";
  serializer->Serialize(ADD_CHAPTER, c, REQUEST, req);
  qDebug() << req;
  connection->request(req, res);
  qDebug() << res;

  qDebug() << "=========================";
  serializer->Serialize(ADD_SECTION, s, REQUEST, req);
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

