#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QObject>
#include <QPushButton>
#include <QWidget>

class StartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StartWidget(QWidget *parent = nullptr);
    QPushButton *btn_scores;
    QPushButton *btn_to_simulator_settings;
    QPushButton *btn_exit;

signals:

};

#endif // STARTWIDGET_H
