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
#include <QBrush>
#include <QPen>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include "marker.h"


Marker::Marker(int n, QGraphicsItem * parent): QGraphicsPathItem(parent)
{
  setNumber(n);
  width = 16;
  halfwidth = 8;
  eyepos = 6;
  eyewidth = 5;
  
  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemIsMovable);

  setPen(QPen(QColor(40, 34, 125), 1, Qt::SolidLine,
	      Qt::FlatCap, Qt::MiterJoin));
  setBrush(QColor(220, 40, 20));

  QPainterPath p;
  p.addRect(eyepos, eyepos, eyewidth, eyewidth);
  
  p.moveTo(halfwidth, 0);
  p.lineTo(width, halfwidth);
  p.lineTo(halfwidth, width);
  p.lineTo(0, halfwidth);
  p.lineTo(halfwidth, 0);
 
  this->setPath(p);
}


void Marker::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
  qDebug() << "Pos  " << num << ", " << pos() << endl;
  model->setItem(num, 0, new QTableWidgetItem(QString::number(pos().x() + 5)));
  model->setItem(num, 1, new QTableWidgetItem(QString::number(pos().y() + 5)));
  model->setItem(num, 2, new QTableWidgetItem(QString::number(0.0)));
  model->setItem(num, 3, new QTableWidgetItem(QString::number(0.0)));
  update();
  QGraphicsItem::mouseReleaseEvent(event);
}


QRectF Marker::boundingRect() const
{
  return QRectF(0.0, 0.0, width, width);
}
