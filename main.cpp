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

#include <QApplication>
#include <QDebug> 
#include "window.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
//	QApplication::instance()->setAttribute(Qt::AA_DontUseNativeMenuBar);
	app.setWindowIcon(QIcon(":/icons/cca128.png"));

	Window window;

	if (argc > 1) {
	  window.setFileName(argv[1]);
	  window.cargaSesion();
	  qDebug() << "Argv " << argv[1]; // << std::endl;
	}
	
	window.show();

	return app.exec();
}
