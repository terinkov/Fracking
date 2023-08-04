#include "graphicswidget.h"
#include "parameters.h"
#include <QtWidgets>

GraphicsWidget::GraphicsWidget(QWidget *parent)
    : QWidget{parent}
{
    QDir *dir = new QDir();
    qDebug() << dir->absolutePath();
    images_path = dir->absolutePath() + "/images/";

}

void GraphicsWidget::run()
{

    timer = new QTimer (this);

    srand(time(NULL));

    connect(timer, SIGNAL (timeout()), this, SLOT(Slot_On_Timer()));
    timer->start(10);

    color_scheme["sky_color"] = QColor(173,217,190);
    color_scheme["ground_surface"] = QColor(227,82,38);
    color_scheme["formation_1"] = QColor(249,199,162);
    color_scheme["water"] = QColor(171,224,240);
    color_scheme["formation_3"] = QColor(193,158,77);
    color_scheme["productive_formation"] = QColor(136,136,136);
    color_scheme["productive_formation_terrigen"] = QColor(194,178,128);
    color_scheme["productive_formation_carbonate"] = QColor(193,158,77);

    QDir *dir = new QDir();
    qDebug() << dir->absolutePath();

    images["truck_1"] = QPixmap();
    images["truck_1"].load(images_path+"car1.png");
    images["truck_2"] = QPixmap();
    images["truck_2"].load(images_path+"car2.png");
    images["derick"] = QPixmap();
    images["derick"].load(images_path+"derick.png");
    images["reservoir"] = QPixmap();
    images["reservoir"].load(images_path+"/reservoir.png");
    images["reservoirs_not_active"] = QPixmap();
    images["reservoirs_not_active"].load(images_path+"reservoirs_not_active.png");
    images["truck_1_base"] = QPixmap();
    images["truck_1_base"].load(images_path+"car1_base.png");
    images["truck_2_base"] = QPixmap();
    images["truck_2_base"].load(images_path+"car2_base2.png");
    images["well"] = QPixmap();
    images["well"].load(images_path+"well.png");

    //cracks
    for(int i = 1; i <= 10; i++){
        QString cur_way = QString(images_path+"cracks/crack_%1.png").arg(QString::number(i));
        images[QString("crack_%1").arg(QString::number(i))]= QPixmap();
        images[QString("crack_%1").arg(QString::number(i))].load(cur_way);
    }


    images_coords["truck_1"] =  QPoint(0,0);
    images_coords["truck_2"] =  QPoint(0,0);
    images_coords["derick"] = QPoint(0,0);
    images_coords["reservoir"] =  QPoint(0,0);
//    images_coords["well"] = QPoint(0,0);
//    images_coords["reservoirs_not_active"] =  QPoint(0,0);
//    images_coords["truck_1_base"] =  QPoint(0,0);
//    images_coords["truck_2_base"] =  QPoint(0,0);

    update_ground_vertical();

    int i = 0;
    for(QMap<QString, QPoint>::Iterator iter = images_coords.begin(); iter!= images_coords.end(); iter++){
        iter.value().setX(i*300);
        i+=1;
        iter.value().setY(ground_vertical-images[iter.key()].height());
    }

    images_coords["well"] = images_coords["derick"];
//    images_coords["reservoirs_not_active"] =  images_coords["reservoir"];
//    images_coords["truck_1_base"] =  images_coords["truck_1"];
//    images_coords["truck_2_base"] =  images_coords["truck_2"];

    fluids_relative_coords["reservoir"]=QRect(41,93,154,213);
    fluids_relative_coords["truck_1"]=QRect(26,10,190,61);
    fluids_relative_coords["truck_2"]=QRect(26,14,178,50);

    fluids_relative_coords_const["reservoir"]=QRect(41,93,154,213);
    fluids_relative_coords_const["truck_1"]=QRect(26,10,190,61);
    fluids_relative_coords_const["truck_2"]=QRect(26,14,178,50);

    wave_fluid["reservoir"] = new Wave(A/10,wolna*100,6.4);
    wave_fluid["truck_1"] = new Wave(A/10,wolna*100,6.4);
    wave_fluid["truck_2"] = new Wave(A/10,wolna*100,6.4);



    for(QMap<QString, Wave*>::Iterator iter = wave_fluid.begin(); iter !=wave_fluid.end(); iter++){
        iter.value()->set_max_characteristics(fluids_relative_coords[iter.key()]);
        iter.value()->max_characteristics->translate(images_coords[iter.key()]);
    }
//    wave_fluid["reservoir"]->set_max_characteristics(fluids_relative_coords["reservoir"]);
//    wave_fluid["reservoir"]->max_characteristics->translate(images_coords["reservoir"].x(),
//                                                            images_coords["reservoir"].y());
//    qDebug()<<"reservoir max_character"<<*wave_fluid["reservoir"]->max_characteristics;

    runned = true;
}



void GraphicsWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    update_ground_vertical();

    int vertical_offset = 0;
    painter.setBrush(color_scheme["sky_color"]);
    painter.drawRect(0,vertical_offset,width(),ground_vertical);
    vertical_offset+=ground_vertical;





    vertical_images_coord=vertical_offset;
    for(QMap<QString, QPoint>::Iterator iter = images_coords.begin(); iter!= images_coords.end(); iter++){
        QString cur_name = iter.key();
        if(iter.key()!="well")
            iter.value().setY(vertical_images_coord - images[cur_name].height());
    }
    painter.setBrush(color_scheme["ground_surface"]);
    painter.drawRect(0,vertical_offset,width(),12);
    vertical_offset+=12;
    painter.setBrush(color_scheme["formation_1"]);
    painter.drawRect(0,vertical_offset,width(),100);
    vertical_offset+=100;
    painter.setBrush(color_scheme["water"]);
    painter.drawRect(0,vertical_offset,width(),100);
    vertical_offset+=100;
    painter.setBrush(color_scheme["formation_3"] );
    painter.drawRect(0,vertical_offset,width(),100);
    vertical_offset+=100;


    painter.setBrush(color_scheme["productive_formation"]);


//    QPixmap shader_rock_pixmap = QPixmap();

    //se7t my shader
    if(Mode == 0){
        //carbonate:
//        painter.setBrush(*shader_rock_carbone);

        painter.setBrush(color_scheme["productive_formation_carbonate"]);
    } else{
        //terrigen:
//        painter.setBrush(*shader_rock_terrigen);
        painter.setBrush(color_scheme["productive_formation_terrigen"]);
    }
//    shader_rock->setTexture(shader_rock_pixmap);
////    painter.setBrush(Qt::TexturePattern);
//    painter.setBrush(shader_rock);

    painter.drawRect(0,vertical_offset,width(),height());
    vertical_offset = height();


    for(QMap<QString, QPoint>::Iterator iter = images_coords.begin(); iter!= images_coords.end(); iter++){
        QString cur_name = iter.key();
        painter.drawPixmap(iter.value(),images[cur_name]);
    }


    QPainterPath wave_drawer;
    painter.setBrush(QBrush(QColor(27,188,182,150),Qt::BrushStyle::SolidPattern));
    for(QMap<QString,QRect>::Iterator iter = fluids_relative_coords.begin();
        iter!=fluids_relative_coords.end(); iter++){
        QString tmp_name = iter.key();
        fluids_absolute_coords[tmp_name] = QRect();
        fluids_absolute_coords[tmp_name].setX(iter.value().x()+images_coords[tmp_name].x());
        fluids_absolute_coords[tmp_name].setY(iter.value().y()+images_coords[tmp_name].y());
        fluids_absolute_coords[tmp_name].setWidth(iter.value().width());
        fluids_absolute_coords[tmp_name].setHeight(iter.value().height());
//        if(flag<4)
//            qDebug()<<tmp_name<<fluids_absolute_coords[tmp_name];
        flag +=1;
    }

    for(QMap<QString, Wave*>::Iterator iter = wave_fluid.begin(); iter !=wave_fluid.end(); iter++){
        if(iter.key() == "reservoir"){
        } else if (iter.key() == "truck_1"){
            painter.setBrush(QColor(173,111,95,160));
        } else {
//            painter.setBrush(QColor(173,111,95,160));

            painter.setBrush(QBrush(QColor(20,210,40,150),Qt::BrushStyle::SolidPattern));
        }

        iter.value()->set_context(wave_drawer,painter,fluids_absolute_coords[iter.key()]);
        iter.value()->draw_frame();
        wave_drawer.clear();
    }

//    wave_fluid["reservoir"]->set_context(wave_drawer,painter,fluids_absolute_coords["reservoir"]);
//    wave_fluid["reservoir"]->draw_frame();
//    wave_drawer.clear();
////    fluids_absolute_coords["truck_1"] = QRect(1000,500,200,200);
//    wave_fluid["truck_1"]->set_context(wave_drawer,painter,fluids_absolute_coords["truck_1"]);
//    wave_fluid["truck_1"]->draw_frame();
//    wave_drawer.clear();
//    wave_fluid["truck_2"]->set_context(wave_drawer,painter,fluids_absolute_coords["truck_2"]);
//    wave_fluid["truck_2"]->draw_frame();


    painter.drawPixmap(images_coords["reservoir"],images["reservoirs_not_active"]);
    painter.drawPixmap(images_coords["truck_1"],images["truck_1_base"]);
    painter.drawPixmap(images_coords["truck_2"],images["truck_2_base"]);


