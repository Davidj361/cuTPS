#include "headers/MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  serverIP = new QString("127.0.0.1");
  portno = 60001;

  connection = new ConnectionClient(serverIP, portno);
  serializer = new Serializer();

  user = new User("peter","", "", "");
  book_list = new vector<Textbook*>();

  connect(ui->actionQuit,     SIGNAL(triggered()), this, SLOT(close()));

  connect(ui->runTestsButton, SIGNAL(clicked()),   this, SLOT(runTests()));
  connect(ui->btnRunTest1,    SIGNAL(clicked()),   this, SLOT(runTest1()));
  connect(ui->btnRunTest2,    SIGNAL(clicked()),   this, SLOT(runTest2()));
  connect(ui->btnRunTest3,    SIGNAL(clicked()),   this, SLOT(runTest3()));

  ui->btnRunTest3->setEnabled(false);


  // For autscrolling to the bottom of the list
  connect(ui->resultsListWidget->verticalScrollBar(), SIGNAL(rangeChanged(int,int)), this, SLOT(scrollDown()));

  connect(connection, SIGNAL(ConnectionError(QString)), this, SLOT(displayError(QString)));
}

MainWindow::~MainWindow() {
    for (int i = 0; i < ui->resultsListWidget->count(); i++)
        delete ui->resultsListWidget->item(i);
  delete ui;
  delete connection;
  delete serverIP;
  delete serializer;
  delete user;
  delete book_list;
}

void MainWindow::scrollDown() {
  ui->resultsListWidget->scrollToBottom();
}

void MainWindow::runTests() {
  qDebug() << "Running all tests!";
  ui->resultsListWidget->clear();

  //    runTest1();
  //    runTest2();
  //    runTest3();
}

void * MainWindow::runTest(QListWidgetItem *listItem, commands_t in_command, void *in_object, QString message) {

    QString result;
    QString errorMsg;
    void *object = 0;

    res.clear();
    req.clear();

    try {
        listItem->setText(message);
        qDebug() << "Serializing Request...";
        serializer->Serialize(in_command, in_object, REQUEST, req);
        qDebug() << "Serialized request is:";
        qDebug() << req;
        qDebug() << "Sending request to server...";
        connection->request(req, res);
        qDebug() << "Response from server size is:";
        qDebug() << res.size();
        qDebug() << "Deserializing request...";
        serializer->Deserialize(res, object, result, errorMsg);
        listItem->setText(message + " " + result);
        if (result == "error")
            listItem->setText(listItem->text() + " " + errorMsg);
        listItem->setForeground( (result == "success") ? QBrush(Qt::green) : QBrush(Qt::red) );
    }
    catch (exception &e) {
        qDebug() << "Exception!";
        qDebug() << e.what();
        listItem->setText(message + "\n  Exception! " + e.what());
        listItem->setForeground(QBrush(Qt::red));
    }
    return object;
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

  Textbook t("1234567890", "Learning NodeJS", "David J", "Graeme J", 2014, "1", "Everything you need to know about NodeJS", true, 50);
  Chapter  c("V8 Engine", 1, &t, "More horsepower!", true, 15);
  Section  s("Many ponies", 1, &c, &t, "Ponies are funny looking", true, 5);

  runTest(test1, ADD_TEXTBOOK, &t, "Performing add textbook test...");
  runTest(test2, ADD_CHAPTER, &c, "Performing add chapter test...");
  runTest(test3, ADD_SECTION, &s, "Performing add section test...");

  ui->btnRunTest1->setEnabled(true);
}

void MainWindow::runTest2() {

  qDebug() << "Running test 2 - Retrieve Content";

  ui->btnRunTest2->setEnabled(false);

  QListWidgetItem *test1 = new QListWidgetItem; // Retrieve content

  ui->resultsListWidget->addItem(test1);

  book_list = static_cast<vector<Textbook*>*>(runTest(test1, GET_CONTENT, user, "Performing Retrieve Content test..."));

  if (book_list != 0) {
      qDebug() << "Book list size: " << book_list->size();
      ui->btnRunTest3->setEnabled(true);
  }

  ui->btnRunTest2->setEnabled(true);
}

void MainWindow::runTest3() {
  qDebug() << "Running test 3 - Adding Invoice";

  ui->btnRunTest3->setEnabled(false);

  QListWidgetItem *test1 = new QListWidgetItem; // Retrieve content

  ui->resultsListWidget->addItem(test1);

  Invoice invoice (user->getUserName());

  Textbook *t = book_list->front();

  invoice.addContent(t);

  runTest(test1, ADD_INVOICE, &invoice, "Performing Add Invoice test...");

  ui->btnRunTest3->setEnabled(true);
}

void MainWindow::displayError(QString error) {
    ui->statusBar->showMessage(error);
}
