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

#include "node.h"
#include "lines.h"
#include "labels.h"
#include "path.h"
#include "marker.h"
#include "gime_scene.h"


GimeScene::GimeScene(QObject * parent)
    : QGraphicsScene(parent)
{    
  setItemIndexMethod(QGraphicsScene::NoIndex);
  pathgroup = 0;
}


void GimeScene::clear()
{
	pathgroup = 0;
	qDeleteAll(nodelist);
	qDeleteAll(itemlist);
	qDeleteAll(labellist);
	nodelist.clear();
	itemlist.clear();
	labellist.clear();
	QGraphicsScene::clear();
}


void GimeScene::addPath(Path *path)
{	
	Node *n = new Node(path);
	nodelist << n;
	addItem(n);
	
	QGraphicsItem *item = new Lines(path);
	itemlist << item;
	
	if (pathgroup==0)
		pathgroup = createItemGroup(itemlist);
	else
		pathgroup->addToGroup(item);  
	
	item = new Labels(path);
	addItem(item);
	labellist << item;
}


void GimeScene::removePath()
{	
	if (Path::selected != NULL) {
		int idx = 0;
		foreach (Node *node, nodelist) {
			if (Path::selected==node->getPath())
				break;
			idx++;
		}
		//printf("removing path %d\n", idx);
		Node *node = nodelist.at(idx);
		QGraphicsItem *item = itemlist.at(idx);
		if (pathgroup!=0)
			pathgroup->removeFromGroup(item);
		removeItem(node);
		removeItem(item);
		nodelist.removeAt(idx);
		itemlist.removeAt(idx);
		delete node;
		delete item;
	}
}


void GimeScene::updateTextLabels()
{
  if (!labellist.isEmpty()) {
    foreach (QGraphicsItem* item, labellist) {
      Labels *labels = (Labels *)item;
      labels->update_text();
    }
    QGraphicsScene::update();
  }
}


void GimeScene::updateShownLabels()
{
  if (!labellist.isEmpty()) {
    foreach (QGraphicsItem* item, labellist) {
      Labels *labels = (Labels *)item;
      labels->update_shown();
    }
    QGraphicsScene::update();
  }
}


void GimeScene::updateFontLabels()
{
  if (!labellist.isEmpty()) {
    foreach (QGraphicsItem* item, labellist) {
      Labels *labels = (Labels *)item;
      labels->update_font();
    }
    QGraphicsScene::update();
  }
}


void GimeScene::updatePositions()
{
  foreach (Node *node, nodelist) {
    node->updatePosition();
  }
  QGraphicsScene::update();
}


void GimeScene::setPathPosition(QPointF p)
{
  if (nodelist.size() > 0) {
    Path *path = (Path::selected==NULL) ? nodelist.last()->getPath(): Path::selected;
    path->setPosition(p);
    
    if (!labellist.isEmpty()) {
      foreach (QGraphicsItem* item, labellist) {
	Labels *labels = (Labels *)item;
	if (labels->getPath()==path)
	  labels->updatePosition();
      }
    }
    
    foreach (Node *node, nodelist) {
      if (node->getPath()==path) {
	node->updatePosition();
	node->update();
      } 
    }
    QGraphicsScene::update();
  }
}


void GimeScene::deletePosition()
{	
  Path *path = Path::selected;
  
  if (nodelist.size() > 0 && path!=NULL) {
    path->deletePosition();
    QGraphicsScene::update();
    //		update();
  }
}


void GimeScene::addMarker(Marker *item)
{
  addItem(item);
  markerlist << item;
}


void GimeScene::removeMarker()
{/*
  removeItem(item);
  nodelist.removeAt(idx);
  itemlist.removeAt(idx);
  delete node;
  delete item;*/
}


void GimeScene::showPaths(bool unhide)
{
  if (Path::selected != NULL) {
    int idx = 0;
    foreach (Node *node, nodelist) {
      if (Path::selected==node->getPath())
	break;
      idx++;
    }
    QGraphicsItem *item = itemlist.at(idx);
    
    if (unhide) {
      item->show();
      //     pathgroup->hide();
    } else {
      pathgroup->show();
      item->hide();
    }
  } else if (unhide) {
    if (pathgroup!=0)
      pathgroup->show();
  } else if (pathgroup!=0)
    pathgroup->hide();
}


void GimeScene::showLabels(bool unhide)
{
  if (!labellist.isEmpty()) {
    foreach (QGraphicsItem* item, labellist) {      
      if (unhide) 
	item->show();
      else
	item->hide();
    }
  }
}


void GimeScene::showMarkers(bool unhide)
{
  if (!markerlist.isEmpty()) {
    foreach (QGraphicsItem* item, markerlist) {      
      if (unhide) 
	item->show();
      else
	item->hide();
    }
  }
}
