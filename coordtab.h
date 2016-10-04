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
#include <QTableView>
#include <QToolBar>
#include <QAction>
#include <QStandardItemModel>
#include "gime_scene.h"


class CoordTab : public QSplitter {
  Q_OBJECT

 public:
  CoordTab(QWidget * parent = 0);
  ~CoordTab();
  void setScene(GimeScene *scene) { this->scene = scene; }
  
 protected:
  QTableView *listcoords;
		    
  public slots:
    void addCoord();
    void removeCoord();
    void toogleVisible();
    
private slots:
  
  void clickedSlot(QModelIndex index)
  {
    QMessageBox::information(NULL,"QTableView Item Clicked",index.data().toString());
  };
  
   void doubleClickedSlot(QModelIndex index)
  {
    QMessageBox::information(NULL,"QTableView Item Double Clicked",index.data().toString());
  }; 
  
 private:
    void createWorkarea();
    QStandardItemModel *model;
    QToolBar *toolbar;
    QString filename;
    GimeScene *scene;
    int ncoords;
    QAction *visibleAction;

};



#endif
