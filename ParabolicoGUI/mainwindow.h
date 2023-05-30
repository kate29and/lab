#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <movimiento.h>
#include <QTimer>
#include <fstream>
#include <QList>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void calcularDatos(Movimiento *cuerpo);

private slots:
    void on_bntSimular_clicked();
    void ActualizarPosicion();

private:
    Ui::MainWindow *ui;
    QList <Movimiento*> Planetas;
    QGraphicsScene *scene;
    QTimer *timer;
    QPainter *painter;
    int temporizador;
    bool mEnabled;
    int opcion;
};
#endif // MAINWINDOW_H
