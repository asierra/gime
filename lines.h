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

#ifndef LINES_H
#define LINES_H

#include <QGraphicsItem>

class Path;


class Lines : public QGraphicsItem
{
 public:
  Lines(Path*);
  
  Path *getPath()  { return path; }
  
  static bool show_arrows;
  static bool show_icons;
	
 protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); 
  QRectF boundingRect() const;

  void draw_icons( QPainter *painter );
	
private:
	Path *path;
};


#endif
