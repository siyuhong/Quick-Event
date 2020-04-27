#ifndef DIALOG_H
#define DIALOG_H

#include "event/quick.h"
#include "event/quickevent.h"
#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    QUICK_EVENT(QDialog)
public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
public slots:
    void event_show_time(const QDateTime &time);

    void on_pushButton_clicked();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Dialog *ui;

    QMessageBox *box;
};

#endif // DIALOG_H
