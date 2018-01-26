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
#include <qdebug.h>
#include "path.h"


int Path::image_idx = 0;
Path* Path::selected = NULL;
QColor Path::defaultColor=Qt::darkBlue;
TableModel *Path::model = NULL;
const char* GIME_NAME_VERSION="GIME 2.4.2";


Path::Path(int size): QPolygon(size)
{
  pen = QPen(defaultColor, 2 /* width */, Qt::SolidLine);
  visible = true;
  show_arrow = false;
  show_icon = false;
}


Path::Path(const QPolygon & polygon): QPolygon(polygon)
{
}

QRectF Path::boundingRectAdjacent() const
{
  QPointF point_tl, point_br;

  QPointF p = point();
  point_tl = point_br = p;
  
  if (image_idx > 0) {
    QPoint point_prev = QPolygon::point(image_idx - 1);

    if (point_prev.x() < point_tl.x())
      point_tl.setX(point_prev.x());
    
    if (point_prev.y() < point_tl.y())
      point_tl.setY(point_prev.y());
    
    if (point_prev.x() > point_br.x())
      point_br.setX(point_prev.x());
    
    if (point_prev.y() > point_br.y())
      point_br.setY(point_prev.y());
  }
  
  if (image_idx < size()-1) {
    QPoint point_next = QPolygon::point(image_idx + 1);

    if (point_next.x() < point_tl.x())
      point_tl.setX(point_next.x());
    
    if (point_next.y() < point_tl.y())
      point_tl.setY(point_next.y());
    
    if (point_next.x() > point_br.x())
      point_br.setX(point_next.x());
    
    if (point_next.y() > point_br.y())
      point_br.setY(point_next.y());
  }
  point_tl -= p;
  point_br -= p;

  return QRectF(point_tl, point_br);
}


void Path::setPosition(QPointF p)
{
  setPoint(image_idx, p.toPoint());
}


void Path::deletePosition()
{
  setPoint(image_idx, QPoint());
}


QDataStream& operator<<(QDataStream& stream, const PathPointer &path)
{
  QString name = path->getName();

  stream << name;
  stream << *(dynamic_cast<QPolygon*>(path));	
  stream << path->pen;
  stream << path->show_arrow;
  stream << path->show_icon;
	
  return stream;
}


QDataStream& operator>>(QDataStream& stream, PathPointer &path)
{
  QString name;
  QPolygon p;
	
  stream >> name;
  stream >> p;	
  path = new Path(p);
  
  stream >> path->pen;
  stream >> path->show_arrow;
  stream >> path->show_icon;

  path->setName(name);
	
  return stream;
}


QString Path::toEPS()
{
	QString out;
	
	QPolygon polygon = toPolygon();
	
	for (int i=0; i < polygon.size(); i++) {
		QPoint p = polygon.point(i);
		if (i==0)
			out += QString("%1 %2 moveto\n").arg(p.x()).arg(p.y());
		else
			out += QString("%1 %2 lineto\n").arg(p.x()).arg(p.y());
	}
	
	return out;
}


QPolygon Path::toPolygon()
{
  QPolygon polygon;

  for (int i = 0; i < size(); ++i) 
    if (!QPolygon::point(i).isNull())
      polygon << QPolygon::point(i);

  return polygon;
}

