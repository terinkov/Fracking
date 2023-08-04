#include "startwidget.h"
#include "qdebug.h"

#include <QVBoxLayout>

StartWidget::StartWidget(QWidget *parent)
    : QWidget{parent}
{
    resize(1920,1080);

    btn_to_simulator_settings = new QPushButton("&To simulator", this);
    btn_to_simulator_settings->setFixedSize(100, 50);
    btn_to_simulator_settings->show();
    btn_to_simulator_settings->move(this->width()/2-50, this->height()/2-105);
    btn_exit = new QPushButton("&Exit", this);
    btn_exit->show();
    btn_exit->setFixedSize(100, 50);
    btn_exit->move(this->width()/2-50, this->height()/2-45);
}
