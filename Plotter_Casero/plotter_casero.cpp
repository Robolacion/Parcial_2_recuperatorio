#include "plotter_casero.h"

/*! \brief calcula la imagen en un punto
 *  \var valor de x
 *
*/
double Plotter_Casero:: f(double X){
    parser.DefineVar(L"x",&X);
    double Y=parser.Eval();
    return Y;
}
/*! \brief valoriza "X" entre 2 valores parametros con un dx definido
 * \var xmin:cota inferior
 * \var xmax:cota superior
 * \var dx: diferencial de x
*/
void Plotter_Casero::SetDomain(double xmin,double xmax,double dx){

    if(dx!=0  &&  dx>0){
        double ctte;int i;
        N_samples=int(1.0/dx);
        N_elem=(xmax-xmin)*N_samples;
        x.resize(double(N_elem));
        y.resize(double(N_elem));
        ctte=xmin;
        x[0]=ctte;
        for (i=1;i<x.length();i++){
            x[i]=ctte+dx;
            ctte=ctte+dx;
        }
    }
    else{
        exit(0);
    }
}
void Plotter_Casero::Set_Image(){
    for (int i = 0; i <x.length(); ++i) {
        y[i]=f(x[i]);
    }
}
double Plotter_Casero:: calc_area(){
    double area_t=0,area_r=0,dx=0,Lim_inf=-100,Lim_sup=100;
    dx=(1.0/N_samples);
    Lim_inf=x.first();
    Lim_sup=x.last();
    if(dx>0){
        for (int i = 0; i < y.length()-1; ++i) {
            if(x[i]<=Lim_sup&&x[i]>=Lim_inf)
            {
                area_r=area_r+y[i]*dx;
                area_t=area_t+(y[i]+y[i+1])*dx/2.0;
                            }

        }
        area_t=(area_t*9+area_r*1)/10.0;
        std::cout<<area_t<<std::endl;
    }
    return area_t;
}

double Plotter_Casero:: calc_area(double xmin,double xmax){ //esta version admite un intervalo acotado por el usuario
    double area_t=0,area_r=0,dx=0,Lim_inf=-100,Lim_sup=100;
    dx=(1.0/N_samples);
    Lim_inf=x.first();
    Lim_sup=x.last();
    if(x.first()<xmin)
        Lim_inf=xmin;
    if(x.last()>xmax)
        Lim_sup=xmax;
    if(dx>0){
        for (int i = 0; i < y.length()-1; ++i) {
            if(x[i]<=Lim_sup&&x[i]>=Lim_inf)
            {
                area_r=area_r+y[i]*dx;
                area_t=area_t+(y[i]+y[i+1])*dx/2.0;
            }

        }
        area_t=(area_t*9+area_r*1)/10.0;
        std::cout<<area_t<<std::endl;
    }
    return area_t;
}
int Plotter_Casero:: busq(double value){ //esta funcion busca un valor de X en el vector
    int i=(N_elem/2)-1,aux=-100000;
        if (x[i]<value)
        {
            for (i=i; i < x.length(); i++) {
                if(x[i]==value){
                    aux= i;
                    break;}
            }
        }
        if(x[i]>value){
            for (i = 0; i<=(N_elem/2)-1 ; i++) {
                if(x[i]==value){
                    aux= i;
                    break;}
                if(x[i]<value && x[i+1]>value)
                    aux=i;
                break;
            }

        }
        return aux;
}
// aux=x[i]+(f(value)-f(i)/(f(i+1)-f(i)))*(x[i+1]-x[i])formula linealización
double Plotter_Casero:: df(double Xo){
    double dx=1.0/N_samples;
    dx=(f(Xo+dx)-f(Xo))/dx;
    return dx;
}

root* Plotter_Casero:: root_bisect(double Xo){ //Xo es el punto donde se desea buscar la raiz
    double x_min=Xo-1,x_max=Xo+1,x_cur,int_count=1;
    x_cur=(x_max+x_min)/2.0;
    if((f(x_min)*f(x_max))<0){
        N_raicez++;
        resize_raicez(N_raicez);
        while ((x_max-x_min)>0.00001 && int_count<1000){ //count es el valor maximo de intentos aceptable entre los valores de x

            if((f(x_min)*f(x_cur))<0)
                x_max=x_cur;
            if((f(x_max)*f(x_cur))<0)
                x_min=x_cur;
            x_cur=(x_max+x_min)/2.0;
            int_count++;
        }

        raicez->ok=true;}
    raicez->value=x_cur;

    //std::cout<<"raiz:"<<raicez->value<<""<<std::endl;
    return raicez;
}
double Plotter_Casero:: root_bisect_b(double Xo){ //Xo es el punto donde se desea buscar la raiz
    double x_min=Xo-1,x_max=Xo+1,x_cur=Xo,int_count=1;
    x_cur=(x_max+x_min)/2.0;
    if((f(x_min)*f(x_max))<0){
        while ((f(x_max)-f(x_min))>0.001 && int_count<1000){ //count es el valor maximo de intentos aceptable entre los valores de x

            if((f(x_min)*f(x_cur))<0)
                x_max=x_cur;
            if((f(x_max)*f(x_cur))<0)
                x_min=x_cur;
            x_cur=(x_max+x_min)/2.0;
            int_count++;

        }
    }

    std::cout<<"N° intentos:"<<int_count<<""<<std::endl;
    return x_cur;
}
root* Plotter_Casero:: root_robol(){ // si esto sigue vacio es porque no se me ocurrió un metodo efectivo para calcular las raicez de f
    int i=0;
    while (i<x.length()-1){
        if((f(x[i])*f(x[i+(N_elem/10)]))<0){
            N_raicez++;
            resize_raicez(N_raicez);
            raicez[N_raicez-1].value=root_bisect_b(x[i]);}
        raicez[N_raicez-1].ok=true;
        i+=(N_elem/20);

    }
return raicez;
}


