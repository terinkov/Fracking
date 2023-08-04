#ifndef GRAPHICS_PARAMETERS_WIDGET_H
#define GRAPHICS_PARAMETERS_WIDGET_H

#include <QPushButton>
#include <QWidget>
#include <QtWidgets>

class graphics_parameters_widget : public QWidget
{
    Q_OBJECT
public:
    explicit graphics_parameters_widget(QWidget *parent = nullptr);

    QPushButton* button_back;
    QPushButton* button_run;

    QLabel *water_level;
    QLabel *corrosive_substances_level;
    QLabel *propane_level;


    QLabel *crack_radius_label_score;
    QLabel *crack_width_label_score;
    QLabel *crack_volume_label_score;
    QLabel *crack_length_label_score;
    QLabel *crack_debit_label_score;

    int getLiquidSum();

    void setFluidLevel();

    QMap<QString,QString> result_params;

signals:

public slots:
    void slotChangedFluidLevel(QString, double);

private:
    int fluid_volume_water=1000;
    int fluid_volume_propane=300;
    int fluid_volume_corrosive=300;
};

#endif // GRAPHICS_PARAMETERS_WIDGET_H
