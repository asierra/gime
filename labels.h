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

#ifndef LABELS_H
#define LABELS_H

#include <QGraphicsItem>

class Path;


class Labels : public QGraphicsItem
{ 
public:
    Labels(Path*);
	Path *getPath()  { return path; }
	void populate();
	void update_text();
	void update_shown();
	void update_font();
	void updatePosition();
	void clear();
	
	static QFont font;
	static QStringList texts;
	static int space;
	static QList<bool> shown;
 
 protected:
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);  
        QRectF boundingRect() const;
	
private:
	Path *path;
};


#endif
