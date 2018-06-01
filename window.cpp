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

#include <QtGui>
#include <QStringListModel>
#include <QPrinter>
#include <QTabWidget>

#include "lines.h"
#include "labels.h"
#include "path.h"
#include "gime_scene.h"
#include "window.h"
#include "graphwidget.h"
#include "textdialog.h"
#include "coordtab.h"


static QFont text_font;

extern int exportToAPNG(QString filename, QStringList list, GimeScene *escena=NULL);

extern Georefencia *georeferente;

QList<QGraphicsSimpleTextItem*> texts_list;


void Window::addText(QPointF &pos, QString &text, QFont &font)
{
  if (!text.isEmpty()) {
    QGraphicsSimpleTextItem *item = new QGraphicsSimpleTextItem();
    item->setFlag(QGraphicsItem::ItemIsSelectable);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setText(text);
    item->setPos(pos);
    item->setFont(font);
    escena->addItem(item);
    texts_list.append(item);
  }
}

Window::Window()
{
  createWorkarea();
  setStretchFactor(0, 1);
  setStretchFactor(1, 0);
  imagemodel = NULL;
  pathmodel = NULL;
  nuevaSesion();
  QFontDatabase::addApplicationFont(":fonts/WeatherFont.ttf");
  //  QString family = QFontDatabase::applicationFontFamilies(id).at(0);
  //  QFont monospace(family);
}


Window::~Window()
{	
  qDeleteAll(pathlist);
  delete imagemodel;
  delete pathmodel;
}


bool Window::nuevaSesion()
{  
  setWindowTitle(tr("GIME"));
  if (imagemodel != NULL)
    delete imagemodel;
  if (pathmodel != NULL)
    delete pathmodel;
  imagemodel = new TableModel(this);	
  Path::model = imagemodel;
  pathmodel = new QStringListModel(this);
  listPaths->setModel(pathmodel);
  listImages->setModel(imagemodel);
  connect(listImages->selectionModel(), SIGNAL(currentChanged(QModelIndex,
							      QModelIndex)),
	  this, SLOT(imageSelected(const QModelIndex&)));	
  filename = "sesion.gime";
  qDeleteAll(pathlist);
  pathlist.clear();
  qDeleteAll(texts_list);
  texts_list.clear();
  Labels::font = QFont();
  Labels::texts.clear();
  Labels::shown.clear();
  drawpathAction->setChecked(false);
  path_toolbar->setEnabled(false);
  escena = new GimeScene(this);
  view->clear();
  view->setScene(escena);
  coordtab->setScene(escena);

  return true;
}


bool Window::extractDatesFromNames()
{
  int k;
  bool ok;
	
  if (imagemodel->stringList().size()==0)
    return false;
		
  QStringList list =imagemodel->stringList();
		
  QFileInfo pathInfo(list.at(0));
  QString filenamei( pathInfo.fileName() );
	
  // Separa digitos de no digitos
  QRegExp rx("(\\d+)");
  QStringList ldigs = filenamei.split(QRegExp("\\D+"), QString::SkipEmptyParts);
  QStringList ltext = filenamei.split(rx, QString::SkipEmptyParts);
  
  k = rx.indexIn(filenamei);
  if (k==0)
    ltext.insert(0, QString());
  
  QString label = QString::fromUtf8("Usar solamente las letras yMdhmj\nyyyy=año MM=mes dd=dia hh=hora mm=min jjj=dia anual");
  
  QStringList formats = TextDialog::getText(this, tr("Formato para extraer fecha"),
					    label, ltext, ldigs, &ok);
  if (!ok || formats.isEmpty())
    return false;
  
  //qDebug() << formats << ", " << ltext << ", " << ldigs<<endl;

  int p=0;
  QList< QPair<int,int> > positions;
  QString format;
  QString format_sq;
  QRegExp rxMask("([yMdhmj]+)");
  int julian_pos = -1;
  
  // Construye format, todos los campos a ignorar se encierran entre ''
  for (k=0; k < formats.size(); k++) {
    p += ltext.at(k).size();
    if (ltext.at(k).size() > 0) {
      format.append(ltext.at(k));
      format_sq.append("'"+ltext.at(k)+"'");
    }
    QString f = formats.at(k);
    int i = rxMask.indexIn(f);
    if (i > -1) { 
      format.append(f);
      if (f.contains("jjj")) {
	int j = f.indexOf("jjj");
	QString l = f.left(j);
	QString r = f.right(f.size() - j - 3);
	format_sq.append(l + "'jjj'" + r);
	//	qDebug() << "l " << l << " r " << r << ", " << f.size() << ", " << j << endl; 
	julian_pos = format.indexOf("jjj");
      } else
	  format_sq.append(rxMask.cap(1));
    } else {
      // Numero no marcado
      format.append(f);
      format_sq.append("'"+f+"'");       
      qDebug() << f << endl;
    } 
    p += ldigs.at(k).size();
  }
  
  if (format.size() < 4)
    return false;
  
  QStringList fechas; 

  for (int i = 0; i < list.size(); ++i) {		
    QFileInfo pathInfo(list.at(i));
    QString filenamei( pathInfo.completeBaseName() );		
    QString f = filenamei;
    QDateTime dt;
    if (f.size() == format.size()) {
      if (julian_pos > -1) {
	int days = f.mid(julian_pos, 3).toInt() - 1;
	QString format_aux = format_sq;
	int julian_posx = format_aux.indexOf("jjj");
	format_aux.replace(julian_posx, 3, f.mid(julian_pos, 3));
	dt = QDateTime::fromString(f, format_aux);
	dt = dt.addDays(days);
	//qDebug() << "formatx " << format_aux << " days " << days << " fecha " << dt << endl;
      } else
	dt = QDateTime::fromString(f, format_sq);
           
      if ( dt.date().year() < 1960 && format.count("y") == 2 )
	dt = dt.addYears(100);
      
      fechas << dt.toString("yyyy-MM-dd-hh:mm");
    } else {
      printf("Error en fecha %d\n", i);
      return false; 
    }
  }
  imagemodel->setDatesList(fechas);
  imagemodel->sort_by_date();
  
  return true;
}


