/*
 * This file is part of GIME, a System to track storms interactively
 * and to do basic meteorological image processing.
 *
 * GIME is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Copyright (c) 2002-2018  Alejandro Aguilar Sierra (asierra@unam.mx)
 * Centro de Ciencias de la Atmosfera, UNAM         
 */

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include <QDebug>

#include "node.h"


float Node::radius = 5.0;


Node::Node(Path *p): path(p)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}


void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
  if (!path->isNull()) {
    QColor color = (path!=Path::selected) ? Qt::black: Qt::red;
    painter->setPen(QPen(color, 2));
    painter->drawEllipse(-radius, -radius, 2*radius, 2*radius);
    //painter->drawRect(path->boundingRectAdjacent());
    //qDebug() << pos() << endl;
  }
}


QRectF Node::boundingRect() const
{
    qreal adjust = 10;
    QRectF b = path->boundingRectAdjacent();
    b.adjust(-adjust, -adjust, adjust, adjust);
 
    return b;
}


QPainterPath Node::shape() const
{
    QPainterPath p;
    p.addEllipse(-10, -10, 20, 20);
    return p;
}


void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{ 
  path->setPosition(pos());
  update();
  QGraphicsItem::mouseReleaseEvent(event);
}


void Node::updatePosition()
{
  setPos(path->point());
  update();
}
