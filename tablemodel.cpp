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

#include "tablemodel.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>

TableModel::TableModel(QObject *parent)
     : QAbstractTableModel(parent)
{
}


QStringList	TableModel::fullStringList () const
{
	QStringList list;
	for (int i=0; i < listNames.size(); i++) {
		QString s = listNames.at(i) + "|" + listDates.at(i).toString("yyyy-MM-dd-hh:mm");
		list.append(s);
	}
	return list;
}


QStringList	TableModel::dateStringList (QString format) const
{
	QStringList list;
	for (int i=0; i < listDates.size(); i++) {
		QString s = listDates.at(i).toString(format);
		list.append(s);
	}
	return list;
}


void TableModel::setStringList ( const QStringList & strings ) 
{ 
	listNames = strings; 
	for (int i=0; i < listNames.size(); i++)
		listDates.append(QDateTime::currentDateTime());

	insertList();
}

void TableModel::setFullStringList ( const QStringList & strings ) 
{ 
	for (int i=0; i < strings.size(); i++) {
		QString s = strings.at(i);
		QStringList l = s.split("|");
		QString ima = l.at(0);

		listNames.append(ima);
		if (l.size()>1) {
			QString dat = l.at(1);
			listDates.append(QDateTime::fromString(dat, "yyyy-MM-dd-hh:mm"));
		} else
			listDates.append(QDateTime::currentDateTime());
	}
	insertList();
}

void TableModel::setDatesList ( const QStringList & strings ) 
{ 
	listDates.clear();
	if (listNames.size()==strings.size())  {
		for (int i=0; i < strings.size(); i++)
			listDates.append(QDateTime::fromString(strings.at(i), "yyyy-MM-dd-hh:mm"));
		QModelIndex index1 = index(0, 1);
		QModelIndex index2 = index(rowCount()-1, 1);
		emit(dataChanged(index1, index2));
	}
}

void TableModel::changeFilePath(QString filePath)
{
  for (int i=0; i < listNames.size(); i++) {
    QString fileName = QFileInfo(listNames.at(i)).fileName();
    QString path = QDir(filePath).filePath(fileName);
    qDebug() << listNames.at(i) << " -> " << path << endl;
    listNames.replace(i, path);
  }
}


void TableModel::sort_by_date() 
{
  QStringList names_aux = listNames;
  QList<QDateTime> dates_sorted = listDates;

  qSort(dates_sorted.begin(), dates_sorted.end());

  for (int i=0; i < dates_sorted.size(); i++) {
    int i2 = listDates.indexOf(dates_sorted.at(i));
    listNames.replace(i, names_aux.at(i2));
    //    qDebug() << "Cambiando " << i << " , " << i2 << endl;  
    
  }
  listDates = dates_sorted;
  QModelIndex index1 = index(0, 1);
  QModelIndex index2 = index(rowCount()-1, 1);
  emit(dataChanged(index1, index2));
  //  qDebug() << listNames << endl;
}

void TableModel::sort_by_name() 
{
  QStringList names_sorted = listNames;
  QList<QDateTime> dates_aux = listDates;

  qSort(names_sorted.begin(), names_sorted.end());

  for (int i=0; i < names_sorted.size(); i++) {
    int i2 = listNames.indexOf(names_sorted.at(i));
    listDates.replace(i, dates_aux.at(i2));
    //    qDebug() << "Cambiando " << i << " , " << i2 << endl;      
  }
  listNames = names_sorted;
  QModelIndex index1 = index(0, 1);
  QModelIndex index2 = index(rowCount()-1, 1);
  emit(dataChanged(index1, index2));
  //  qDebug() << listNames << endl;
}


int TableModel::rowCount(const QModelIndex &parent) const
 {
     Q_UNUSED(parent);
     return listNames.size();
 }

 int TableModel::columnCount(const QModelIndex &parent) const
 {
     Q_UNUSED(parent);
     return 2;
 }


QVariant TableModel::data(const QModelIndex &index, int role) const
 {	
   if (!index.isValid())
     return QVariant();

   if (index.row() >= listNames.size() || index.row() < 0)
     return QVariant();

   if (role == Qt::DisplayRole) {
     if (index.column() == 0) {
       QFileInfo pathInfo(listNames.at(index.row()));
       return pathInfo.fileName();	
     } else if (index.column() == 1)
       return listDates.at(index.row()).toString("yyyy-MM-dd-hh:mm");
   }
   return QVariant();
 }


QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
     if (role != Qt::DisplayRole)
         return QVariant();

     if (orientation == Qt::Horizontal) {
         switch (section) {
             case 0:
                 return tr("Imagen");

             case 1:
                 return tr("Fecha");

             default:
                 return QVariant();
         }
     }
     return QVariant();
 }

bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
 {
     Q_UNUSED(index);
     beginInsertRows(QModelIndex(), position, position+rows-1);
     endInsertRows();
     return true;
 }


bool TableModel::insertList()
{
	beginInsertRows(QModelIndex(), 0, listNames.size()-1);
	endInsertRows();	
	QModelIndex index1 = index(0, 0);
	QModelIndex index2 = index(rowCount()-1, 1);
	emit(dataChanged(index1, index2));
	return true;
}


bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
 {
     Q_UNUSED(index);
     beginRemoveRows(QModelIndex(), position, position+rows-1);

     for (int row=0; row < rows; ++row) {
         listNames.removeAt(position);
	     listDates.removeAt(position);
     }

     endRemoveRows();
     return true;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{ 
	if (index.isValid() && role == Qt::EditRole) {
		int row = index.row();

		QString s = listNames.value(row);

		if (index.column() == 0)
			listNames.replace(row, s);
		else if (index.column() == 1) { 
			s = value.toString();
			listDates.replace(row, QDateTime::fromString(s, "yyyy-MM-dd-hh:mm"));
		} else
			return false;

		emit(dataChanged(index, index));

		return true;
	}
	return false;
}


Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}



QString	TableModel::dateSuggestedFormat(int space) const
{
	QString format;
	
	int day, month, year, hour, min;
	bool uday=false, umonth=false, uyear=false, uhour=false, umin=false;
	if (space==0)
		format = "MMdd";
	else {
		year = listDates.at(0).date().year();
		month = listDates.at(0).date().month();
		day = listDates.at(0).date().day();
		hour = listDates.at(0).time().hour();
		min = listDates.at(0).time().minute();
		for (int i=space; i < listDates.size(); i+=space) {	
			if (!uday && day != listDates.at(i).date().day())
				uday = true;
			if (!umonth && month != listDates.at(i).date().month())
				umonth = true;
			if (!uyear && year != listDates.at(i).date().year())
				uyear = true;
			if (!uhour && hour != listDates.at(i).time().hour())
				uhour = true;
			if (!umin && min != listDates.at(i).time().minute())
				umin = true;
		}
		if (uyear)
			format += "yyyy";
		if (umonth)
			format += "MM";
		if (uday)
			format += "dd";
		if (uhour)
			format += "hh";
		if (umin)
			format += "mm";
	}

	return format;
}


int TableModel::imagesPerDay()
{
  int day;
  int i;
  
  for (i=0; i < listDates.size(); i++) {
    if (i == 0)
      day = listDates.at(i).date().day();
    else
      if (listDates.at(i).date().day() > day)
	return i;

  }
  return i;
}
