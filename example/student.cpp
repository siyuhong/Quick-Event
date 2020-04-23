#include "student.h"

Student::Student(QObject *parent) : QObject(parent)
{

}

Student::Student(const Student &other)
{
    this->name_ = other.name_;
    this->id_ = other.id_;
}

Student &Student::operator=(const Student &other)
{
    this->name_ = other.name_;
    this->id_ = other.id_;
    return *this;
}
