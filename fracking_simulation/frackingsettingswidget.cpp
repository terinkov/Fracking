#include "frackingsettingswidget.h"



FrackingSettingsWidget::FrackingSettingsWidget(QWidget *parent)
    : QWidget{parent}
{

//    for
//    parameters
    parameters = new Parameters;
//    QVBoxLayout *layout = new QVBoxLayout();
//    QGridLayout *gridLayout = new QGridLayout(this);

    QVBoxLayout *all_layout = new QVBoxLayout(this);
    //input mode
//    QLabel * mode_label = new QLabel(this);
//    mode_label->setText("Choose mode");
//    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//    mode_label->setSizePolicy(sizePolicy);
    QGroupBox *groupMode = new QGroupBox("Choose mode");
    QVBoxLayout *mode_layout = new QVBoxLayout(this);
//    mode_layout->addWidget(mode_label);
    mode_layout->addWidget(parameters->radio_carbon);
    mode_layout->addWidget(parameters->radio_terrigen);
    groupMode->setLayout(mode_layout);
//    QVBoxLayout * tmp_layout_group_wrapper = new QVBoxLayout;
//    tmp_layout_group_wrapper.ad
    all_layout->addWidget(groupMode);
    groupMode_buttongroup = new QButtonGroup();
    groupMode_buttongroup->addButton(parameters->radio_carbon,0);
    groupMode_buttongroup->addButton(parameters->radio_terrigen,1);
    QObject::connect(groupMode_buttongroup,SIGNAL(idClicked(int)),this,SLOT(setParametersMode(int)));


    QGroupBox * groupParams = new QGroupBox("Input parameters",this);
    groupParams->setAlignment(Qt::AlignCenter);
    groupParams->setMinimumSize(this->width(),groupParams->height());
    //input parameters
    QGridLayout*insertedGridLayout = new QGridLayout(groupParams);
//    inser
//    insertedGridLayout->SetFixedSize(this->width(),450);
//    insertedGridLayout->SetMinimumSize()
    int i = 0;
    for(QMap<QString, QDoubleSpinBox*>::Iterator iter=parameters->mapped_parameters_line_edits.begin();
        iter!= parameters->mapped_parameters_line_edits.end();
        iter+=1){

        QLabel *tmp_label = new QLabel(this);
        tmp_label->setText(iter.key());
        insertedGridLayout->addWidget(tmp_label,i,0);
//        insertedGridLayout->addWidget()
        double *cur_value = parameters->mapped_parameters_default_values[iter.key()];
        iter.value()->setValue(*cur_value);
        insertedGridLayout->addWidget(iter.value(),i,1);
        i+=1;
    }
    groupParams->setLayout(insertedGridLayout);
//    gridLayout->addWidget(groupParams,0,1,2,1,Qt::AlignCenter);
//    grid
//    groupParams->setSizePolicy(sizePolicy);
    groupParams->setFixedSize(1900,400);
    groupParams->show();
    all_layout->addWidget(groupParams);



    button_back = new QPushButton("back",this);
    button_back->setFixedSize(100,50);
    button_next = new QPushButton("next",this);
    button_next->setFixedSize(100,50);
//    layout->addWidget(button_back);
//    layout->addWidget(button_next);
    QHBoxLayout *buttons_layout = new QHBoxLayout;
    buttons_layout->addWidget(button_back);
    buttons_layout->addWidget(button_next);
//    gridLayout->addLayout(buttons_layout);
    all_layout->addLayout(buttons_layout);
//  parameters

    setLayout(all_layout);
}

bool FrackingSettingsWidget::isValid()
{
    bool flag_valid = true;
    for(QMap<QString, QDoubleSpinBox*>::Iterator iter=parameters->mapped_parameters_line_edits.begin();
        iter!= parameters->mapped_parameters_line_edits.end();
        iter+=1){
        double cur = iter.value()->value();
        if(cur == 0)
            flag_valid = false;
    }
    qDebug()<<parameters->radio_carbon->isChecked();
    qDebug()<<parameters->radio_terrigen->isChecked();
    if(parameters->Mode==-1)
        flag_valid=false;
    return flag_valid;
}

void FrackingSettingsWidget::getResultsOfGrp(int liquidVolume)
{
    parameters->setLiquidVolume(liquidVolume);
    double  ChackLength =parameters->getChackLength();
    double  Qt=parameters->getNewDebit();
    double  Vt=parameters->getChackVolume();
    double  w=parameters->getChackWidth();
    double  rc=parameters->getChackRadius();
    emit translateResultsOfGrp(ChackLength,
                               Qt,
                               Vt,
                               w,
                               rc);
}

void FrackingSettingsWidget::clear_fields()
{
    parameters->Mode = -1;
    groupMode_buttongroup->setExclusive(false);
    if(groupMode_buttongroup->checkedButton() != nullptr)
        groupMode_buttongroup->checkedButton()->setChecked(false);
    groupMode_buttongroup->setExclusive(true);
}

void FrackingSettingsWidget::setParametersMode(int newMode){
    parameters->Mode = newMode;
}
