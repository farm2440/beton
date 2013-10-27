#ifndef DIALOGSELECTFILE_H
#define DIALOGSELECTFILE_H

#include <QDialog>
#include <QStringList>
#include <QTime>

#include "gpio.h"

namespace Ui {
    class DialogSelectFile;
}

class DialogSelectFile : public QDialog {
    Q_OBJECT
public:
    DialogSelectFile(QWidget *parent = 0, QStringList *fileList = NULL );
    ~DialogSelectFile();

    void setFileList(QStringList *fileList);
    QString getSelectedFileName();
protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialogSelectFile *ui;

    QStringList *list;
    QString selectedFileName;
private slots:
    void selectedFileChanged(int row);
    void onCancel();
    void onOK();
    void beep();
};

#endif // DIALOGSELECTFILE_H
