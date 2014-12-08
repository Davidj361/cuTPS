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


/////////////
// NOTES
/////////////
// Each QListWidgetItem in the QListWidgets should
// have a pointer the corresponding object they hold
// Either a Textbook*, Course*, Section*
// This will help avoid overhead with algorithms
// and prove to be useful for memory management/accessing


#endif