//  draw tube
//    painter.translate(images["derick"].rect().x()++tube_relative_coords.x(),images["derick"].rect().y()+tube_relative_coords.y());
//    painter.setBrush(Qt::black);
//    painter.drawRect(0,0,20,250);
//    painter.setBrush(Qt::green);
//    painter.drawRect(0,0,10,400);
//    painter.translate(10,400);
//    painter.drawRect(0,0,600, 10);
    images_coords["well"] = QPoint(images_coords["derick"].x()+tube_relative_coords.x(),images_coords["derick"].y()+tube_relative_coords.y());
//    qDebug()<<images_coords["well"]<<images_coords["derick"];
    painter.drawPixmap(images_coords["well"],images["well"]);



//    painter.scale()

//    painter.scale(scale,scale);


    if(activated_grp==true){

        //cracks drawing
        for(int i = 1; i <= 5; i++){
            QString cur_name = QString("crack_%1").arg(QString::number(i));
            painter.drawPixmap(images_coords["well"].x()+cracks_relative_to_tube_coords.x()
                    - images[cur_name].width()+ i*70,
                                images_coords["well"].y()+
                    - images[cur_name].height()+ cracks_relative_to_tube_coords.y(),
                    images[cur_name]);
        }

        for(int i = 6; i <= 10; i++){
            QString cur_name = QString("crack_%1").arg(QString::number(i));
            painter.drawPixmap(images_coords["well"].x()+cracks_relative_to_tube_coords.x()
                    + (i-6)*70,
                                images_coords["well"].y()+
                    10+ cracks_relative_to_tube_coords.y(),
                    images[cur_name]);
        }
    }

//    painter.drawRec


//    painter.end();
//    painter.begin(this);


//    painter.drawPixmap(images_coords["reservoir"],images["derick"]);

//    painter.setPen(QPen(Qt::black, 1));
//    painter.drawPie (QRect (10, 10, 440, 280), 90 * 16, 270 * 16);
//    QBrush brush(Qt::white);
//    painter.setBrush(brush);
//    int size = 300;
//    draw_Kantor_set(4, 300, this->width()/2-size/2, this->height()/2-size/2, painter);

}

void GraphicsWidget::Slot_On_Timer()
{
//    x_rotate+=1;
//    у_new+=1.0;
//    qDebug()<< shake_timer;
    if(shake_timer<=0){
        shake_timer = 0;
        update_ground_vertical();
        timer->setInterval(10);
        update();
    } else {
        timer->setInterval(2);
        shake_timer -= .02;
        double current_multiplier = rand()%10 + 0.35;
        update_ground_vertical();
//        qDebug()<<"Ground vertical"<<current_multiplier;
        update();
    }
}

void GraphicsWidget::slotActivatedGRP(double scale)
{
    qDebug()<<"SLOT ACTIVATED GRP";
    activated_grp = true;
    this->scale = scale;
    for(int i = 1; i <= 10; i++){
        QString cur_way = QString(images_path+"/cracks/crack_%1.png").arg(QString::number(i));
        images[QString("crack_%1").arg(QString::number(i))]= QPixmap();
        images[QString("crack_%1").arg(QString::number(i))].load(cur_way);
    }
    for(int i = 1; i <= 10; i++){
        QString cur_name = QString("crack_%1").arg(QString::number(i));
//        qDebug()<<images[cur_name].size();
        double size_before_w = (double)images[cur_name].width();
        double size_after_w = (double)images[cur_name].width()*scale;
        double size_before_h = (double)images[cur_name].height();
        double size_after_h = (double)images[cur_name].height()*scale;
        images[cur_name]=images[cur_name].scaled(size_after_w,size_after_h,Qt::IgnoreAspectRatio);
//        qDebug()<<images[cur_name].size();
    }
}

void GraphicsWidget::increase_level()
{
    if(wave_fluid["reservoir"]->max_characteristics->y()>fluids_relative_coords["reservoir"].y()+images_coords["reservoir"].y()-20) {
//    if(<images_coords["reservoir"].y()*2){
        fluids_relative_coords["reservoir"].setY(wave_fluid["reservoir"]->max_characteristics->y()-images_coords["reservoir"].y());
    } else {
        fluids_relative_coords["reservoir"].setY(fluids_relative_coords["reservoir"].y()-20);
    }
//    qDebug() << "reserv inc" << fluids_relative_coords["reservoir"].y();
    *wave_fluid["reservoir"]->characteristics = fluids_relative_coords["reservoir"];
    emit changedFluidLevel("reservoir",wave_fluid["reservoir"]->get_calculated_percent());
}

