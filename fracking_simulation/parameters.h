#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "qmath.h"
#include <QLineEdit>
#include <math.h>
#include <QtWidgets>


class Parameters
{
public:
    int Mode = -1;
    //Mode = 0 карбонатные (известянки, доломиты)
    //Mode = 1 терригенные (песчанники)
    QRadioButton * radio_carbon;
    QRadioButton * radio_terrigen;


    Parameters();
    ~Parameters();
    double L = 300;//глубина скважины   [300,3000]
    double D;
    double H = 13.5; //вскрытая толщина пласта
    double K = 0.1; //проницаемость пласта [10^-2;1] мкм^2
    double E;
    double n = 0.25; // коэфициент Пуассона
    double rp;
    double rn;
    double m = 0.02; //вязкость жидкости разрыва МПа/с [0,01;0,1] (или нижняя грань еще на порядок меньше)
    double C;
    double Q;

    //подача насосных агрегатов при грп л/мин  [800, 2400]:
    double give_Q = 800;
    //продолжительность закачки жидкости мин [6,20]:
    double t = 6;
    QDoubleSpinBox *edit_t;
    // превышение давления на забое скважины над локальным горным МПа
    double delta_P = 2.5;

    QDoubleSpinBox *edit_delta_P;
    // длина трещины м
    double CrackLength;

    // модуль Юнга домноженный на 10^4
    double UngE;
    // радиус контура питания скважины (параметр, заданный пользователем) расстояние между двумя скважинами
    double Rk=300;
    QDoubleSpinBox *edit_Rk;

    double LiquidVolume;


//    double Q0 = getDebitBeforeGRP();//дебит скважины до ГРП м3/сек
//    QLineEdit *edit_Q0;


    //дополнительное фильтрационное сопротивление, вызванное несовершенством скважины значение
    double C_dop = 1;
    QDoubleSpinBox *edit_C_dop;


    QDoubleSpinBox *edit_L;
    QLineEdit *edit_D;
    QDoubleSpinBox *edit_H; //вскрытая толщина пласта
    QDoubleSpinBox *edit_K;
    QLineEdit *edit_E;
    QLineEdit *edit_n;
    QLineEdit *edit_rp;
    QLineEdit *edit_rn;
    QDoubleSpinBox *edit_m;
    QLineEdit *edit_C;
    QLineEdit *edit_Q;
//    QMap<QString,QLineEdit*> parameters_line_edits;
    QMap <QString, double*> mapped_parameters_default_values;
    QMap <QString, QDoubleSpinBox*> mapped_parameters_line_edits;

    double getChackLength();
    double getChackRadius();
    double getChackWidth();
    double getChackVolume();
    double getNewDebit();
    double getGRPEffect();
    double getDebitBeforeGRP();


    void setLiquidVolume(double newLiquidVolume);
    void insertMode();
    void insertParameters();
    void clear_fields();
    int getMode() const;
};

#endif // PARAMETERS_H
