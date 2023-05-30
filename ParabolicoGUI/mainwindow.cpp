#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "movimiento.h"

#include <iostream>

using namespace std;

int times = 0;
ofstream fout;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    cin >> opcion;
    ui->setupUi(this);
    scene=new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(-635, -315, 1270, 630); // (posx, posy, ancho, alto)
    scene->setBackgroundBrush(Qt::black);
    timer = new QTimer();

    //Planetas = new QList<Movimiento*>();
    connect(timer, SIGNAL(timeout()), this,SLOT(ActualizarPosicion()));
    temporizador = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bntSimular_clicked()
{
    opcion = ui->putOpcion->text().toDouble();

    //Limpiar escenario
    if((Planetas.size() != 0) && (opcion == 0))
    {
        for(auto itL = Planetas.begin(); itL != Planetas.end(); itL++)
            scene->removeItem(*itL);

        Planetas.clear();
    }

     //Inicializar planetas
    if(opcion  == 1)
    {
        // (x, y, velx, vely, masa, radio, color)
         Planetas.push_back(new Movimiento('A', 0, 0, 0, 0, 50000, 18, 'A'));
         scene->addItem(Planetas.back());
         Planetas.push_back(new Movimiento('B', -5000, 0, 0, -2, 70, 10, 'M'));
         scene->addItem(Planetas.back());
         Planetas.push_back(new Movimiento('C', 5000, 0, 0, 2, 70, 10, 'B'));
         scene->addItem(Planetas.back());
         Planetas.push_back(new Movimiento('D', 0, -5000, 2, 0, 70, 10, 'R'));
         scene->addItem(Planetas.back());
         Planetas.push_back(new Movimiento('E', 0, 5000, -2, 0, 70, 10, 'G'));
         scene->addItem(Planetas.back());
         timer->start(1);
    }

    else if(opcion == 2)
    {
        // (x, y, velx, vely, masa, radio, color)
        Planetas.push_back(new Movimiento('A', 0, -7000, 2, 0, 70, 11, 'M'));
        scene->addItem(Planetas.back());
        Planetas.push_back(new Movimiento('B', 0, 0, 0, 0, 70000, 18, 'A'));
        scene->addItem(Planetas.back());
        Planetas.push_back(new Movimiento('C', 4000, 5000, -1.6, 1.2, 25, 11, 'B'));
        scene->addItem(Planetas.back());
        timer->start(1);
    }

}

void MainWindow::ActualizarPosicion()
{    

    if(times == 0)
    {
        fout.open("calculos.txt");
        times++;
    }

    for(auto itL = Planetas.begin(); itL != Planetas.end(); itL++)
        (*itL)->calcularDistancia(Planetas);

    for(auto itL = Planetas.begin(); itL != Planetas.end(); itL++)
    {
        //painEvent();//Dibujar trayectoria

        (*itL)->calcularAceleracion(Planetas);
        (*itL)->calcularDatos();
    }

    for(auto itL = Planetas.begin(); itL != Planetas.end(); itL++)
    {
        cout << (*itL)->getPosx() << "\t" << (*itL)->getPosy() << "\t";
        fout << (*itL)->getPosx() << "\t" << (*itL)->getPosy() << "\t";
    }

    cout << endl;
    fout << endl;

    if(temporizador >= 200000)
    {
      timer->stop();
      fout.close();
      cout<<"Archivo generado" <<endl;
    }

    temporizador++;
}

