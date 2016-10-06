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

#ifndef MARKER_H
#define MARKER_H

#include <QGraphicsItem>
#include <QTableWidget>



class Marker : public QGraphicsPathItem
{ 
 public:
  Marker(int n, QGraphicsItem * parent = 0);
  void setNumber(int i) { num = i; }
  void setModel(QTableWidget *m) { model = m; }
  
  QRectF boundingRect() const;

 protected:
  void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

 private:
  int num;
  int width, halfwidth, eyepos, eyewidth;
  QTableWidget *model;
};


#endif
