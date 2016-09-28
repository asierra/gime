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

#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QDateTimeEdit>


class TableModel : public QAbstractTableModel
{
  Q_OBJECT

 public:
  TableModel(QObject *parent=0);

  QStringList	stringList () const {  return listNames; }
  QStringList	fullStringList () const;
  QStringList	dateStringList (QString format="yyyy-MM-dd-hh:mm") const;
  QDateTime dateTimeAt(int i)  { return listDates.at(i); }
  QString	dateSuggestedFormat (int) const;
	
  void setStringList ( const QStringList & strings );
  void setFullStringList ( const QStringList & strings );
  void setDatesList ( const QStringList & dates );
	
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
  bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
  bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());

  bool insertList();

  // Imágenes por día
  int imagesPerDay();

	
  //     QList< QPair<QString, QString> > getList();

 private:
  QStringList listNames;
  QList<QDateTime> listDates;
};



#endif
