#include "movimiento.h"


QRectF Movimiento::boundingRect() const
{
    return QRectF(0, 0, 2 * r, 2 * r);
}

void Movimiento::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    srand(time(0));
    QColor(rand()%255, rand()%255, rand()%255);
    if(color == 'A')
        painter->setBrush(Qt::yellow);
    else
        painter->setBrush(QColor(rand() % 255, rand() % 255, rand() % 255));

    painter->drawEllipse(boundingRect());
}
double Movimiento::getPosx() const
{
    return posx;
}

double Movimiento::getPosy() const
{
    return posy;
}

double Movimiento::getMasa() const
{
    return masa;
}

double Movimiento::getVelX() const
{
    return velX;
}

double Movimiento::getVelY() const
{
    return velY;
}



char Movimiento::getNombre() const
{
    return nombre;
}

Movimiento::Movimiento()
{

}

Movimiento::Movimiento(char nombre_, double x,  double y, double velX_, double velY_,
                       double masa_, int r_, char color_)
{
    nombre = nombre_;

    // Posiciones que cambian
    posx = x;
    posy = y;

    //color de la particula
    color = color_;

    // Velocidades en X y Y
    velX = velX_;
    velY = velY_;

    masa = masa_;

    r = r_;

    setPos(posx, -posy);
}

void Movimiento::calcularDistancia(QList <Movimiento*> planetas)
{
    Distancias.clear();

    for(auto itL = planetas.begin(); itL != planetas.end(); itL++)
    {
        if((*itL)->getNombre() != nombre)
        {
            distancia = sqrt(pow((*itL)->getPosx() - posx, 2)
                             + pow((*itL)->getPosy() - posy, 2));

            Distancias.insert((*itL)->getNombre(), distancia);
        }
    }
}

void Movimiento::CalcularPosicion()
{
    posx += velX;
    posy += velY;

    setPos(posx / 14, -posy / 22.7);
}

void Movimiento::calcularDatos(Movimiento *)
{
    CalcularVelocidad();
    CalcularPosicion();
}

void Movimiento::calcularAngulo(double posx_, double posy_)
{
    double auxX = 0, auxY = 0;

    auxX = posx_ - posx;
    auxY = posy_ - posy;

    if(posx - posx_ == 0)
        auxX = 0.0000000001;

    angulo = atan2((auxY), (auxX));
}

void Movimiento::calcularAceleracion(QList <Movimiento*> planetas)
{
    fxtotal = 0;
    fytotal = 0;

    for(auto itL = planetas.begin(); itL != planetas.end(); itL++)
    {
        if((*itL)->getNombre() != nombre)
        {
            calcularAngulo((*itL)->getPosx(), (*itL)->getPosy());

            distancia = Distancias[(*itL)->getNombre()];

            fuerzaG((*itL)->getMasa(), distancia);
        }
    }
}

void Movimiento::fuerzaG(int masa2, double r)
{
    fgravedad = masa2 / (r * r);
    fuerzax = fgravedad * cos(angulo); // fuerzax = acelX
    fuerzay = fgravedad * sin(angulo);

    calcularFuerzaGT();
}

void Movimiento::calcularFuerzaGT()
{
    fxtotal += fuerzax; // aceLXT = fxtotal
    fytotal += fuerzay;
}

void Movimiento::CalcularVelocidad()
{
    velX += fxtotal * tiempo; // vel = vel0 + acel * t; acel = f / m
    velY += fytotal * tiempo;
}

void Movimiento::calcularDatos()
{
    CalcularVelocidad();
    CalcularPosicion();
}

QRectF Trayectoria::boundingRect() const
{
    return Movimiento::boundingRect();
}

void Trayectoria::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void) option;
    (void) widget;

    QPoint p1, p2;

    //p1.setX(posx);
    //p2.setY(posy);

    painter->setBrush(Qt::white);
    painter->drawLine(p1, p2);
}
