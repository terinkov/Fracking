#include "parameters.h"

int Parameters::getMode() const
{
    return Mode;
}

Parameters::Parameters()
{

//    QLineEdit *edit_L;
//    QLineEdit *edit_D;
//    QLineEdit *edit_H;
//    QLineEdit *edit_K;
//    QLineEdit *edit_E;
//    QLineEdit *edit_n;
//    QLineEdit *edit_rp;
//    QLineEdit *edit_rn;
//    QLineEdit *edit_m;
//    QLineEdit *edit_C;
//    QLineEdit *edit_Q;
    edit_L= new QDoubleSpinBox;
    edit_K= new QDoubleSpinBox;
    edit_m= new QDoubleSpinBox;
    edit_t= new QDoubleSpinBox;
    edit_delta_P= new QDoubleSpinBox;
    edit_Rk= new QDoubleSpinBox;
    edit_H= new QDoubleSpinBox;
    edit_C_dop = new QDoubleSpinBox;

    mapped_parameters_line_edits["Well depth"] = edit_L;
    edit_L->setMinimum(300);
    edit_L->setMaximum(3000);
    edit_L->setSingleStep(100);
    mapped_parameters_line_edits["Reservoir permeability"]=edit_K;
    edit_K->setRange(0.01,1);
    edit_K->setSingleStep(0.01);
//    mapped_parameters["Poisson ratio"]=;
    mapped_parameters_line_edits["Viscosity of the rupture fluid"]=edit_m;
    edit_m->setRange(0.01,0.1);
    edit_m->setSingleStep(0.01);
    mapped_parameters_line_edits["Duration of liquid injection"]=edit_t;
    edit_t->setRange(5,20);
    edit_t->setSingleStep(1);
    mapped_parameters_line_edits["Pressure difference (bottom of the well and local mining)"]=edit_delta_P;
    edit_delta_P->setRange(2,4.2);
    edit_delta_P->setSingleStep(0.2);
    mapped_parameters_line_edits["Radius of the well supply circuit"]=edit_Rk;
    edit_Rk->setRange(100,600);
    edit_Rk->setSingleStep(100);
    mapped_parameters_line_edits["Uncovered layer thickness"] = edit_H;
    edit_H->setRange(8,20);
    edit_H->setSingleStep(1);
//    mapped_parameters_line_edits["Debit before fracking"] = edit_Q0;
    mapped_parameters_line_edits["Additional filtration resistance"] = edit_C_dop;
    edit_C_dop->setRange(0.1,10);
    edit_C_dop->setSingleStep(0.1);

    mapped_parameters_default_values["Well depth"] = &L;
    mapped_parameters_default_values["Reservoir permeability"]=&K;
//    mapped_parameters["Poisson ratio"]=;
    mapped_parameters_default_values["Viscosity of the rupture fluid"]=&m;
    mapped_parameters_default_values["Duration of liquid injection"]=&t;
    mapped_parameters_default_values["Pressure difference (bottom of the well and local mining)"]=&delta_P;
    mapped_parameters_default_values["Radius of the well supply circuit"]=&Rk;
    mapped_parameters_default_values["Uncovered layer thickness"] = &H;
//    mapped_parameters_default_values["Debit before fracking"] = &Q0;
    mapped_parameters_default_values["Additional filtration resistance"] = &C_dop;





    radio_carbon= new QRadioButton(("Carbonate rock"));
    radio_terrigen = new QRadioButton("Terrigen rock");

}

Parameters::~Parameters()
{
    mapped_parameters_default_values.clear();
    mapped_parameters_line_edits.clear();
}

double Parameters::getChackLength(){
    double ChackLength = sqrt(100*LiquidVolume*UngE/(5.6*(1-n)*(1-n)*H*delta_P));
    return ChackLength;
}

double Parameters::getChackRadius(){
    double C = 0.0269-3.21*L/1000000;
    double rc = C*sqrt(give_Q*sqrt(m*t/K));
    return rc;
}

double Parameters::getChackWidth(){
    double chack_length = getChackLength();
    double w = 8*(1-n)*(1-n)*delta_P*chack_length/UngE;
    return w;
}

double Parameters::getChackVolume(){
    double Vt = getChackWidth()*getChackRadius()*getChackRadius()*M_PI;
    return Vt;
}

double Parameters::getNewDebit(){
    double Qt = 2*M_PI*K*10*delta_P/(100000*m*qLn(Rk*1000/LiquidVolume*getChackRadius()));
    return Qt;
}

double Parameters::getGRPEffect(){
    double Ef = getNewDebit()/getDebitBeforeGRP();
    return Ef;
}

double Parameters::getDebitBeforeGRP(){
    return getNewDebit()*qLn(Rk/getChackRadius())/(C_dop+qLn(Rk*LiquidVolume/1000/getChackRadius()));
}

void Parameters::setLiquidVolume(double newLiquidVolume)
{
    LiquidVolume = newLiquidVolume;
}

void Parameters::insertMode()
{
    if(radio_carbon->isChecked()){
        Mode = 0;
        n = 0.3;
        UngE = 7;
    } else {
        Mode = 1;
        n = 0.13;
        UngE = 3.5;

    }
}

void Parameters::insertParameters()
{
//    for(QMap<QString, QDoubleSpinBox*>::Iterator iter = mapped_parameters_line_edits.begin();
//        iter!=mapped_parameters_line_edits.end();
//        iter++){
//        *mapped_parameters_default_values[(iter.key())] = iter.value()->value();
        mapped_parameters_default_values["Well depth"] = &L;
        mapped_parameters_default_values["Reservoir permeability"]=&K;
    //    mapped_parameters["Poisson ratio"]=;
        mapped_parameters_default_values["Viscosity of the rupture fluid"]=&m;
        mapped_parameters_default_values["Duration of liquid injection"]=&t;
        mapped_parameters_default_values["Pressure difference (bottom of the well and local mining)"]=&delta_P;
        mapped_parameters_default_values["Radius of the well supply circuit"]=&Rk;
        mapped_parameters_default_values["Uncovered layer thickness"] = &H;
    //    mapped_parameters_default_values["Debit before fracking"] = &Q0;
        mapped_parameters_default_values["Additional filtration resistance"] = &C_dop;


        L = edit_L->value();
        C_dop = edit_C_dop->value();
        H = edit_H->value();
        Rk = edit_Rk->value();
        delta_P = edit_delta_P->value();
        t = edit_t->value();
        m = edit_m->value();
        K = edit_K->value();
}

void Parameters::clear_fields()
{
//    btnGroup->setExclusive(false);
//    if(btnGroup->checkedButton() != nullptr)
//        btnGroup->checkedButton()->setChecked(false);
//    btnGroup->setExclusive(true);

//    radio_carbon->setChecked(false);
//    radio_terrigen->setChecked(false);

//    for(QMap<QString, QDoubleSpinBox*>::Iterator iter = mapped_parameters_line_edits.begin();
//        iter!=mapped_parameters_line_edits.end();
//        iter++){
////        *mapped_parameters_default_values[(iter.key())] = QString(iter.value()->text()).toDouble();
//    }
}