QWidget *Window::createMenubar(QWidget * window)
{
  QMenuBar* menubar = new QMenuBar(window);
  fileMenu = menubar->addMenu(tr("&File"));
  editMenu = menubar->addMenu(tr("&Edit"));
  QMenu *textMenu = menubar->addMenu(tr("&Text"));
  windowMenu = menubar->addMenu(tr("&Window"));
  helpMenu = menubar->addMenu(tr("&Help"));
	
  QAction *newAction = new QAction(QObject::trUtf8("&Nueva sesión"), this);	
  fileMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(nuevaSesion()));
  
  loadAction = new QAction(QIcon(":/icons/document-open.png"), tr("&Carga imagen(es)"), this);	
  fileMenu->addAction(loadAction);
  connect(loadAction, SIGNAL(triggered()), this, SLOT(cargaImagenes()));
	
  fileMenu->addSeparator();
	
  newAction = new QAction(QObject::trUtf8("C&arga sesión anónima"), this);	
  fileMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(cargaSesion()));
	
  newAction = new QAction(QObject::trUtf8("C&arga sesión existente"), this);	
  fileMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(cargaSesionComo()));
	
  fileMenu->addSeparator();
  newAction = new QAction(QObject::trUtf8("&Guarda sesión anónima"), this);	
  fileMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(guardaSesion()));
  newAction = new QAction(QObject::trUtf8("&Guarda sesión como..."), this);	
  fileMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(guardaSesionComo()));
  newAction = new QAction(QObject::trUtf8("&Guarda sesión actual"), this);
  newAction->setShortcut(QKeySequence(QKeySequence::Save));	
  fileMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(guardaSesionActual()));

  fileMenu->addSeparator();
  newAction = new QAction(QObject::trUtf8("Guarda &trayectoria"), this);
  connect(newAction, SIGNAL(triggered()), this, SLOT(guardaTrayectoria()));	
  fileMenu->addAction(newAction);
  
  fileMenu->addSeparator();
  newAction = new QAction(QObject::trUtf8("Exporta a &JPEG"), this);
  fileMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(renderToJPEG()));
	
  fileMenu->addSeparator();
  newAction = new QAction(QObject::trUtf8("Exporta a &PNG transparente"), this);
  fileMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(renderToPNG()));
	
  newAction = new QAction(QObject::trUtf8("&Exporta a EPS"), this);	
  fileMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(exportPathAsEPS()));
  
