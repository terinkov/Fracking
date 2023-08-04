#ifndef SCORESWIDGET_H
#define SCORESWIDGET_H

#include <QObject>
#include <QPushButton>
#include <QWidget>

class ScoresWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScoresWidget(QWidget *parent = nullptr);
    QPushButton *btn_back;
signals:

};

#endif // SCORESWIDGET_H
