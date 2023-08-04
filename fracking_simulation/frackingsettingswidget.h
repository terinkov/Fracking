#ifndef FRACKINGSETTINGSWIDGET_H
#define FRACKINGSETTINGSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "parameters.h"

class FrackingSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FrackingSettingsWidget(QWidget *parent = nullptr);
    QPushButton *button_back;
    QPushButton *button_next;
    Parameters *parameters;
   QButtonGroup * groupMode_buttongroup;
//    void
    bool isValid();
signals:
    void translateResultsOfGrp(double,double,double,double,double);
public slots:
    void getResultsOfGrp(int);
    void clear_fields();
    void setParametersMode(int newMode);
};

#endif // FRACKINGSETTINGSWIDGET_H
