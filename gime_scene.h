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

#ifndef GIMESCENE_H
#define GIMESCENE_H

#include <QGraphicsScene>

class Node;
class Path;
class Marker;


class GimeScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GimeScene(QObject * parent = 0);

	void addPath(Path *path);
	void removePath();
	void showPaths(bool show=true);
	void showLabels(bool show=true);
	void showNodes(bool show=true);
	void addMarker(Marker *item);
	void removeMarker();
	void showMarkers(bool show=true);
	void updateTextLabels();
	void updateShownLabels();
	void updateFontLabels();
	void updatePositions();
	void setPathPosition(QPointF);
	void deletePosition();
	void clear();
	
private:
	QList<Node*> nodelist;
	QList<QGraphicsItem*> itemlist;
	QList<QGraphicsItem*> labellist;
	QList<QGraphicsItem*> markerlist;
	QGraphicsItemGroup *pathgroup;
};


#endif
