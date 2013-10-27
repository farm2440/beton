#ifndef DIALOGPROGRESS_H
#define DIALOGPROGRESS_H

#include <QDialog>
#include <QProcess>
#include <QTime>
#include <QMessageBox>

namespace Ui {
    class DialogProgress;
}

class DialogProgress : public QDialog {
    Q_OBJECT
public:
    DialogProgress(QWidget *parent = 0);
    ~DialogProgress();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialogProgress *ui;
};

#endif // DIALOGPROGRESS_H
