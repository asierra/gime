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

#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>


class QStringList;


class TextDialog : public QDialog
{
  //  Q_OBJECT

 public:
  TextDialog(QWidget *parent = 0, Qt::WindowFlags flags = 0);
  ~TextDialog();

  void createLayout(QLayout *layout);
	
  void setLabelText(const QString &text);
  QString labelText() const;

  void setOkButtonText(const QString &text);
  QString okButtonText() const;

  void setCancelButtonText(const QString &text);
  QString cancelButtonText() const;

  QStringList collectTexts() const;
  
  QLayout *buildTextInput(QStringList labels, QStringList text);
	
  static QStringList getText(QWidget *parent, const QString &title, const QString &label,
			     QStringList &labels, QStringList &text,
			     bool *ok = 0, Qt::WindowFlags flags = 0);

 private:
  QLabel label;
  QList<QLineEdit *> lineEdits;
  QDialogButtonBox *buttonBox;
};


#endif