//	newAction = new QAction(QObject::trUtf8("Exporta a SVG"), this);	
//	fileMenu->addAction(newAction);
//	connect(newAction, SIGNAL(triggered()), this, SLOT(exportPathAsSVG()));
	
  newAction = new QAction(QObject::trUtf8("Exporta a APNG"), this);     
  fileMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(exportAsAPNG()));

  fileMenu->addSeparator();
  newAction = new QAction(QObject::trUtf8("&Salir"), this);
  newAction->setShortcut(QKeySequence(QKeySequence::Quit));
  fileMenu->addAction(newAction); 
  connect(newAction, SIGNAL(triggered()), qApp, SLOT(quit()));

  // Edit menú
  newAction = new QAction(QObject::trUtf8("Extrae &fechas de nombre"), this);	
  editMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(extractDatesFromNames()));

  newAction = new QAction(QObject::trUtf8("Cambia &tamaño o tipo de letra"), this);	
  editMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(cambiaLetra()));
  
  newAction = new QAction(QObject::trUtf8("Cambia &ancho de línea"), this);	
  editMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(cambiaAnchoLinea()));
  
  newAction = new QAction(QObject::trUtf8("Cambia &estilo de línea"), this);	
  editMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(cambiaEstiloLinea()));
  
  newAction = new QAction(QObject::trUtf8("&Ordena por fecha"), this);	
  editMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(sort_by_date()));
  
  newAction = new QAction(QObject::trUtf8("Ordena por &nombre"), this);	
  editMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(sort_by_name()));

  // Text menu
  newAction = new QAction(QObject::trUtf8("Activa &etiquetas"), this);	
  textMenu->addAction(newAction);
  //connect(newAction, SIGNAL(triggered()), this, SLOT(help()));
  
  newAction = new QAction(QObject::trUtf8("&Agrega texto"), this);	
  textMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(agregaTexto()));
  
  newAction = new QAction(QObject::trUtf8("A&grega griego"), this);	
  textMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(agregaGriego()));

  // Help menu
  newAction = new QAction(QObject::trUtf8("A&yuda"), this);	
  helpMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(help()));
  
  newAction = new QAction(QObject::trUtf8("&Acerca"), this);	
  helpMenu->addAction(newAction);
  connect(newAction, SIGNAL(triggered()), this, SLOT(acerca()));

  return menubar;
}


