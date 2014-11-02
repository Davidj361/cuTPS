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

  connect(connection, SIGNAL(ConnectionError(QString)), this, SLOT(displayError(QString)));
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
  ui->resultsListWidget->addItem(test2);
  ui->resultsListWidget->addItem(test3);

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
  }
  catch (exception &e) {
      qDebug() << e.what();
  }

  try {
      test2->setText("Performing add chapter test...");

      qDebug() << "=========================";
      serializer->Serialize(ADD_CHAPTER, c, REQUEST, req);
      qDebug() << req;
      connection->request(req, res);
      qDebug() << res;
      serializer->Deserialize(res, object, result, errorMsg);

      qDebug() << "Result: " << result;
      if (result == "success") {
          test2->setText( test2->text() + "PASSED" );
          test2->setForeground(QBrush(Qt::green));
      }
      else {
          test2->setText( test2->text() + "FAILED" );
          test2->setForeground(QBrush(Qt::red));
      }
  }
  catch (exception &e) {
      qDebug() << e.what();
  }

  try {
      test3->setText("Performing add section test...");

      qDebug() << "=========================";
      serializer->Serialize(ADD_SECTION, s, REQUEST, req);
      qDebug() << req;
      connection->request(req, res);
      qDebug() << res;
      serializer->Deserialize(res, object, result, errorMsg);

      qDebug() << "Result: " << result;
      if (result == "success") {
          test3->setText( test3->text() + "PASSED" );
          test3->setForeground(QBrush(Qt::green));
      }
      else {
          test3->setText( test3->text() + "FAILED" );
          test3->setForeground(QBrush(Qt::red));
      }
  }
  catch (exception &e) {
      qDebug() << e.what();
  }

  ui->btnRunTest1->setEnabled(true);
}

void MainWindow::runTest2() {
  qDebug() << "Running test 2 - Retrieve Content";

  ui->btnRunTest2->setEnabled(false);

  QListWidgetItem *test1 = new QListWidgetItem; // Retrieve content

  ui->resultsListWidget->addItem(test1);

  QString result;
  QString errorMsg;
  void *object = 0;

  User user("peter","", "", "");
  vector<Textbook*> book_list;

  try {
      test1->setText ("Performing Retrieve Content test...");
      serializer->Serialize(GET_CONTENT, &user, REQUEST, req);
      qDebug() << req;
      connection->request(req, res);
      qDebug() << res;
      serializer->Deserialize(res, object, result, errorMsg);
      book_list = *(static_cast<vector<Textbook*>*>(object));

      qDebug() << "Result: " << result;
      if (result == "success") {
          test1->setText( test1->text() + "PASSED" );
          test1->setForeground(QBrush(Qt::green));
      }
      else {
          test1->setText( test1->text() + "FAILED" );
          test1->setForeground(QBrush(Qt::red));
      }

  }
  catch (exception &e) {
      test1->setText( test1->text() + "FAILED - " + e.what() );
      test1->setForeground(QBrush(Qt::red));
      qDebug() << e.what();
  }

  ui->btnRunTest2->setEnabled(true);
}

void MainWindow::runTest3() {
  qDebug() << "Running test 3";
}

void MainWindow::displayError(QString error) {
    ui->statusBar->showMessage(error);
}
