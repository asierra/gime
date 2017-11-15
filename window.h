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

#ifndef WINDOW_H
#define WINDOW_H


#include <QSplitter>
#include <QListView>
#include <QTableView>

#include "tablemodel.h"

class QLabel;
class QGraphicsView; 
class QMenu;
class GraphWidget;
class QStringListModel;
class Path;
class QToolBar;
class QDateTimeEdit;
class GimeScene;
class QSpinBox;
class CoordTab;

class Window : public QSplitter {
  Q_OBJECT

 public:
  Window();
  ~Window();
  void selImage(int i);
		
 protected:
  GraphWidget *view;
  GimeScene *escena;
  QTableView *listImages;
  QListView *listPaths;
  void keyPressEvent(QKeyEvent *event);
		    
  public slots:
    void cargaImagenes();	
    void borraListaImagenes();
    void acerca();
    void help();
    bool nuevaSesion();
    bool cargaSesion();
    bool cargaSesionComo();
    bool guardaSesion();
    bool guardaSesionComo();
    bool guardaSesionActual();
    bool guardaTrayectoria();
    bool exportPathAsEPS();
    bool exportAsAPNG();
    bool renderToJPEG();
    bool renderToPNG();
    
    bool extractDatesFromNames();
    void cambiaLetra();
    void cambiaAnchoLinea();
    void cambiaEstiloLinea();
    
    void cambiaFecha();
    void imageSelected(const QModelIndex &index);
    void pathClicked(const QModelIndex &index);
    void imageFirst();
    void imagePrev();
    void imageNext();
    void imageLast();
    void addPath();
    void removePath();
    void drawPath();
    void drawLabels();
    void toggleLabel();
    void spaceLabels(int);
    void labelManualFormat();
    void drawArrows();
    void drawHourIcons();
    void setSelectedColor();
    void agregaTexto();
    void agregaGriego();
    bool asignaFecha(const QModelIndex &index);
	
 private:
    void updateview();
    QWidget *createWorkarea();
    QWidget *createMenubar(QWidget * window);
    void addText(QPointF &pos, QString &text, QFont &font);
    QMenu *fileMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;
    QMenu *editMenu;
    TableModel *imagemodel;
    QStringListModel *pathmodel;
    QToolBar *path_toolbar;
    QAction *loadAction;
    QAction *drawpathAction;
    QAction *drawLabelsAction;
    QAction *drawArrowsAction;
    QAction *drawHourIconsAction;
    QAction *pathColorAction;
    QAction *action_year;
    QAction *action_mounth;
    QAction *action_day;
    QAction *action_hour;
    QAction *action_min;
    QList<Path*> pathlist;
    QString filename;
    QDateTimeEdit *datetime;
    QSpinBox *spinLabels;
    CoordTab *coordtab;
};
#endif
