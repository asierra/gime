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

#include <qdatetime.h>
#include <qdebug.h>

int main() {
  //  QDateTime::fromString(f, format);
  qDebug() << "Current " << QDateTime::currentDateTime() << endl;
  //  QString date = "wa-00152011095.jpg";
  QString date = "wa-00152011095.jpg";
  QString format = "'wa-'hhmm'20'yy'095.jpg'";
  
  qDebug() << "Format " << format << " Date " << date << endl;
  qDebug() << QDateTime::fromString(date, format).addDays(95) << endl;
}
