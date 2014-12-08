#ifndef GUARD_CONTENTMANAGERPAGE_H
#define GUARD_CONTENTMANAGERPAGE_H

#include <QMessageBox>
#include <QWidget>
#include <QListWidget>

namespace Ui {
    class MainWindow;
}

class ContentManagerPage: public QWidget {
    public:
        void setUi(Ui::MainWindow* ui);
    private:
        Ui::MainWindow* ui;
};


#endif
