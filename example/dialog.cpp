#include "dialog.h"
#include "ui_dialog.h"
#include "event/quickapplication.h"

#include "student.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QuickApplication::subscibeEvent(this, "show_time");
    box = new QMessageBox();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::event_show_time(const QDateTime &time)
{
    box->setText(time.toString());
    box->show();
}

void Dialog::on_pushButton_clicked()
{
    Student student;

    student.name_ = ui->name_lineEdit->text();
    student.id_ = ui->id_lineEdit->text();

    ui->show_label->setText("登录...");

    QuickApplication::publishEvent("denglu", Qt::AutoConnection, student);
}

void Dialog::on_pushButton_2_clicked()
{
      QuickApplication::exit();
}

void Dialog::on_pushButton_3_clicked()
{
    QuickApplication::publishEvent("dashao", Qt::AutoConnection, ui->name_lineEdit->text(), QString("打扫卫生"));
}

void Dialog::on_pushButton_4_clicked()
{
     QuickApplication::quit();
}
