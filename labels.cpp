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

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include "labels.h"
#include "path.h"


int Labels::space = 1;
QFont Labels::font;
QStringList Labels::texts;
QList<bool> Labels::shown;


Labels::Labels(Path *p): path(p)
{
  setZValue(-1);
  populate();
}


void Labels::clear()
{
  QList<QGraphicsItem*> itemlist = childItems();
  if (!itemlist.isEmpty()) {
    qDeleteAll(itemlist);
    itemlist.clear();
  }
}


void Labels::populate()
{
  QPoint offset(5, 5);

  clear();
  for (int i=0; i < path->size(); i++) {
    QPoint p = path->point(i) + offset;
    QGraphicsSimpleTextItem *item = new QGraphicsSimpleTextItem(this);
    item->setPos(p);
    item->setFont(font);
    item->setFlag(QGraphicsItem::ItemIsSelectable);
    item->setFlag(QGraphicsItem::ItemIsMovable);
  }
}


void Labels::update_text()
{
  QList<QGraphicsItem*> itemlist = childItems();

  for (int i=0; i < texts.size(); i++) {
    if (!path->isNull(i)) {      
      QGraphicsSimpleTextItem *item = (QGraphicsSimpleTextItem*)itemlist.at(i);
	item->setText(texts.at(i));
    }
  }
  //  printf("Texto actualizado %s\n", texts.at(0).toStdString().c_str());
}


void Labels::update_font()
{
  QList<QGraphicsItem*> itemlist = childItems();

  for (int i=0; i < itemlist.size(); i++) {
    QGraphicsSimpleTextItem *item = (QGraphicsSimpleTextItem*)itemlist.at(i);
    item->setFont(font);
  }
}


void Labels::update_shown()
{
  QList<QGraphicsItem*> itemlist = childItems();

  for (int i=0; i < texts.size(); i++) {
    QGraphicsItem* item = itemlist.at(i);
    if (!path->isNull(i) && shown.at(i))
      item->show();
    else
      item->hide();	
  }
}


void Labels::updatePosition()
{
  QPoint offset(5, 5);
  QPoint p = path->point() + offset;

  QList<QGraphicsItem*> itemlist = childItems();
  QGraphicsSimpleTextItem *item = (QGraphicsSimpleTextItem*)itemlist.at(Path::image_idx);
  item->setPos(p);
}


void Labels::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{
}

QRectF Labels::boundingRect() const
{
  return QRectF();
}
