#ifndef PLOTTER_CASERO_H
#define PLOTTER_CASERO_H
#pragma once
#include"muParser.h"
#include"qcustomplot.h"
#include<QDebug>
struct root{
    bool ok=false;
    double value;
};

class Plotter_Casero
{
private:
    mu::Parser parser;
    int N_elem,N_samples,N_raicez=0;
    double area;
    root *raicez;

public:
    QVector <double> x,y;
    Plotter_Casero(){  SetDomain(-3.,+3,0.25);}
    ~Plotter_Casero(){delete []raicez;}
    void pars(mu::Parser pars){parser=pars;} //ruego por que muparser tenga definido correctamente el operador "="
    double f(double x);
    int Nraicez(){return N_raicez;}
    void SetDomain(double xmin,double xmax,double dx);
    void Set_Image();
    double calc_area();
    double calc_area(double xmin,double xmax);
    root* root_bisect(double Xo);
    double root_bisect_b(double Xo);
    double df(double Xo);
    root* root_robol();
    int busq(double value);
    void resize_raicez(int value){root *aux; aux=new root[value]; for (int k = 0; k < N_raicez; ++k) {
    aux[k].value=raicez[k].value; aux[k].ok=raicez[k].ok;} delete[]raicez; raicez=aux; }
};


#endif // PLOTTER_CASERO_H
