#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtPrintSupport/QPrinter>


enum Widgets{
    start_widget=0,
    scores_widget=1,
    fracking_settings_widget=2,
    graphics_widget=3,
};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stackedWidget = new QStackedWidget(this);


//    startWidget
    startWidget = new StartWidget(stackedWidget);
    QObject::connect(startWidget->btn_to_simulator_settings, SIGNAL(clicked()), this, SLOT(setSimulatorSettingsWidget()));
    QObject::connect(startWidget->btn_exit, SIGNAL(clicked()), this, SLOT(slotClose()));

    stackedWidget->addWidget(startWidget);

//  fracking_settings widget
    frackingSettingsWidget = new FrackingSettingsWidget(this);
    QObject::connect(frackingSettingsWidget->button_back, SIGNAL(clicked()), this, SLOT(setStartWidget()));
    QObject::connect(frackingSettingsWidget->button_next, SIGNAL(clicked()), this, SLOT(setGraphicsWidget()));
    stackedWidget->addWidget(frackingSettingsWidget);

//    main_widget:
    interface_graphics_handler = new Interface_graphics_handler(this);
    stackedWidget->addWidget(interface_graphics_handler);
    QObject::connect(interface_graphics_handler->parameters_widget->button_back, SIGNAL(clicked()), this, SLOT(backToStartWidget()));
    QObject::connect(interface_graphics_handler, SIGNAL(signalAskResultsOfGrp(int)), frackingSettingsWidget, SLOT(getResultsOfGrp(int)));
    QObject::connect(frackingSettingsWidget,SIGNAL(translateResultsOfGrp(double,double,double,double,double)),
                     interface_graphics_handler, SLOT(receiveResultsOfGrp(double,double,double,double,double)));
    QObject::connect(interface_graphics_handler, SIGNAL(signalDialogScreenshot()), this, SLOT(slotDialogScreenshot()));

//    out
    setCentralWidget(stackedWidget);

//  dialog declaration
    input_name_dialog = new QDialog(this);
    QVBoxLayout *dialog_layout = new QVBoxLayout();
    input_name_dialog_text_edit = new QLineEdit();

    QLabel* label_name = new QLabel(this);
    label_name->setText("Input user name: ");
    QPushButton* pcmdOk =new QPushButton("&Ok");
    QPushButton* pcmdCancel =new QPushButton("&Cancel");
    QObject::connect(pcmdOk, SIGNAL(clicked() ), this, SLOT(accept_if_valid_dialog_name()));
    connect(pcmdCancel, SIGNAL(clicked()), input_name_dialog, SLOT(reject()));

//    QVBoxLayout *main_dialog_layout = new QVBoxLayout;
    QHBoxLayout *buttons_layout = new QHBoxLayout;
    buttons_layout->addWidget(pcmdOk);
    buttons_layout->addWidget(pcmdCancel);
//    main_dialog_layout->addLayout(buttons_layout);
    dialog_layout->addWidget(label_name);
    dialog_layout->addWidget(input_name_dialog_text_edit);
    dialog_layout->addLayout(buttons_layout);

    input_name_dialog->setLayout(dialog_layout);
//  dialog validation
    QRegExp rx_name("\\w+");
    QValidator *validator_name = new QRegExpValidator(rx_name, this);

    input_name_dialog_text_edit->setValidator(validator_name);
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<event->key();
        switch(event->key()){
            case Qt::Key_I:
                qDebug()<<"increase";
                interface_graphics_handler->graphics_widget->increase_level();
                break;
            case Qt::Key_D:
                qDebug()<<"decrease";
                interface_graphics_handler->graphics_widget->decrease_level();

                break;
        }
}

void MainWindow::setScoresWidget()
{
    stackedWidget->setCurrentIndex(Widgets::scores_widget);
}

void MainWindow::setSimulatorSettingsWidget()
{
    if(input_name_dialog->exec()== QDialog::Accepted){
        this->user_name = input_name_dialog_text_edit->text();
        stackedWidget->setCurrentIndex(Widgets::fracking_settings_widget);
    }

}

