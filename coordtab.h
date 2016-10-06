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

#ifndef COORDTAB_H
#define COORDTAB_H

#include <QtGui>
#include <QSplitter>
#include <QTableWidget>
#include <QToolBar>
#include <QAction>
#include "gime_scene.h"


class Georefencia;


class CoordTab : public QSplitter {
  Q_OBJECT

 public:
  CoordTab(QWidget * parent = 0);
  ~CoordTab();
  void setScene(GimeScene *scene) { this->scene = scene; }
  void feedFromGeoreferencing();
  float getValue(int row, int col) {    
    QModelIndex index = listcoords->model()->index(row, col, QModelIndex());
    return listcoords->model()->data(index).toFloat();
  }
  
 protected:
  QTableWidget *listcoords;
		    
  public slots:
    void addCoord();
    void removeCoord();
    void toogleVisible();
    void computeGeoreferencing();
    
 private:
    void createWorkarea();
    QToolBar *toolbar;
    QString filename;
    GimeScene *scene;
    int ncoords;
    QAction *visibleAction;

};


typedef Georefencia *GeorefenciaPointer;

class Georefencia {
 public:
  Georefencia();
  void compute(float x, float y, float &lo, float &la);
  
  float x1, y1, x2, y2;
  float lo1, la1, lo2, la2;

  friend QDataStream& operator << (QDataStream&, const GeorefenciaPointer&);
  friend QDataStream& operator >> (QDataStream&, GeorefenciaPointer&);

};

QDataStream& operator << (QDataStream&, const GeorefenciaPointer&);
QDataStream& operator >> (QDataStream&, GeorefenciaPointer&);

#endif
