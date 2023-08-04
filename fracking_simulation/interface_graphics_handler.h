#ifndef INTERFACE_GRAPHICS_HANDLER_H
#define INTERFACE_GRAPHICS_HANDLER_H

#include "graphics_parameters_widget.h"
#include "graphicswidget.h"
#include "parameters.h"
#include <QObject>
#include <QWidget>

class Interface_graphics_handler : public QWidget
{
    Q_OBJECT
public:
    explicit Interface_graphics_handler(QWidget *parent = nullptr);
public:
    GraphicsWidget *graphics_widget;
    graphics_parameters_widget *parameters_widget;
//    Parameters *parameters;

    void setMode(int newMode);


    void calculateDefaultLiquidVolume();

    void translateModeToGraphics();

private:
    int Mode;
    int LiquidVolume;
    int average_volume = 1400;

signals:
    void signalCalculateGrp();
    void signalAskResultsOfGrp(int);
    void signalDialogScreenshot();

public slots:
    void getResultsOfGrp();
    void receiveResultsOfGrp(double,double,double,double,double);
    void slotAskResultsOfGrp();
    void slotChangedFluidLevel(QString, double);

    void askMainDialogScreenshot();

};

#endif // INTERFACE_GRAPHICS_HANDLER_H
