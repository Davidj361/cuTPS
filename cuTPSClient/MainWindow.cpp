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

  connect(connection, SIGNAL(ConnectionError(QString)), this, SLOT(displayError()));
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

  test1->setForeground(QBrush(Qt::green));

  test2->setText("Testing something else...");
  test2->setForeground(QBrush(Qt::red));

  ui->resultsListWidget->addItem(test2);

  //    runTest1();
  //    runTest2();
  //    runTest3();
}

// Add Content test
void MainWindow::runTest1() {
  qDebug() << "Running test 1 - Adding Content";

  ui->btnRunTest1->setEnabled(false);

  QListWidgetItem *test1 = new QListWidgetItem; // Add textbook test
  QListWidgetItem *test2 = new QListWidgetItem; // Add chapter test
  QListWidgetItem *test3 = new QListWidgetItem; // Add section test

  ui->resultsListWidget->addItem(test1);

  QString result;
  QString errorMsg;
  void* object = 0;

  Textbook *t = new Textbook("1234567890", "Learning NodeJS", "David J", "Graeme J", 2014, "1", "Everything you need to know about NodeJS", true, 50);
  Chapter  *c = new Chapter("V8 Engine", 1, t, "More horsepower!", true, 15);
  Section  *s = new Section("Many ponies", 1, c, t, "Ponies are funny looking", true, 5);

  try {
      test1->setText("Performing add textbook test...");

      qDebug() << "=========================";
      serializer->Serialize(ADD_TEXTBOOK, t, REQUEST, req);
      qDebug() << req;
      connection->request(req, res);
      qDebug() << res;
      serializer->Deserialize(res, object, result, errorMsg);

      qDebug() << "Result: " << result;
      if (result == "success") {
          test1->setText( test1->text() + "PASSED" );
          test1->setForeground(QBrush(Qt::green));
      }
      else {
          test1->setText( test1->text() + "FAILED" );
          test1->setForeground(QBrush(Qt::red));
      }

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
  catch (exception &e) {
      qDebug() << e.what();
  }

  ui->btnRunTest1->setEnabled(true);
}

void MainWindow::runTest2() {
  qDebug() << "Running test 2";
  User user("peter","", "", "");
  QByteArray res;
  QByteArray req;

  serializer->Serialize(GET_CONTENT, &user, REQUEST, req);
  qDebug() << req;
  connection->request(req, res);
  qDebug() << res;
}

void MainWindow::runTest3() {
  qDebug() << "Running test 3";
}

void MainWindow::displayError(QString error) {
    ui->statusBar->showMessage(error);
}
