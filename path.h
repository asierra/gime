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

#ifndef PATH_H
#define PATH_H

#include <QPolygon>
#include "tablemodel.h"


class Path;
typedef Path *PathPointer;


class Path : public QPolygon
{
 public:
  Path(int size);	
  Path(const QPolygon & polygon);

  void setPosition(QPointF);
  void deletePosition();
	
  QPoint point () const  { return QPolygon::point(image_idx); }
  QPoint point (int i) const  { return QPolygon::point(i); }
  QRectF boundingRectAdjacent() const;
  bool isNull () const { return QPolygon::point(image_idx).isNull(); }
  bool isNull (int idx) const { return QPolygon::point(idx).isNull(); }
  QDateTime dateTimeAt(int i)  {
    if (model != NULL)
      return model->dateTimeAt(i);
    else
      return QDateTime();
  }
	
  QString getName()  { return name; }
  void setName(const QString n)  { name = n; }
	
  QString toEPS();

  // This polygon only have the not null points, so may be smaller than path
  QPolygon toPolygon();
	
  static int image_idx; 
  static Path *selected;
  static TableModel *model;
  static QColor defaultColor;
  QColor color;
  bool visible;
  int width;
  
  friend QDataStream& operator << (QDataStream&, const PathPointer&);
  friend QDataStream& operator >> (QDataStream&, PathPointer&);

 private:
  QString name;
};


QDataStream& operator << (QDataStream&, const PathPointer&);
QDataStream& operator >> (QDataStream&, PathPointer&);


#endif
