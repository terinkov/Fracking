#include "graphics_parameters_widget.h"
#include <QtWidgets>

graphics_parameters_widget::graphics_parameters_widget(QWidget *parent)
    : QWidget{parent}
{
    water_level = new QLabel(this);
    corrosive_substances_level = new QLabel(this);
    propane_level = new QLabel(this);

    QGroupBox *groupBoxFluids = new QGroupBox(tr("Fluid percents: "));

    QGridLayout*insertedGridLayout = new QGridLayout();
    QLabel *tmp_label = new QLabel(this);
    tmp_label->setText("Water (л):");
    insertedGridLayout->addWidget(tmp_label,0,0);
    insertedGridLayout->addWidget(water_level,0,1);
    QLabel *tmp_label_2 = new QLabel(this);
    tmp_label_2->setText("Corrosive substances (л):"); //разъедающие
    insertedGridLayout->addWidget(tmp_label_2,1,0);
    insertedGridLayout->addWidget(propane_level,1,1);
    QLabel *tmp_label_3 = new QLabel(this);
    tmp_label_3->setText("Propane (sand) (л):"); //пропант
    insertedGridLayout->addWidget(tmp_label_3,2,0);
    insertedGridLayout->addWidget(corrosive_substances_level,2,1);
    groupBoxFluids->setLayout(insertedGridLayout);





    QGroupBox *groupBoxResults = new QGroupBox(tr("Results"));

    crack_radius_label_score = new QLabel(this);
    crack_width_label_score = new QLabel(this);
    crack_volume_label_score = new QLabel(this);
    crack_length_label_score = new QLabel(this);
    crack_debit_label_score = new QLabel(this);

    QGridLayout*insertedGridResults = new QGridLayout();
    QLabel * crack_radius_label= new QLabel(this);
    crack_radius_label->setText("Crack radius (м-12):");
    insertedGridResults->addWidget(crack_radius_label,0,0);
    insertedGridResults->addWidget(crack_radius_label_score,0,1);
    QLabel * crack_width_label = new QLabel(this);
    crack_width_label->setText("Crack width (м-3):"); //разъедающие
    insertedGridResults->addWidget(crack_width_label,1,0);
    insertedGridResults->addWidget(crack_width_label_score,1,1);
    QLabel * crack_volume_label = new QLabel(this);
    crack_volume_label->setText("Crack volume (м^3-18):"); //пропант
    insertedGridResults->addWidget(crack_volume_label,2,0);
    insertedGridResults->addWidget(crack_volume_label_score,2,1);
    QLabel * crack_length_label= new QLabel(this);
    crack_length_label->setText("Crack length (м):"); //пропант
    insertedGridResults->addWidget(crack_length_label,3,0);
    insertedGridResults->addWidget(crack_length_label_score,3,1);
    QLabel * crack_debit_label= new QLabel(this);
    crack_debit_label->setText("Well Debit (м^3/сек):"); //пропант
    insertedGridResults->addWidget(crack_debit_label,4,0);
    insertedGridResults->addWidget(crack_debit_label_score,4,1);
    groupBoxResults->setLayout(insertedGridResults);




    //crack_radius_label_score
//    crack_width_label_score
//    crack_volume_label_score
//    crack_length_label_score
//    crack_debit_label_score




//    QLabel *lbl_x = new QLabel;
//    lbl_x->setText(("Input X size of table"));
//    QLabel *lbl_y = new QLabel;
//    lbl_y->setText(("Input Y size of table"));
//    QGridLayout *grid_bounds = new QGridLayout;
//    grid_bounds->addWidget(lbl_x,0,0);
////    grid_bounds->addWidget(spin_box_x,0,1);
//    grid_bounds->addWidget(lbl_y,1,0);
////    grid_bounds->addWidget(spin_box_y,1,1);
//    groupBox_bounds->setLayout(grid_bounds);
////    containter->addWidget(groupBox);
////    containter->addWidget(spin_box_x);
////    QGridLayout* layout_main = new QGridLayout;
////    layout_main->addWidget(groupBox,0,0);
    QVBoxLayout *containter = new QVBoxLayout;
    containter->addWidget(groupBoxFluids);
    containter->addWidget(groupBoxResults);

    button_back =new QPushButton("&Back");
    button_run =new QPushButton("&Run");

    QHBoxLayout *buttons_layout = new QHBoxLayout;
    buttons_layout->addWidget(button_back);
    buttons_layout->addWidget(button_run);
    containter->addLayout(buttons_layout);
    setLayout(containter);
}

int graphics_parameters_widget::getLiquidSum(){return fluid_volume_water+
            fluid_volume_propane+
            fluid_volume_corrosive;}

void graphics_parameters_widget::setFluidLevel(){
    water_level->setText(QString::number(1.0*fluid_volume_water,'f',3));
    corrosive_substances_level->setText(QString::number(1.0*fluid_volume_propane,'f',3));
    propane_level->setText(QString::number(1.0*fluid_volume_corrosive,'f',3));
}

void graphics_parameters_widget::slotChangedFluidLevel(QString str, double level)
{
    if(str=="reservoir"){
        water_level->setText(QString::number(level*fluid_volume_water,'f',3));
    } else if(str == "truck_1"){

        corrosive_substances_level->setText(QString::number(level*fluid_volume_propane,'f',3));
    } else {

        propane_level->setText(QString::number(level*fluid_volume_corrosive,'f',3));
    }
}
