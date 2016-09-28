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
#include "gime_scene.h"
#include "graphwidget.h"
#include "window.h"
#include <QtGui>

#include <math.h>
#include <string>
using namespace std;


GraphWidget::GraphWidget(Window *parent)
    : QGraphicsView(parent) 
{    
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setMinimumSize(512, 512);
	if (parent != 0)
		window = parent;
}


void GraphWidget::clear()
{
	fondo = QImage();
	if (scene() != NULL) {
		scene()->clear();
		delete scene();
	}
	resetCachedContent();
}


void GraphWidget::setImage(QString filename)
{
	fondo.load(filename);
   	scene()->setSceneRect(0, 0, fondo.width(), fondo.height());
	QStringList slist = fondo.textKeys();
//	printf("Cagando imagen %s %d\n", filename.toStdString().c_str(), slist.size());
	setWindowTitle(filename);
	resetCachedContent();
	scene()->update();
}


void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    QRectF sceneRect = this->sceneRect();

	QColor color(Qt::white);

	if (!fondo.isNull()) {
		painter->drawImage(sceneRect, fondo);
		color.setAlphaF(0.25);
	}
	painter->fillRect(sceneRect, QBrush(color));
}


void GraphWidget::keyPressEvent(QKeyEvent *event)
{
  switch (event->key()) {
  case Qt::Key_E: // Encajar
    fitInView(this->sceneRect());
    break;
  case Qt::Key_F:
    window->toggleLabel();
    break;
  case Qt::Key_S: {
    QImage img(scene()->width(),scene()->height(),QImage::Format_ARGB32_Premultiplied);
    QPainter p(&img);
    QRectF sceneRect = this->sceneRect();
    if (!fondo.isNull()) 
      p.drawImage(sceneRect, fondo);
    scene()->render(&p);
    p.end();
    img.save("XXX.png"); }
    break;
  case Qt::Key_PageUp:
    window->imagePrev();
    break;
  case Qt::Key_PageDown:
    window->imageNext();
    break;
  case Qt::Key_Home:
    window->imageFirst();
    break;
  case Qt::Key_End:
    window->imageLast();
    break; 
  case Qt::Key_Backspace:
    if (QMessageBox::question(this, tr("Eliminar nodo"),
			      QObject::trUtf8("¿Desea eliminar el nodo?"),
			      QMessageBox::Yes | QMessageBox::No)) {
      GimeScene *escena = (GimeScene*)scene();
      escena->deletePosition();
    }
    break;
  default:
    QGraphicsView::keyPressEvent(event);
  }
}


void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}


void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}


void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}


void GraphWidget::selectPath()
{
	scene()->update();
}



void GraphWidget::mouseDoubleClickEvent(QMouseEvent  *event)
{
  GimeScene *escena = (GimeScene*)scene();
  escena->setPathPosition(mapToScene(event->pos()));
  QGraphicsView::mouseDoubleClickEvent(event);
}

