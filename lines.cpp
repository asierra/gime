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

#include <math.h>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include "lines.h"
#include "path.h"



bool Lines::show_arrows = false;
bool Lines::show_icons = false;


Lines::Lines(Path *p): path(p)
{
    setZValue(-1);
}


void Lines::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
  QPolygon polygon = path->toPolygon();
	
  QColor color1 = (Path::selected==path) ? Qt::red: path->color;
  QPen pen = QPen(color1, path->width);
  printf("Pen w %d\n", pen.width());
  painter->setPen(pen);
  painter->drawPolyline(polygon);

  if (show_arrows && polygon.size() > 1) {
    int i = polygon.size() - 1;
    QPoint p2 = polygon.point(i);
    QPoint p1 = polygon.point(i-1);

    float r = 8;
    float theta = atan2f(p1.y() - p2.y(), p1.x() - p2.x());
    float alpha = M_PI/2.0 - theta;
    float cs = cos(-alpha), sn = sin(-alpha);
    
    float x = r*0.5, y = r;
    QPointF ap1 = p2 + QPointF(-x*cs - sn*y, -x*sn + y*cs);
    QPointF ap2 = p2 + QPointF( x*cs - sn*y,  x*sn + y*cs);

    painter->drawLine(ap1, p2);
    painter->drawLine(ap2, p2);
  }

  if (show_icons && polygon.size() > 0)
    draw_icons(painter);
}


void Lines::draw_icons( QPainter *painter )
{
  int width = path->width;
  int r = (width + 1)/2;

  for (int i=0;  i < path->size(); i++) {
    QPoint p = path->point(i);
    QDateTime d = path->dateTimeAt(i);

    if (!d.isNull()) {
      int h = d.time().hour();
      if (h == 0) {	
	painter->setBrush(Qt::black);
	painter->setPen(Qt::white);
	painter->drawEllipse(p, r, r);
      } else if (h == 12) {	
	painter->setBrush(Qt::white);
	painter->setPen(Qt::black);
	painter->drawEllipse(p, r, r);
      }
    }
  }
}

QRectF Lines::boundingRect() const
{
    return path->boundingRect();
}
