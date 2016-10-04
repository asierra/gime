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

Marker *marker;

CoordTab::CoordTab(QWidget * parent): QSplitter(parent)
{
  setOrientation(Qt::Vertical);
  model = new QStandardItemModel(2, 4, this);
  model->setHorizontalHeaderItem(0, new QStandardItem(QString("X")));
  model->setHorizontalHeaderItem(1, new QStandardItem(QString("Y")));
  model->setHorizontalHeaderItem(2, new QStandardItem(QString("lo")));
  model->setHorizontalHeaderItem(3, new QStandardItem(QString("la")));
  listcoords = NULL;
  ncoords = 0;
  scene = NULL;
  
  createWorkarea();
}


CoordTab::~CoordTab()
{
  delete model;
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

  listcoords = new QTableView(this);
  listcoords->setModel(model);
  listcoords->setAlternatingRowColors(true);
  listcoords->setSelectionBehavior(QAbstractItemView::SelectItems);
  listcoords->setTextElideMode(Qt::ElideLeft);  
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
    marker = new Marker(ncoords++);
    marker->setModel(model);
    if (scene != NULL)
      scene->addMarker(marker);
}


void CoordTab::removeCoord()
{
  qDebug() << "Por implementar" << endl;
  --ncoords;
}
