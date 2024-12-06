#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plotter_casero.h"
//#include "qcustomplot.h"
//#include "muParser.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    mu::Parser parser;
    Plotter_Casero funcion;
    bool ok;
    FILE *f;

public slots:
    void plot();
    void Set_parser();
    void Horizontal_axis_init();
    void calc_root();
    void save_file();
    void root_robol();
};
#endif // MAINWINDOW_H
