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

#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>

#include "path.h"

class GraphWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE


class Node : public QGraphicsItem
{
 public:
  Node(Path*);
  void updatePosition();
  static float radius;	
  Path *getPath()  { return path; }
	
 protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);  
  QRectF boundingRect() const;
  QPainterPath shape() const;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
  
 private:
  Path *path;
};


#endif