QWidget * Window::createWorkarea()
{	
  view = new GraphWidget(this);
	
  QSplitter *imaSplitter = new QSplitter(Qt::Vertical, this);
  //imaSplitter->setMaximumWidth(600);
  createMenubar(imaSplitter);

  QToolBar *toolbar = new QToolBar("image toolbar", this);
	
  toolbar->addAction(loadAction);
	
  QAction *action = new QAction(QIcon(":/icons/go-first.png"), "Primera imagen", this);
  connect(action, SIGNAL(triggered()), this, SLOT(imageFirst()));
  toolbar->addAction(action);
	
  action = new QAction(QIcon(":/icons/go-previous.png"), "Imagen previa", this);
  connect(action, SIGNAL(triggered()), this, SLOT(imagePrev()));
  toolbar->addAction(action);
	
  action = new QAction(QIcon(":/icons/go-next.png"), tr("Imagen siguiente"), this);
  connect(action, SIGNAL(triggered()), this, SLOT(imageNext()));
  toolbar->addAction(action);
  
  action = new QAction(QIcon(":/icons/go-last.png"), "Ultima imagen", this);
  connect(action, SIGNAL(triggered()), this, SLOT(imageLast()));
  toolbar->addAction(action);
	
  action = new QAction(QIcon(":/icons/folder-new.png"), "Nueva sesión", this);
  connect(action, SIGNAL(triggered()), this, SLOT(borraListaImagenes()));
  toolbar->addAction(action);
	
  listImages = new QTableView(this);
  listImages->setAlternatingRowColors(true);
  listImages->setSelectionBehavior(QAbstractItemView::SelectRows);
  listImages->setSelectionMode(QAbstractItemView::SingleSelection);
  listImages->setEditTriggers(QAbstractItemView::NoEditTriggers);
  listImages->setTextElideMode(Qt::ElideLeft);  
  listImages->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);	
	
  //    listImages->setSortingEnabled(true);
  //    listImages->sortByColumn(1, Qt::AscendingOrder);
    
  QSplitter *dateSplitter = new QSplitter(this);
  datetime = new QDateTimeEdit(QDateTime::currentDateTime(), this);
  datetime->setDisplayFormat("yyyy-MM-dd-hh:mm");
  dateSplitter->addWidget(datetime);
	
  QPushButton *button = new QPushButton("Cambia Fecha", this);
  connect(button, SIGNAL(pressed()), this, SLOT(cambiaFecha()));
  dateSplitter->addWidget(button);
	
  imaSplitter->addWidget(new QLabel(QString::fromUtf8("Imágenes"), this));
  imaSplitter->addWidget(toolbar);
  imaSplitter->addWidget(listImages);
  imaSplitter->addWidget(dateSplitter);

  
  path_toolbar = new QToolBar("path toolbar", this);
  
  action = new QAction(QIcon(":/icons/list-add.png"), "Nueva trayectoria", this);
  connect(action, SIGNAL(triggered()), this, SLOT(addPath()));
  path_toolbar->addAction(action);
	
  drawpathAction = new QAction(QIcon(":/icons/airport2.png"), "Ver trayectorias", this);
  drawpathAction->setCheckable(true);
  drawpathAction->setChecked(true);
  connect(drawpathAction, SIGNAL(triggered()), this, SLOT(drawPath()));
  path_toolbar->addAction(drawpathAction);
	
  drawArrowsAction = new QAction(QIcon(":/icons/go-up.png"), "Dibujar flecha", this);
  drawArrowsAction->setCheckable(true);
  connect(drawArrowsAction, SIGNAL(triggered()), this, SLOT(drawArrows()));
  path_toolbar->addAction(drawArrowsAction);
	
  action = new QAction(QIcon(":/icons/list-remove.png"), "Eliminar trayectoria", this);
  connect(action, SIGNAL(triggered()), this, SLOT(removePath()));
  path_toolbar->addAction(action);

  drawHourIconsAction = new QAction(QIcon(":/icons/clock.png"), "Dibujar iconos horarios", this);
  drawHourIconsAction->setCheckable(true);
  connect(drawHourIconsAction, SIGNAL(triggered()), this, SLOT(drawHourIcons()));
  path_toolbar->addAction(drawHourIconsAction);
	
  QPixmap pathcolorpixmap(32,32);
  pathcolorpixmap.fill(Path::defaultColor);
  pathColorAction = new QAction(QIcon(pathcolorpixmap), "Cambiar color de trayectoria", this);
  connect(pathColorAction, SIGNAL(triggered()), this, SLOT(setSelectedColor()));
  path_toolbar->addAction(pathColorAction);
	
  drawLabelsAction = new QAction(QIcon(":/icons/format-text-bold.png"), "Ver etiquetas", this);
  drawLabelsAction->setCheckable(true);
  connect(drawLabelsAction, SIGNAL(triggered()), this, SLOT(drawLabels()));
  path_toolbar->addAction(drawLabelsAction);
	
  spinLabels = new QSpinBox(this);
  spinLabels->setRange(0, 100);
  spinLabels->setValue(1);
  connect(spinLabels, SIGNAL(valueChanged(int)), this, SLOT(spaceLabels(int)));
  path_toolbar->addWidget(spinLabels);
  
  action_year = new QAction("Y", this);
  action_year->setCheckable(true);
  connect(action_year, SIGNAL(triggered()), this, SLOT(labelManualFormat()));
  action_mounth = new QAction("M", this);
  action_mounth->setCheckable(true);
  connect(action_mounth, SIGNAL(triggered()), this, SLOT(labelManualFormat()));
  action_day = new QAction("D", this);
  action_day->setCheckable(true);
  connect(action_day, SIGNAL(triggered()), this, SLOT(labelManualFormat()));
  action_hour = new QAction("h", this);
  action_hour->setCheckable(true);
  connect(action_hour, SIGNAL(triggered()), this, SLOT(labelManualFormat()));
  action_min = new QAction("m", this);
  action_min->setCheckable(true);
  connect(action_min, SIGNAL(triggered()), this, SLOT(labelManualFormat()));
  path_toolbar->addAction(action_year);	
  path_toolbar->addAction(action_mounth);	
  path_toolbar->addAction(action_day);	
  path_toolbar->addAction(action_hour);		
  path_toolbar->addAction(action_min);		
  
  path_toolbar->setEnabled(false);
	
  listPaths = new QListView(this);
  listPaths->setAlternatingRowColors(true);
  connect(listPaths, SIGNAL(clicked(QModelIndex)),
	  this, SLOT(pathClicked(const QModelIndex&)));
 
  QTabWidget *lowTab = new QTabWidget(imaSplitter);
  QSplitter *pathSplitter = new QSplitter(Qt::Vertical);
  //  pathSplitter->addWidget(new QLabel("Trayectorias"));
  pathSplitter->addWidget(path_toolbar);
  pathSplitter->addWidget(listPaths);
  lowTab->addTab(pathSplitter, "Trayectorias");

  coordtab = new CoordTab(this);
  lowTab->addTab(coordtab, "Coordenadas");
  
  imaSplitter->addWidget(lowTab);
  
  addWidget(view);
  addWidget(imaSplitter);
  
  return this;
 }


void Window::cargaImagenes()
{
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::ExistingFiles);
	dialog.setNameFilter(tr("Images (*.png *.jpg *.tif *gif)")); 
	if (dialog.exec()) {
		QStringList fileNames = dialog.selectedFiles();
		QStringList list = imagemodel->stringList();
		int idx = list.size();
		list << fileNames;
		imagemodel->setStringList(list);
		path_toolbar->setEnabled(true);
		selImage(idx);
	}
}

		
void Window::borraListaImagenes()
{
	if (imagemodel->rowCount() > 0) {
		QMessageBox msgBox;
		msgBox.setText(QObject::trUtf8("¿Desea eliminar la sesión?"));
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::No);
		int ret = msgBox.exec();
		if (ret==QMessageBox::Yes) 
			nuevaSesion();
	}
}	


