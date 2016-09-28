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

#include "textdialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

TextDialog::TextDialog(QWidget *parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
{
	
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}


TextDialog::~TextDialog()
{
}


void TextDialog::createLayout(QLayout *layout)
{
	QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    mainLayout->addWidget(&label);
    mainLayout->addLayout(layout);
    mainLayout->addWidget(buttonBox);
	this->setLayout(mainLayout);
}


QLayout *TextDialog::buildTextInput(QStringList labels, QStringList text)
{
	QHBoxLayout *textLayout = new QHBoxLayout();
	textLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	lineEdits.clear();
	for (int i=0; i < labels.size(); i++) {
		QLabel *label = new QLabel(labels.at(i));
		label->setFont(QFont("Courier"));
		textLayout->addWidget(label);
		if (text.size() > i) {   // Ojo, y si text > labels?
			QLineEdit *ledit = new QLineEdit();
			QString t = text.at(i);
			ledit->setText(t);
			ledit->setMaxLength(t.size());		
			QString mask;
			mask.fill('N', t.size());
			ledit->setInputMask(mask);
			ledit->setFont(QFont("Courier"));
			lineEdits.append(ledit);
			textLayout->addWidget(ledit);
		}		
	}
	textLayout->addStretch();

	return textLayout;
}


void TextDialog::setLabelText(const QString &text)
{
    label.setText(text);
}


QString TextDialog::labelText() const
{
    return label.text();
}


void TextDialog::setOkButtonText(const QString &text)
{
    buttonBox->button(QDialogButtonBox::Ok)->setText(text);
}

QString TextDialog::okButtonText() const
{
    return buttonBox->button(QDialogButtonBox::Ok)->text();
}


void TextDialog::setCancelButtonText(const QString &text)
{
    buttonBox->button(QDialogButtonBox::Cancel)->setText(text);
}

QString TextDialog::cancelButtonText() const
{
    return buttonBox->button(QDialogButtonBox::Cancel)->text();
}


QStringList TextDialog::collectTexts() const
{
  QStringList l;
	
  for (int i=0; i < lineEdits.size(); i++) {
    qDebug() << "Linedits " << lineEdits.at(i)->text() << endl;
    l.append(lineEdits.at(i)->text());
  }
  return l;
}


QStringList TextDialog::getText(QWidget *parent, const QString &title, const QString &label,
							  QStringList &labels, QStringList &text, 
							  bool *ok, Qt::WindowFlags flags)
{
    TextDialog dialog(parent, flags);
    dialog.setWindowTitle(title);
    dialog.setLabelText(label);
	dialog.createLayout(dialog.buildTextInput(labels, text));
	
    int ret = dialog.exec();
    if (ok)
        *ok = !!ret;
    if (ret) {
        return dialog.collectTexts(); //
    } else {
        return QStringList();
    }
}
