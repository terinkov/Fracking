#include "ScoresWidget.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

ScoresWidget::ScoresWidget(QWidget *parent)
    : QWidget{parent}
{
    QLabel *lbl = new QLabel;
    lbl->setText("Results");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lbl);
//    add scorerecords

//

    btn_back = new QPushButton;
    btn_back->setText("Back");
    layout->addWidget(btn_back);

    setLayout(layout);

}

