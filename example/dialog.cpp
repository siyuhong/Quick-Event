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
    //
    QuickApplication::subscibeEvent(this, "denglu_jieguo");
    QuickApplication::subscibeEvent(this, "show_time");
    box = new QMessageBox();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::event_denglu_jieguo(QSharedPointer<QVariant> ptr)
{
    box->close();

    auto status = ptr->value<int>();

    if(status)
        ui->show_label->setText("登录成功");
    else
        ui->show_label->setText("登录失败");
}

void Dialog::event_show_time(QSharedPointer<QVariant> ptr)
{
    qDebug() << ptr->value<QString>();
    box->setText(ptr->value<QString>());
    box->show();
}

void Dialog::on_pushButton_clicked()
{
    Student student;

    student.name_ = ui->name_lineEdit->text();
    student.id_ = ui->id_lineEdit->text();

    ui->show_label->setText("登录...");

    QuickApplication::postEvent(nullptr, student, "denglu");

}

void Dialog::on_pushButton_2_clicked()
{
      QuickApplication::exit();
}

void Dialog::on_pushButton_3_clicked()
{
    QuickApplication::postEvent(nullptr, QString("打扫卫生"), "dashao");
}
