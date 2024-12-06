#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->run_plotter,SIGNAL(clicked()),this,SLOT(plot()));
    connect(ui->Function,SIGNAL(textEdited(QString)),this,SLOT(Set_parser()));
    connect(ui->Raiz,SIGNAL(clicked(bool)),this,SLOT(calc_root()));
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(save_file()));
  //  connect(ui->Raiz_otro,SIGNAL(clicked(bool)),this,SLOT(root_robol()));
}

MainWindow::~MainWindow()
{
    delete ui;


}

void MainWindow::plot(){
    Horizontal_axis_init();
    funcion.Set_Image();
    ui->area->display(funcion.calc_area());
    ui->plotter->addGraph();
    ui->plotter->setInteractions(QCP::iRangeZoom| QCP::iRangeDrag);
    ui->plotter->graph(0)->setData(funcion.x,funcion.y);
    ui->plotter->graph(0)->setPen(QPen(QColor(255,80,0,155)));
    ui->plotter->graph(0)->setBrush(QBrush(QColor(0,250,0,100)));
    ui->plotter->graph(0)->rescaleKeyAxis();
    ui->plotter->replot();
}
void MainWindow:: Set_parser(){
    parser.SetExpr(ui->Function->text().toStdWString());
    parser.DefineVar(L"x",funcion.x.data());
    funcion.pars(parser);

}
void MainWindow::Horizontal_axis_init(){
    ui->X_min->text().toDouble(&ok);
    ui->X_max->text().toDouble(&ok);
    ui->dx->text().toDouble(&ok);
    if(ok==true && ui->X_min->text().toDouble()<=ui->X_max->text().toDouble()){
        funcion.SetDomain(ui->X_min->text().toDouble(),ui->X_max->text().toDouble(),ui->dx->text().toDouble());qDebug("X axis initialized");}

    ok=true;

}
void MainWindow:: calc_root(){
    ui->Ent_raiz->text().toDouble(&ok);
    if(ok==true){
        qDebug("anda?");
        //la funcion de mi libreria devuelve el numero de interacciones con cout, puede crashear
        ui->raiz_unica->display(funcion.root_bisect_b(ui->Ent_raiz->text().toDouble()));
    }
    ok=true;
}
void MainWindow::root_robol(){ // muy tarde para experimentar
    root *list;
    list=funcion.root_robol();
    if(funcion.Nraicez()==1)
        ui->lcdNumber->display(list[0].value);
    if(funcion.Nraicez()==2)
        ui->lcdNumber_2->display(list[1].value);
    if(funcion.Nraicez()==3)
        ui->lcdNumber_3->display(list[2].value);
    if(funcion.Nraicez()==4)
        ui->lcdNumber_4->display(list[3].value);

}
void MainWindow:: save_file(){
    f=fopen("C:\\Users\\agust\\OneDrive\\Escritorio\\Examen 2 recuperatorio\\data.txt","w");
    for (int var = 0; var < funcion.x.length(); ++var) {
        fprintf(f,"x=%f y=%f \n",funcion.x[var],funcion.y[var]);
    }
    fclose(f);

}