void Window::acerca()
{
  QMessageBox::about(this, trUtf8(GIME_NAME_VERSION),
		     trUtf8("Sistema de rastreo de tormentas y análisis\nde imágenes meteorológicas.\nAutor: Alejandro Aguilar Sierra\nCentro de Ciencias de la Atmósfera, UNAM"));
}

#include "help.h"

void Window::help()
{
  QWidget *helpwindow = new QWidget;
  helpwindow->setAttribute(Qt::WA_DeleteOnClose);
  
  QTextEdit* help=new QTextEdit();
  help->setReadOnly(true);
  help->append(trUtf8(help_string));
  help->setMinimumWidth(600);
  help->setMinimumHeight(550);
  
  QPushButton *closeButton = new QPushButton(tr("&Close"));
  connect(closeButton, SIGNAL(clicked()), helpwindow, SLOT(close()));
  
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(help);
  layout->addWidget(closeButton);
  
  helpwindow->setLayout(layout);
  helpwindow->setWindowTitle(tr("GIME -  Ayuda"));
  helpwindow->show();
}

void Window::imageSelected(const QModelIndex &index) {
  int i = index.row();
  Path::image_idx = i;
  escena->updatePositions();
  if (view->setImage(imagemodel->stringList().at(i)))
    datetime->setDateTime(imagemodel->dateTimeAt(i));
  else if (QMessageBox::question(this, tr("Imagen no encontrada"),
				 QObject::trUtf8("¿Desea usar misma ruta que la sesión?"),
				 QMessageBox::Yes | QMessageBox::No)) {
    qDebug() << "Leyendo imagenes path ruta " << filename << endl;
    imagemodel->changeFilePath(QFileInfo(filename).canonicalPath());
  }
}


void Window::cambiaFecha()
{
  QModelIndex index = listImages->currentIndex();
  if (Path::image_idx >= 0 && index.column()==1) 
    imagemodel->setData(index, datetime->dateTime().toString("yyyy-MM-dd-hh:mm"), Qt::EditRole);
}


bool Window::asignaFecha(const QModelIndex &index) {
  if (index.column() > 0) {
    imagemodel->setData(index, datetime->dateTime().toString("yyyy-MM-dd-hh:mm"));
    return true;
  }
  return false;
}


void Window::pathClicked(const QModelIndex &index) {
	int i = index.row();	

	if (Path::selected == pathlist.at(i)) {
		Path::selected = NULL;
		listPaths->clearSelection();
	} else
		Path::selected = pathlist.at(i);
	view->selectPath();
}


void Window::selImage(int i)
{
	if (i >= 0 && i < imagemodel->rowCount()) {
		QModelIndex index = imagemodel->index(i, 0);
		listImages->setCurrentIndex(index);
		imageSelected(index);
	}
}


void Window::imageFirst()
{
	selImage(0);
}


void Window::imagePrev()
{
	QModelIndex index = listImages->currentIndex();
	int i = index.row();
	selImage(i-1);
}


void Window::imageNext()
{
	QModelIndex index = listImages->currentIndex();
	int i = index.row();
	selImage(i+1);
}

void Window::imageLast()
{
	selImage(imagemodel->rowCount()-1);
}


void Window::addPath()
{
	QStringList list = pathmodel->stringList();
	int id = list.size();
	Path *path = new Path(imagemodel->stringList().size());
	path->setName(QString("%1").arg(id+1,3,10,QChar('0')));
	pathlist << path;
	escena->addPath(path);
	list << path->getName();
	pathmodel->setStringList(list);
}


void Window::removePath()
{
	if (Path::selected != NULL) {
		QMessageBox msgBox;
		msgBox.setText(QObject::trUtf8("¿Desea eliminar la trayectoria seleccionada?"));
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::No);
		int ret = msgBox.exec();
		switch (ret) {
			case QMessageBox::No:
				printf("No\n");
			break;
			case QMessageBox::Yes:
				escena->removePath();
				pathlist.removeOne(Path::selected);
				QModelIndex index = listPaths->currentIndex();
				int i = index.row();
				pathmodel->removeRows(i,1);
				delete Path::selected;
			break;
		}
		Path::selected = NULL;
	}
}


void Window::setSelectedColor()
{
  QColor color = QColorDialog::getColor(Path::defaultColor);
  if (Path::selected!=NULL)
    Path::selected->pen.setColor(color);
  else
    Path::defaultColor = color;
		
  QPixmap pathcolorpixmap(32,32);
  pathcolorpixmap.fill(Path::defaultColor);
  pathColorAction->setIcon(QIcon(pathcolorpixmap));
  
  if (!escena->selectedItems().empty()) {
    QGraphicsSimpleTextItem *item = (QGraphicsSimpleTextItem*)escena->selectedItems()[0];
    if (item->parentItem() == 0) {
      item->setBrush(QBrush(color));
      // qDebug() << "Color text " << item->text() << " " << color << " vs " << item->brush().color() << endl;
    }
  }
}


