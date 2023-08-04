#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>


class Wave{
private:
    QPainterPath *wave_frame;
    QPainter *painter;
public:
    QRect *max_characteristics;
    QRect *characteristics;
    double percent = 1.0;
    double amplitude;
    double w;
    double result_offset;
    double m_offset;
    double keyboard_velocity = 0.02;
    Wave(double amplitude, double w, double offset, QPainterPath& wave_frame, QPainter& painter,QRect &rect)
//        :wave_frame(wave_frame)
//        ,painter(painter)
//        ,characteristics(rect)
    {
        this->painter = &painter;
        this->wave_frame = &wave_frame;
        this->amplitude=amplitude;
        this->characteristics = &rect;
        this->w = w;
        this->m_offset = offset;
    }
    ~Wave(){
        delete max_characteristics;
        delete characteristics;
    }
    Wave(double amplitude, double w, double offset)
    {
        this->amplitude=amplitude;
        this->w = w;
        this->m_offset = offset;
    }
    void set_context(QPainterPath& wave_frame, QPainter& painter,QRect &rect){
        this->painter = &painter;
        this->wave_frame = &wave_frame;
        this->characteristics = &rect;
    }
    void set_max_characteristics(QRect rect){
        max_characteristics = new QRect(rect);
//                rect;
    }
    void decrease(){
        if(characteristics->height()>0 && characteristics->height()<max_characteristics->height())
            characteristics->setY(characteristics->y()+keyboard_velocity);
    }
    void increase(){
        if(characteristics->height()>0 && characteristics->height()<max_characteristics->height())
            characteristics->setY(characteristics->y()-keyboard_velocity);
    }
//    Wave();
    void draw_frame(){
        wave_frame->moveTo(characteristics->x(), characteristics->y()+characteristics->height());
        for (int i = 0; i <= characteristics->width(); i+=1) // x изменяется от значения 0 ~ w до синусоиды
        {
            double waveY = (double) (amplitude * sin (w * i + result_offset)) ; // waveY изменяется при изменении значения x, получая таким образом синусоидальную кривую
            wave_frame->lineTo (characteristics->x()+i, waveY+characteristics->y()); // Рисуем линию от последней точки рисования до (x, waveY);
        }
        wave_frame->lineTo (characteristics->width()+characteristics->x(), characteristics->y()+characteristics->height());
        painter->drawPath(*wave_frame);
        result_offset+=m_offset;
    }
    double get_calculated_percent(){
        percent = (double)(characteristics->height())/(double)(max_characteristics->height());
        return percent;
    }

};


class GraphicsWidget : public QWidget
{
    Q_OBJECT
private:

    double shake_timer = 0;
    bool runned = false;
    QColor sky_color;
    QMap<QString, QColor> color_scheme;
    QMap<QString, QPixmap> images;
    QMap<QString, QPoint> images_coords;
    QMap<QString, QRect> fluids_relative_coords;
    QMap<QString, QRect> fluids_relative_coords_const;
    QMap<QString, QRect> fluids_absolute_coords;
    QMap<QString, QRect> fluids_max_characteristics;
    QString images_path;

    QPoint tube_relative_coords = QPoint(85,400);
    QPoint cracks_relative_to_tube_coords = QPoint(283,444);
//    QPainterPath wave_drawer;
//    Wave *wave_fluid_reservoir;
//    Wave *wave_fluid_truck_1;
//    Wave *wave_fluid_truck_2;
    QMap<QString, Wave*> wave_fluid;
    int flag = 0;

    int ground_vertical = 0;
//    QRect wave_reservoir_rect;
//    QRect wave_fluid_rect_truck1;
//    QRect wave_fluid_rect_truck2;

    int vertical_images_coord = 0;
    double m_offset = 0;
    double wolna = M_PI / 1000; // w - угловая скорость, можно понимать как плотность волны, чем больше плотность
    double k = 200;
    double A = 20;

    void update_ground_vertical(double multiple = 0.40);

    double scale=1;
    double last_scale=1;
public:
    bool activated_grp = false;
    explicit GraphicsWidget(QWidget *parent = nullptr);
    void run();

    void paintEvent(QPaintEvent *);
    QTimer *timer;

    void setMode(int newMode);

public slots:
    void Slot_On_Timer();
    void slotActivatedGRP(double scale = 1);
    void increase_level();
    void decrease_level();
protected:
//    virtual void mousePressEvent (QMouseEvent* pe);
//    virtual void mouseReleaseEvent(QMouseEvent* pe);
    virtual void mouseMoveEvent (QMouseEvent* pe);
    virtual void resizeEvent(QResizeEvent *event);
//    virtual void keyPressEvent(QKeyEvent *event);
signals:
    void changedFluidLevel(QString, double);

private:
    int Mode = 0;

private:
    void shake_cam(double time);

};

#endif // GRAPHICSWIDGET_H
