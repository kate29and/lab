#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H
#include <math.h>
#include <QGraphicsItem>
#include <QPainter>
#include <QList>
#include <QMap>
#include <QPainter>

# define tiempo 1
class Movimiento : public QGraphicsItem
{
    // Atributos
    char nombre;
    double posx, posy;
    double angulo;
    double fgravedad;
    double fuerzax, fuerzay, fxtotal, fytotal;
    QMap <char, double> Distancias;
    double masa;
    double distancia;
    double velX, velY;
    double r;
    char color;

protected:


public:
    //Constructor
    Movimiento();
    Movimiento(char, double x, double y, double velx_, double vely, double masa, int r_, char color);

    //Métodos
    void calcularFuerzaGT();
    void fuerzaG(int masa2, double r);
    void CalcularPosicion();
    void calcularDatos(Movimiento*);
    void calcularDistancia(QList <Movimiento*>);
    void calcularAngulo(double posx_, double posy_);
    void calcularAceleracion(QList <Movimiento*> planetas);
    void fuerzaG(int masa2, double posX, double posY);
    void CalcularVelocidad();
    void aumentarTiempo();
    void calcularDatos();

    void setAceleracion(double newAceleracion);
    QRectF boundingRect() const;
        void paint(QPainter *painter,
             const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    //Getter y setter
    double getPosx() const;
    double getPosy() const;
    double getMasa() const;
    double getVelX() const;
    double getVelY() const;

    char getNombre() const;
};

class Trayectoria : private Movimiento
{
    QPainter *painter;

public:
    QRectF boundingRect() const;
        void paint(QPainter *painter,
             const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // MOVIMIENTO_H
