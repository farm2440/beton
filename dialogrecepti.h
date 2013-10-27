#ifndef DIALOGRECEPTI_H
#define DIALOGRECEPTI_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QTime>
#include <QTextCodec>

#include "dictionary.h"
#include "iniparser.h"
#include "gpio.h"

/* Диалогова форма за управление на рецептите */
namespace Ui {
    class DialogRecepti;
}

class DialogRecepti : public QDialog {
    Q_OBJECT
public:
    DialogRecepti(QWidget *parent = 0);
    ~DialogRecepti();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialogRecepti *ui;

    dictionary *dict; //ползва се от iniparser. в него се зарежда съдържанието на отворения ini файл
private slots:
    void onOpenFile();
    void onExit();
    void beep();
};

#endif // DIALOGRECEPTI_H