void Window::drawPath()
{
  if (drawpathAction->isChecked())
    escena->showPaths(true);
  else
    escena->showPaths(false);	
  updateview();
}


void Window::drawLabels()
{
  if (drawLabelsAction->isChecked()) {
    if (Labels::texts.isEmpty()) {
      Labels::texts = imagemodel->dateStringList(imagemodel->dateSuggestedFormat(Labels::space));
      if (Labels::shown.isEmpty()) {
	for (int i=0; i < Labels::texts.size(); i++)
	  Labels::shown.append(true);
      }
      escena->updateTextLabels();
    }
    escena->showLabels(true);
  } else
    escena->showLabels(false);
  updateview();
}


void Window::toggleLabel()
{
  if (drawLabelsAction->isChecked()) {
    Labels::shown[Path::image_idx] =  !Labels::shown[Path::image_idx];
    escena->updateShownLabels();
    updateview();  
  } 
}


void Window::spaceLabels(int space)
{
  if (drawLabelsAction->isChecked()) {
    for (int i=0; i < Labels::texts.size(); i++) {
      bool is_shown = ((space==0 && i==0) || (space > 0 && (i % space==0)));
      Labels::shown[i] = is_shown;
    }
    escena->updateShownLabels();
    updateview();  
  }
}


void Window::labelManualFormat()
{
  QString format;

  if (action_year->isChecked())
    format += "yyyy";
  if (action_mounth->isChecked())
    format += "MM";
  if (action_day->isChecked())
    format += "dd";
  if (action_hour->isChecked())
    format += "hh";
  if (action_min->isChecked())
    format += "mm";

  if (format == "dd") {
    format = "d";
    int count = imagemodel->imagesPerDay();
    spinLabels->setSingleStep(count);
    spinLabels->setValue(0);
    qDebug() <<  "Images per day " << count << endl;
  } else 
    spinLabels->setSingleStep(1);
  
  Labels::texts = imagemodel->dateStringList(format);
  escena->updateTextLabels();
  updateview();  
}


bool Window::exportPathAsEPS()
{
	QString epsfile = QFileDialog::getSaveFileName(0, tr("Exportar EPS"),
        "", tr("EPS files (*.eps)"));
	
	QFile file(epsfile);
	if (!file.open(QIODevice::WriteOnly))
		return false;

	QTextStream out(&file);

	QString eps = "%!PS-Adobe-3.0 EPSF-3.0\n"
	"%%Pages 0\n"
	"%%BoundingBox: 0 0 ";
	
	eps += QString("%1 %2\n").arg(view->scene()->width()).arg(view->scene()->height());
	eps += "newpath\n";
	foreach (Path *path, pathlist)
		eps += path->toEPS();
	eps += "stroke\n";
	out << eps;
	
	return true;
}


bool Window::renderToJPEG()
{
	if (!view->fondo.isNull()) {
		QImage img(view->fondo.size(), QImage::Format_ARGB32_Premultiplied);
		QPainter painter(&img);
		painter.setRenderHint(QPainter::Antialiasing);
		painter.drawImage(view->fondo.rect(), view->fondo);
		QColor color(Qt::white);
		color.setAlphaF(0.25);
		painter.fillRect(view->fondo.rect(), QBrush(color));
		escena->showNodes(false);
		escena->render(&painter);
		painter.end();
		img.save("gime.jpg", "JPG");
		escena->showNodes(true);
		return true;
	}
	return false;
}


bool Window::renderToPNG()
{
	if (!view->fondo.isNull()) {	  
	  QString pngfile = QFileDialog::getSaveFileName(0, tr("Exportar a PNG transparente"),
							 "", tr("PNG files (*.png)"));
	
	  QImage img(view->fondo.size(), QImage::Format_ARGB32_Premultiplied);
	  img.fill(qRgba(0,0,0,0));
	  QPainter painter(&img);
	  //painter.setRenderHint(QPainter::Antialiasing);
	  //		painter.drawImage(view->fondo.rect(), view->fondo);
	  QColor color(Qt::white);
	  color.setAlphaF(0.25);
	  //painter.fillRect(view->fondo.rect(), QBrush(color));
	  painter.setBackground(QBrush(color));
	  escena->showNodes(false);
	  escena->render(&painter);
	  painter.end();
	  img.save(pngfile, "PNG");
	  escena->showNodes(true);
	  return true;
	}
	return false;
}


bool Window::exportAsAPNG()
{
  QString filename = QFileDialog::getSaveFileName(0, tr("Exportar a APNG"),
						  "", tr("APNG files (*.apng)"));
  if (exportToAPNG(filename, imagemodel->stringList(), escena)==0) 
    return true;
  else
    QMessageBox::warning(this, "Error", "Error o APNG no soportado.");
  
  return false;
}


