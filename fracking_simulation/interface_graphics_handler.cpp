#include "interface_graphics_handler.h"
#include <QtWidgets>

Interface_graphics_handler::Interface_graphics_handler(QWidget *parent)
    : QWidget{parent}
{

//    parameters = new Parameters();

    graphics_widget = new GraphicsWidget();
    parameters_widget = new graphics_parameters_widget();

    parameters_widget->water_level->setText(QString::number(1000,'f',3));
    parameters_widget->corrosive_substances_level->setText(QString::number(300,'f',3));
    parameters_widget->propane_level->setText(QString::number(300,'f',3));


    QSplitter *splitter = new QSplitter(parent);
    splitter->setChildrenCollapsible(true);

    splitter->addWidget(graphics_widget);
    splitter->addWidget(parameters_widget);


    QVBoxLayout *containter = new QVBoxLayout;
    containter->addWidget(splitter);
    setLayout(containter);

    QObject::connect(graphics_widget,SIGNAL(changedFluidLevel(QString, double)),parameters_widget, SLOT(slotChangedFluidLevel(QString, double)));
    QObject::connect(graphics_widget,SIGNAL(changedFluidLevel(QString, double)),this, SLOT(slotChangedFluidLevel(QString, double)));
//    activated_grp;
//    QObject::connect(parameters_widget->button_run,SIGNAL(clicked()),graphics_widget, SLOT(slotActivatedGRP()));

    QObject::connect(parameters_widget->button_run,SIGNAL(clicked()),this,SLOT(slotAskResultsOfGrp()));
    QObject::connect(parameters_widget->button_run,SIGNAL(clicked()),this,SLOT(askMainDialogScreenshot()));
}

void Interface_graphics_handler::calculateDefaultLiquidVolume()
{
    LiquidVolume = parameters_widget->getLiquidSum();
}

void Interface_graphics_handler::translateModeToGraphics()
{

    graphics_widget->run();
    graphics_widget->setMode(Mode);
    qDebug()<<"MODE"<<(Mode);
}

void Interface_graphics_handler::setMode(int newMode)
{
    Mode = newMode;
}

void Interface_graphics_handler::getResultsOfGrp()
{

    LiquidVolume = parameters_widget->water_level->text().toDouble()
            +
            parameters_widget->propane_level->text().toDouble()
            +
            parameters_widget->corrosive_substances_level->text().toDouble()
            ;
}

void Interface_graphics_handler::receiveResultsOfGrp(double ChackLength, double Qt, double Vt, double w, double rc)
{
    parameters_widget->result_params["rad"] =QString::number(rc);
    parameters_widget->result_params["width"] =QString::number(w);
    parameters_widget->result_params ["volume"] =QString::number(Vt) ;
    parameters_widget->result_params ["length"] =QString::number(ChackLength) ;
    parameters_widget->result_params["debit"] =QString::number(Qt);

    parameters_widget->crack_radius_label_score->setText(QString::number(rc));
    parameters_widget->crack_width_label_score->setText(QString::number(w));
    parameters_widget->crack_volume_label_score->setText(QString::number(Vt));
    parameters_widget->crack_length_label_score->setText(QString::number(ChackLength));
    parameters_widget->crack_debit_label_score->setText(QString::number(Qt));

    qDebug()<< "Default_Values" <<w<<ChackLength<<rc<<w*ChackLength*rc;

    graphics_widget->slotActivatedGRP((double)LiquidVolume/(double)average_volume);
}

void Interface_graphics_handler::slotAskResultsOfGrp()
{

    emit signalAskResultsOfGrp(LiquidVolume);
}

void Interface_graphics_handler::slotChangedFluidLevel(QString, double)
{
    this->LiquidVolume = parameters_widget->water_level->text().toDouble()
            +
            parameters_widget->propane_level->text().toDouble()
            +
            parameters_widget->corrosive_substances_level->text().toDouble()
            ;
    qDebug()<<LiquidVolume;
}

void Interface_graphics_handler::askMainDialogScreenshot()
{
    emit signalDialogScreenshot();
//    QDialog confirmDialog(this);
//    confirmDialog.setModal(true);
//    QVBoxLayout * dialog_layout = new QVBoxLayout;
//    QLabel *label = new QLabel("Are you sure want to exit");
//    dialog_layout->addWidget(label);

//    QPushButton* pcmdOk =new QPushButton("&Ok");
//    QPushButton* pcmdCancel =new QPushButton("&Cancel");
//    QObject::connect(pcmdOk, SIGNAL(clicked() ), &confirmDialog, SLOT(accept() ));
//    QObject::connect(pcmdCancel, SIGNAL(clicked()), &confirmDialog, SLOT(reject()));

//    QHBoxLayout *buttons_layout = new QHBoxLayout;
//    buttons_layout->addWidget(pcmdOk);
//    buttons_layout->addWidget(pcmdCancel);
//    dialog_layout->addLayout(buttons_layout);
//    confirmDialog.setLayout(dialog_layout);


//    if(confirmDialog.exec()== QDialog::Accepted){

//    }
}