void MainWindow::accept_if_valid_dialog_name(){
    if(input_name_dialog_text_edit->text()!=""){
        input_name_dialog->accept();
//        setSimulatorSettingsWidget();
    } else {
        QMessageBox msgBox;
        msgBox.setText("You input incorrect name.");
//        msgBox.setInformativeText("You input incorrect name." );
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
}

void MainWindow::slotClose()
{
    close();
}

void MainWindow::setStartWidget()
{
    stackedWidget->setCurrentIndex(Widgets::start_widget);
}

void MainWindow::setGraphicsWidget()
{
    if(frackingSettingsWidget->isValid()){
        frackingSettingsWidget->parameters->insertMode();
        frackingSettingsWidget->parameters->insertParameters();


//        interface_graphics_handler->parameters = frackingSettingsWidget->parameters;
        interface_graphics_handler->setMode(frackingSettingsWidget->parameters->Mode);
        interface_graphics_handler->translateModeToGraphics();
        interface_graphics_handler->calculateDefaultLiquidVolume();
//        interface_graphics_handler->graphics_widget->setMode(interface_graphics_handler->parameters->Mode);

        stackedWidget->setCurrentIndex(Widgets::graphics_widget);
    } else {
        QMessageBox msgBox;
        msgBox.setText("You input incorrect data. Fill all fields.");
//        msgBox.setInformativeText("You input incorrect name." );
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
    //    interface_graphics_handler->run();
}

void MainWindow::backToStartWidget()
{
    QDialog confirmDialog(this);
    confirmDialog.setModal(true);
    QVBoxLayout * dialog_layout = new QVBoxLayout;
    QLabel *label = new QLabel("Are you sure want to exit to menu?");
    dialog_layout->addWidget(label);

    QPushButton* pcmdOk =new QPushButton("&Ok");
    QPushButton* pcmdCancel =new QPushButton("&Cancel");
    QObject::connect(pcmdOk, SIGNAL(clicked() ), &confirmDialog, SLOT(accept() ));
    QObject::connect(pcmdCancel, SIGNAL(clicked()), &confirmDialog, SLOT(reject()));

    QHBoxLayout *buttons_layout = new QHBoxLayout;
    buttons_layout->addWidget(pcmdOk);
    buttons_layout->addWidget(pcmdCancel);
    dialog_layout->addLayout(buttons_layout);
    confirmDialog.setLayout(dialog_layout);


    if(confirmDialog.exec()== QDialog::Accepted){
        setStartWidget();
        frackingSettingsWidget->clear_fields();
        interface_graphics_handler->graphics_widget->activated_grp = false;
        interface_graphics_handler->parameters_widget->crack_radius_label_score->setText("");
        interface_graphics_handler->parameters_widget->crack_width_label_score->setText("");
        interface_graphics_handler->parameters_widget->crack_volume_label_score->setText("");
        interface_graphics_handler->parameters_widget->crack_length_label_score->setText("");
        interface_graphics_handler->parameters_widget->crack_debit_label_score->setText("");
//        frackingSettingsWidget->parameters = new Parameters();
        user_name = "";
    }
}

void MainWindow::slotDialogScreenshot()
{
    QDialog dialogSave(this);
    dialogSave.setModal(true);
    QVBoxLayout * dialog_layout = new QVBoxLayout;
    QLabel *label = new QLabel("Are you want to save results?");
    dialog_layout->addWidget(label);

    QPushButton* pcmdOk =new QPushButton("&Yes");
    QPushButton* pcmdCancel =new QPushButton("&No");
    QObject::connect(pcmdOk, SIGNAL(clicked() ), &dialogSave, SLOT(accept() ));
    QObject::connect(pcmdCancel, SIGNAL(clicked()), &dialogSave, SLOT(reject()));

    QHBoxLayout *buttons_layout = new QHBoxLayout;
    buttons_layout->addWidget(pcmdOk);
    buttons_layout->addWidget(pcmdCancel);
    dialog_layout->addLayout(buttons_layout);
    dialogSave.setLayout(dialog_layout);


    if(dialogSave.exec()== QDialog::Accepted){
        takeScreenshot();
        saveScreenshot();
        saveResultFile();
        backToStartWidget();
    }

}

void MainWindow::saveScreenshot()
{
    const QString format = "png";
    QString initialPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    if (initialPath.isEmpty())
    initialPath = QDir::currentPath();
    initialPath += tr("/untitled.") + format;

    QFileDialog fileDialog(this, tr("Save As"), initialPath);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setDirectory(initialPath);
    QStringList mimeTypes;
    const QList<QByteArray> baMimeTypes = QImageWriter::supportedMimeTypes();
    for (const QByteArray &bf : baMimeTypes)
    mimeTypes.append(QLatin1String(bf));
    fileDialog.setMimeTypeFilters(mimeTypes);
    fileDialog.selectMimeTypeFilter("image/" + format);
    fileDialog.setDefaultSuffix(format);
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    const QString fileName = fileDialog.selectedFiles().first();
    file_dir = fileName;
    if (!original_pixmap.save(fileName)) {
        QMessageBox::warning(this, tr("Save Error"), tr("The image could not be saved to \"%1\".")
            .arg(QDir::toNativeSeparators(fileName)));
    }
}

void MainWindow::takeScreenshot()
{
    original_pixmap = this->grab(this->rect());
}

void MainWindow::saveResultFile(){
    interface_graphics_handler->parameters_widget->result_params;
    QString str;
    str += "User parameters: \n";
    str += "User name: " + user_name+"\n";
    str += "Mode: "+QString(frackingSettingsWidget->parameters->getMode()==0?"Carbonate":"Terrigen")+"\n";
    str += "Well depth(м): " + QString::number(frackingSettingsWidget->parameters->L)+"\n";
    str += "Reservoir permeability (мкм^2): " + QString::number(frackingSettingsWidget->parameters->K)+"\n";
    str += "Viscosity of the rupture fluid (МПа/с): " + QString::number(frackingSettingsWidget->parameters->m)+"\n";
    str += "Radius of the well supply circuit (м): " + QString::number(frackingSettingsWidget->parameters->Rk)+"\n";
    str += "Pressure difference (bottom of the well and local mining) (МПа): " + QString::number(frackingSettingsWidget->parameters->delta_P)+"\n";
    str += "Uncovered layer thickness (м): " + QString::number(frackingSettingsWidget->parameters->H)+"\n";
    str += "Additional filtration resistance: " + QString::number(frackingSettingsWidget->parameters->C_dop)+"\n";

    str += "Result parameters:\n";
    str += "New well debit (м^3/сек): " + interface_graphics_handler->parameters_widget->result_params["debit"]+"\n";
    str += "Crack radius (м-12): " + interface_graphics_handler->parameters_widget->result_params["rad"]+"\n";
    str += "Crack width (м-3): " + interface_graphics_handler->parameters_widget->result_params["width"]+"\n";
    str += "Crack volume (м^3-18): " + interface_graphics_handler->parameters_widget->result_params["volume"]+"\n";
    str += "Crack length (м): " + interface_graphics_handler->parameters_widget->result_params["length"]+"\n";

    QString directory_to_save = file_dir.left(file_dir.length()-4)+".pdf";
    qDebug()<<directory_to_save;
    QTextDocument *tmp_document = new QTextDocument(str);
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName((directory_to_save));
    tmp_document->print(&printer);


}