bool Window::guardaTrayectoria()
{
  if (Path::selected == NULL) {
    QMessageBox::warning(this, "Error", "Selecciona primero una trayectoria");
    return false;
  } else if (georeferente == NULL) {
    QMessageBox::warning(this, "Error", "Define primero las coordenadas");
    return false;
  } else {
    qDebug() << "Path selected " << *Path::selected << endl;
    QString fn = Path::selected->getName()+".tray";
    QFile file(fn);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
      return false;
    QTextStream out(&file);
    QPolygon poly = Path::selected->toPolygon();
    foreach (QPoint p, poly) {
      float x, y, la, lo;
      x = p.x();
      y = p.y();
      georeferente->compute(x, y, la, lo);
      qDebug() << x << y << la << lo << endl;
      out << la << " " << lo << endl;
    }
    file.flush();
    QMessageBox::information(this, "Trayectoria guardada", fn);
  }
  return true;
}


bool Window::guardaSesionComo()
{
  filename = QFileDialog::getSaveFileName(0,
	     QObject::trUtf8("Guarda sesión"), "",
	     tr("GIME Sessions (*.gime)"));
  if (!filename.endsWith(".gime"))
    filename.append(".gime");
  setWindowTitle(tr("GIME - ")+filename);
  return guardaSesion();
}


bool  Window::guardaSesionActual()
{
  qDebug() << filename;
  return guardaSesion();
}


bool Window::guardaSesion()
{    
  if (filename=="sesion.gime" && QMessageBox::warning(this, tr("Guardar sesion"),
						      tr("¿Desea sobreescribir la sesion anonima?"),
						      QMessageBox::Save | QMessageBox::Cancel,
						      QMessageBox::Save)==QMessageBox::Cancel)
    return false;
	
  QFile file(filename);
  if (!file.open(QIODevice::WriteOnly))
    return false;

  QDataStream outStream(&file);
  outStream << (quint32)GIME_MAGIC;
  outStream << (quint32)GIME_DATA_VERSION;
  outStream.setVersion(QDataStream::Qt_4_7);

  outStream << imagemodel->fullStringList();

  outStream << pathlist.size();

  int i = 0;
  foreach (Path *path, pathlist) {
    path->setName(pathmodel->stringList().at(i));
    outStream << path;
    i++;
  }
  
  if (georeferente!=NULL) {
    outStream << 1;
    outStream << georeferente;
  } else 
    outStream << 0;
	
  if (texts_list.size() > 0) {
    outStream << texts_list.size();
    qDebug() << "Text list " << texts_list.size() << endl;	  
    foreach (QGraphicsSimpleTextItem *text_item, texts_list) {
      outStream << text_item->pos();
      outStream << text_item->text();
      outStream << text_item->font();
      outStream << text_item->brush().color();
    }
  } else 
    outStream << 0;
	
  return true;
}


bool Window::cargaSesionComo()
{
  filename = QFileDialog::getOpenFileName(this,
     QObject::trUtf8("Carga sesión"), "sesion.gime", tr("GIME Sessions (*.gime)"));
	
  return cargaSesion();;
}


bool Window::cargaSesion()
{
  quint32 magic, version;
  
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly))
    return false;

  setWindowTitle(tr("GIME - ")+filename);
  
  QDataStream inStream(&file);

  inStream >> magic;
  if (magic != GIME_MAGIC) {
    QMessageBox::warning(this, trUtf8("Cargar GIME"), trUtf8("Formato incorrecto: ") + QString::number(magic));
    return false;
  }
  
  inStream >> version;
  if (version != GIME_DATA_VERSION) {    
    QMessageBox::warning(this, trUtf8("Cargar GIME"), trUtf8("Versión incorrecta: ") + QString::number(version));
    return false;
  }
  
  inStream.setVersion(QDataStream::Qt_4_7);

  QStringList list;
  inStream >> list;
  imagemodel->setFullStringList(list);
	
  int psize;
  inStream >> psize;
  for (int i=0; i < psize; i++) {
    Path *path;
    inStream >> path;
    pathlist.append(path);
  }	
  QStringList plist;
  foreach (Path *path, pathlist) {
    escena->addPath(path);
    plist << path->getName();
    
  }
  pathmodel->setStringList(plist);
  
  int isgr;
  inStream >> isgr;
  if (isgr == 1) {
    inStream >> georeferente;
    coordtab->feedFromGeoreferencing();
  }
  
  int ntexts;	
  inStream >> ntexts;
  if (ntexts > 0) {
    for (int i=0; i < ntexts; i++) {
      QPointF pos;
      QString text;
      QFont font;
      QColor color;
      inStream >> pos;
      inStream >> text;
      inStream >> font;
      inStream >> color;
      addText(pos, text, font);
      
      QAbstractGraphicsShapeItem *p = (QAbstractGraphicsShapeItem*)texts_list.last();
      p->setBrush(QBrush(color));      
    }
  }	
  path_toolbar->setEnabled(true);
  selImage(0);
	
  return true;
}


