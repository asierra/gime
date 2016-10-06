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
#include <QDebug>
#include "coordtab.h"
#include "marker.h"

Georefencia *georeferente;


CoordTab::CoordTab(QWidget * parent): QSplitter(parent)
{
  setOrientation(Qt::Vertical);
  listcoords = NULL;
  ncoords = 0;
  scene = NULL;
  georeferente = NULL;
  createWorkarea();
}


CoordTab::~CoordTab()
{
  delete listcoords;
}


void CoordTab::createWorkarea()
{
  toolbar = new QToolBar("coord toolbar", this);  
  addWidget(toolbar);
  
  visibleAction = new QAction(QIcon(":/icons/eye.png"), "Ver georreferencias", this);
  visibleAction->setCheckable(true);
  visibleAction->setChecked(true);
  connect(visibleAction, SIGNAL(triggered()), this, SLOT(toogleVisible()));
  
  toolbar->addAction(visibleAction);  
  
  QAction *action = new QAction(QIcon(":/icons/list-add.png"), "Nueva coordenada", this);
  connect(action, SIGNAL(triggered()), this, SLOT(addCoord()));
  toolbar->addAction(action);  
  
  action = new QAction(QIcon(":/icons/list-remove.png"), "Elimina coordenada", this);
  connect(action, SIGNAL(triggered()), this, SLOT(removeCoord()));
  toolbar->addAction(action);
  
  action = new QAction(QIcon(":/icons/mapa.png"), "Calcula georreferenciación", this);
  connect(action, SIGNAL(triggered()), this, SLOT(computeGeoreferencing()));
  toolbar->addAction(action);  

  listcoords = new QTableWidget(this);
  listcoords->setRowCount(2);
  listcoords->setColumnCount(4);
  QStringList m_TableHeader;
  m_TableHeader << "X" << "Y" << "lo" << "la";
  listcoords->setHorizontalHeaderLabels(m_TableHeader);
  listcoords->setAlternatingRowColors(true);
  addWidget(listcoords);
}


void CoordTab::toogleVisible()
{
  if (visibleAction->isChecked())
    scene->showMarkers(true);
  else
    scene->showMarkers(false);
}


void CoordTab::addCoord()
{
  Marker *marker = new Marker(ncoords++);
  marker->setModel(listcoords);
  if (scene != NULL)
    scene->addMarker(marker);
}


void CoordTab::removeCoord()
{
  qDebug() << "Por implementar" << endl;
  --ncoords;
}


void CoordTab::computeGeoreferencing()
{
  if (georeferente==NULL)
    georeferente = new Georefencia();

  georeferente->x1 = getValue(0, 0);
  georeferente->y1 = getValue(0, 1);
  georeferente->x2 = getValue(1, 0);
  georeferente->y2 = getValue(1, 1);

  float lo1 = getValue(0, 2);
  float la1 = getValue(0, 3);
  float lo2 = getValue(1, 2);
  float la2 = getValue(1, 3);

  if (lo1==lo2 || la1==la2) {
    QMessageBox::warning(this, "Error", "Corrige latitudes y longitudes.");
    return;
  }
  
  georeferente->lo1 = lo1;
  georeferente->la1 = la1;
  georeferente->lo2 = lo2;
  georeferente->la2 = la2;
}


void CoordTab::feedFromGeoreferencing()
{
  if (georeferente!=NULL) {
    listcoords->setItem(0, 0, new QTableWidgetItem(QString::number(georeferente->x1)));
    listcoords->setItem(0, 1, new QTableWidgetItem(QString::number(georeferente->y1)));
    listcoords->setItem(0, 2, new QTableWidgetItem(QString::number(georeferente->lo1)));
    listcoords->setItem(0, 3, new QTableWidgetItem(QString::number(georeferente->la1)));
    listcoords->setItem(1, 0, new QTableWidgetItem(QString::number(georeferente->x2)));
    listcoords->setItem(1, 1, new QTableWidgetItem(QString::number(georeferente->y2)));
    listcoords->setItem(1, 2, new QTableWidgetItem(QString::number(georeferente->lo2)));
    listcoords->setItem(1, 3, new QTableWidgetItem(QString::number(georeferente->la2)));
  }
}


Georefencia::Georefencia()
{
  x1 = y1 = x2 = y2 = 0.0;
}


void Georefencia::compute(float x, float y, float &lo, float &la)
{
  lo = lo1 + (x1 - x) * (lo2 - lo1) / (x1 - x2);
  la = la1 + (y1 - y) * (la2 - la1) / (y1 - y2);
}


QDataStream& operator<<(QDataStream& stream, const GeorefenciaPointer &georf)
{
  stream << georf->x1;
  stream << georf->y1;
  stream << georf->lo1;
  stream << georf->la1;
  stream << georf->x2;
  stream << georf->y2;
  stream << georf->lo2;
  stream << georf->la2;
        
  return stream;
}


QDataStream& operator>>(QDataStream& stream, GeorefenciaPointer &georf)
{
  georf = new Georefencia();

  stream >> georf->x1;
  stream >> georf->y1;
  stream >> georf->lo1;
  stream >> georf->la1;
  stream >> georf->x2;
  stream >> georf->y2;
  stream >> georf->lo2;
  stream >> georf->la2;

  return stream;
}