void GraphicsWidget::decrease_level()
{
    if(wave_fluid["reservoir"]->max_characteristics->y()+wave_fluid["reservoir"]->max_characteristics->height()<
            fluids_relative_coords["reservoir"].y()+images_coords["reservoir"].y()+20){
        fluids_relative_coords["reservoir"].setY(wave_fluid["reservoir"]->max_characteristics->y()+wave_fluid["reservoir"]->max_characteristics->height()
                -images_coords["reservoir"].y());
    } else {
        fluids_relative_coords["reservoir"].setY(fluids_relative_coords["reservoir"].y()+20);
    }
//    fluids_relative_coords["reservoir"].setHeight(fluids_relative_coords["reservoir"].height()-wave_fluid["reservoir"]->keyboard_velocity);

//    qDebug()<<"reserv dec"<<fluids_relative_coords["reservoir"].y();
    *wave_fluid["reservoir"]->characteristics = fluids_relative_coords["reservoir"];
    emit changedFluidLevel("reservoir",wave_fluid["reservoir"]->get_calculated_percent());

}

void GraphicsWidget::mouseMoveEvent(QMouseEvent *pe)
{
    if(wave_fluid["reservoir"]->max_characteristics->contains(pe->pos())){
        fluids_relative_coords["reservoir"].setY(pe->y()-images_coords["reservoir"].y());
        emit changedFluidLevel("reservoir",wave_fluid["reservoir"]->get_calculated_percent());
    } else if(wave_fluid["truck_1"]->max_characteristics->contains(pe->pos())){
        fluids_relative_coords["truck_1"].setY(pe->y()-images_coords["truck_1"].y());
        emit changedFluidLevel("truck_1",wave_fluid["truck_1"]->get_calculated_percent());
    } else if(wave_fluid["truck_2"]->max_characteristics->contains(pe->pos())){
        fluids_relative_coords["truck_2"].setY(pe->y()-images_coords["truck_2"].y());
        emit changedFluidLevel("truck_2",wave_fluid["truck_2"]->get_calculated_percent());
    }
}

void GraphicsWidget::resizeEvent(QResizeEvent *event)
{
    if(!runned)
        run();
    update_ground_vertical();
    for(QMap<QString, QPoint>::Iterator iter = images_coords.begin(); iter!= images_coords.end(); iter++){
        iter.value().setY(ground_vertical-images[iter.key()].height());
    }
//    wave_fluid["reservoir"]->set_max_characteristics(fluids_relative_coords["reservoir"]);
//    wave_fluid["reservoir"]->max_characteristics->translate(images_coords["reservoir"].x(),
//                                                            images_coords["reservoir"].y());
    for(QMap<QString, Wave*>::Iterator iter = wave_fluid.begin(); iter !=wave_fluid.end(); iter++){
        iter.value()->set_max_characteristics(fluids_relative_coords_const[iter.key()]);
        iter.value()->max_characteristics->translate(images_coords[iter.key()]);
    }
}

//void GraphicsWidget::keyPressEvent(QKeyEvent *event)
//{
//    qDebug()<<event->key();
//    switch(event->key()){
//        case Qt::Key_I:
//            qDebug()<<"increase";
//            wave_fluid["reservoir"]->increase();
//            break;
//        case Qt::Key_D:
//            qDebug()<<"decrease";
//            wave_fluid["reservoir"]->decrease();

//            break;
//    }
//}

void GraphicsWidget::setMode(int newMode)
{
    Mode = newMode;
}

void GraphicsWidget::update_ground_vertical(double multiple){
    this->ground_vertical = height()*multiple;
}

void GraphicsWidget::shake_cam(double time)
{
    shake_timer = time;
}

//void Wave::draw_frame(){
//    wave_frame->moveTo(characteristics->x(), characteristics->y()+characteristics->height());
//    for (int i = 0; i <= characteristics->width(); i+=1) // x изменяется от значения 0 ~ w до синусоиды
//    {
//        double waveY = (double) (amplitude * sin (w * i + result_offset)) ; // waveY изменяется при изменении значения x, получая таким образом синусоидальную кривую
//        wave_frame->lineTo (characteristics->x()+i, waveY+characteristics->y()); // Рисуем линию от последней точки рисования до (x, waveY);
//    }
//    wave_frame->lineTo (characteristics->width()+characteristics->x(), characteristics->y()+characteristics->height());
//    painter->drawPath(*wave_frame);
//    result_offset+=m_offset;
//}
