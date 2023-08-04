#ifndef SCORERECORD_H
#define SCORERECORD_H

#include "parameters.h"

#include <QObject>
#include <QWidget>

class ScoreRecord : public QWidget
{
    Q_OBJECT
public:
    explicit ScoreRecord(QWidget *parent = nullptr);

    QString name;
//    Parameters parameters;
    QString mode;

signals:

};

#endif // SCORERECORD_H
