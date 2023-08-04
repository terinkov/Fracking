//#ifndef FLUID_H
//#define FLUID_H

//#include "qpainter.h"
//#include "qpainterpath.h"
//#include <QObject>
//#include <QWidget>
//#include <cmath>


//class Wave{
//private:
//    QPainterPath *wave_frame;
//    QPainter *painter;
//public:
//    QRect *characteristics;
//    double amplitude;
//    double w;
//    double result_offset;
//    double m_offset;
//    Wave(double amplitude, double w, double offset, QPainterPath& wave_frame, QPainter& painter,QRect &rect)
////        :wave_frame(wave_frame)
////        ,painter(painter)
////        ,characteristics(rect)
//    {
//        this->painter = &painter;
//        this->wave_frame = &wave_frame;
//        this->amplitude=amplitude;
//        this->characteristics = &rect;
//        this->w = w;
//        this->m_offset = offset;
//    }
//    Wave(double amplitude, double w, double offset)
//    {
//        this->amplitude=amplitude;
//        this->w = w;
//        this->m_offset = offset;
//    }
//    void set_context(QPainterPath& wave_frame, QPainter& painter,QRect &rect){
//        this->painter = &painter;
//        this->wave_frame = &wave_frame;
//        this->characteristics = &rect;
//    }
////    Wave();
//    void draw_frame(){
//        wave_frame->moveTo(characteristics->x(), characteristics->y()+characteristics->height());
//        for (int i = 0; i <= characteristics->width(); i+=1) // x изменяется от значения 0 ~ w до синусоиды
//        {
//            double waveY = (double) (amplitude * sin (w * i + result_offset)) ; // waveY изменяется при изменении значения x, получая таким образом синусоидальную кривую
//            wave_frame->lineTo (characteristics->x()+i, waveY+characteristics->y()); // Рисуем линию от последней точки рисования до (x, waveY);
//        }
//        wave_frame->lineTo (characteristics->width()+characteristics->x(), characteristics->y()+characteristics->height());
//        painter->drawPath(*wave_frame);
//        result_offset+=m_offset;
//    }
//};

//class Fluid : public QWidget
//{
//    Q_OBJECT
//public:
//    explicit Fluid(QWidget *parent = nullptr);
//    Wave wave;
//protected:
//    virtual void mousePressEvent (QMouseEvent* pe);
//    virtual void mouseReleaseEvent(QMouseEvent* pe);
//    virtual void mouseMoveEvent (QMouseEvent* pe);
//signals:

//};

//#endif // FLUID_H
