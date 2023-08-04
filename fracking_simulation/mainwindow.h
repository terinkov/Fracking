#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ScoresWidget.h"
#include "frackingsettingswidget.h"
#include "graphicswidget.h"
#include "interface_graphics_handler.h"
#include "parameters.h"
#include "startwidget.h"

#include <QMainWindow>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Main handler. includes classes of Results_handler and Session_handler
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStackedWidget *stackedWidget;
    StartWidget *startWidget;
    ScoresWidget *scoresWidget;
    Interface_graphics_handler *interface_graphics_handler ;
//    SessionHandler *sessionHandler;
    QDialog *input_name_dialog;
    QLineEdit *input_name_dialog_text_edit;

//    QWidget *fracking_settings_widget;
    FrackingSettingsWidget *frackingSettingsWidget;

    QPixmap original_pixmap;

    void saveScreenshot();
    void takeScreenshot();
    void saveResultFile();
protected:

    virtual void keyPressEvent(QKeyEvent *event);

public slots:
    void setScoresWidget();
    void setSimulatorSettingsWidget();
    void setStartWidget();
    void setGraphicsWidget();
    void backToStartWidget();

    void slotDialogScreenshot();

    void accept_if_valid_dialog_name();
    void slotClose();

//signals:
//    void signalWaveFluidIncrease();
//    void signalWaveFluidDecrease();
private:
    Ui::MainWindow *ui;
    QString user_name;
    QString file_dir;
//    Parameters *user_parameters;

};
#endif // MAINWINDOW_H