void Window::keyPressEvent(QKeyEvent *event)
{
  switch (event->key()) {
  case Qt::Key_F:
    toggleLabel();
    break;
  case Qt::Key_Home:
    imageFirst();
    break;
  case Qt::Key_End:
    imageLast();
    break;
  case Qt::Key_Delete:
    if (QMessageBox::question(this, tr("Eliminar Imagen"),
			      QObject::trUtf8("¿Desea eliminar la imagen de la lista?"),
			      QMessageBox::Yes | QMessageBox::No)) {
      
      QModelIndex index = listImages->currentIndex();
      int i = index.row();      
      qDebug() << "Eliminando " << i << endl;
      imagemodel->removeRows(i,1);
    }
    break;
  default:
    QSplitter::keyPressEvent(event);
  }
}


void Window::drawArrows()
{
  bool show_arrows = drawArrowsAction->isChecked();

  if (Path::selected != NULL) {
    Path::selected->show_arrow = show_arrows;
    } else      
      foreach (Path *path, pathlist) 
	path->show_arrow = show_arrows;
  
  updateview(); 
}

void Window::drawHourIcons()
{
  bool show_icons = drawHourIconsAction->isChecked();
  
  if (Path::selected != NULL) {
    Path::selected->show_icon = show_icons;
  } else      
    foreach (Path *path, pathlist) 
      path->show_icon = show_icons;
  
  updateview(); 
}


void Window::cambiaLetra()
{
  bool ok, text_ok = false;
  QFont font = Labels::font;

  if (!escena->selectedItems().empty()) {
    QGraphicsSimpleTextItem *item = (QGraphicsSimpleTextItem*)escena->selectedItems()[0];
    qDebug() << "Typo " << item->type() << endl;
    if (item->parentItem() == 0) {
      font = item->font();
      text_ok = true;
    }
  }
      
  font = QFontDialog::getFont(&ok,font, this);
  
  if (ok) {
    if (text_ok) {
      text_font = font;
      QGraphicsSimpleTextItem *item = (QGraphicsSimpleTextItem*)escena->selectedItems()[0];
      item->setFont(text_font);
      qDebug() << "Family " << text_font.family() << endl;
    } else {
      Labels::font = font;
      escena->updateFontLabels();
    }
    updateview();	    
  } 
}


void Window::cambiaAnchoLinea()
{
  bool ok;
  int width = (Path::selected != NULL) ? Path::selected->pen.width(): 2;
  int i = QInputDialog::getInt(this, tr("Ancho de línea"),
                                 tr("Ancho:"), width, 0, 100, 1, &ok);
  if (ok) {
    if (Path::selected != NULL) {
      Path::selected->pen.setWidth(i);
      qDebug() << "Cambiando ancho " << width << endl;  
    } else      
      foreach (Path *path, pathlist) 
	path->pen.setWidth(i);
    updateview();	
  }
}


void Window::cambiaEstiloLinea()
{
  bool ok;
  QStringList items;
  items << tr("Solid") << tr("DashLine") << tr("DotLine") << tr("DashDotLine");
  int selected = (Path::selected != NULL) ? Path::selected->pen.style() - 1: 0;

  QString item = QInputDialog::getItem(this, tr("Estilo de línea"),
				tr("Estilo:"), items, selected, false, &ok);
  if (ok) {
    if (Path::selected != NULL) {
      Qt::PenStyle style = (Qt::PenStyle)(items.indexOf(item) + 1);
      Path::selected->pen.setStyle(style);
      qDebug() << "Cambiando estilo " << style << endl;  
    } /*else      
      foreach (Path *path, pathlist) 
      path->width = i;*/
    updateview();	
  }
}


void Window::sort_by_date()
{
  imagemodel->sort_by_date();
}


void Window::sort_by_name()
{
  imagemodel->sort_by_name();
}


void Window::agregaGriego() {
  text_font.setFamily("Standard Symbols L");
  agregaTexto();
}


void Window::agregaTexto() {
  bool ok;
  QString text = QInputDialog::getText(this, tr("Texto sobre la imagen"),
				       tr("Texto:"), QLineEdit::Normal, "", &ok);
  if (ok) {
    QPointF p(0,0);
    addText(p, text, text_font);
  }
}


void Window::updateview() {
    QWidget * viewport = view->viewport();
    viewport->update();	
}

