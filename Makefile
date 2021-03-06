#############################################################################
# Makefile for building: gime
# Generated by qmake (2.01a) (Qt 4.8.7) on: Fri Jun 1 20:51:51 2018
# Project:  gime.pro
# Template: app
# Command: /usr/lib/x86_64-linux-gnu/qt4/bin/qmake -o Makefile gime.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/x86_64-linux-gnu/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		window.cpp \
		graphwidget.cpp \
		path.cpp \
		node.cpp \
		lines.cpp \
		tablemodel.cpp \
		labels.cpp \
		textdialog.cpp \
		gime_scene.cpp \
		coordtab.cpp \
		marker.cpp \
		exportAPNG.cpp \
		characterwidget.cpp moc_window.cpp \
		moc_graphwidget.cpp \
		moc_tablemodel.cpp \
		moc_gime_scene.cpp \
		moc_coordtab.cpp \
		moc_characterwidget.cpp \
		qrc_gime.cpp
OBJECTS       = main.o \
		window.o \
		graphwidget.o \
		path.o \
		node.o \
		lines.o \
		tablemodel.o \
		labels.o \
		textdialog.o \
		gime_scene.o \
		coordtab.o \
		marker.o \
		exportAPNG.o \
		characterwidget.o \
		moc_window.o \
		moc_graphwidget.o \
		moc_tablemodel.o \
		moc_gime_scene.o \
		moc_coordtab.o \
		moc_characterwidget.o \
		qrc_gime.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		gime.pro
QMAKE_TARGET  = gime
DESTDIR       = 
TARGET        = gime

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: gime.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile gime.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile gime.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/gime1.0.0 || $(MKDIR) .tmp/gime1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/gime1.0.0/ && $(COPY_FILE) --parents window.h graphwidget.h path.h node.h lines.h tablemodel.h labels.h textdialog.h gime_scene.h coordtab.h marker.h characterwidget.h .tmp/gime1.0.0/ && $(COPY_FILE) --parents gime.qrc .tmp/gime1.0.0/ && $(COPY_FILE) --parents main.cpp window.cpp graphwidget.cpp path.cpp node.cpp lines.cpp tablemodel.cpp labels.cpp textdialog.cpp gime_scene.cpp coordtab.cpp marker.cpp exportAPNG.cpp characterwidget.cpp .tmp/gime1.0.0/ && (cd `dirname .tmp/gime1.0.0` && $(TAR) gime1.0.0.tar gime1.0.0 && $(COMPRESS) gime1.0.0.tar) && $(MOVE) `dirname .tmp/gime1.0.0`/gime1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/gime1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_window.cpp moc_graphwidget.cpp moc_tablemodel.cpp moc_gime_scene.cpp moc_coordtab.cpp moc_characterwidget.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_window.cpp moc_graphwidget.cpp moc_tablemodel.cpp moc_gime_scene.cpp moc_coordtab.cpp moc_characterwidget.cpp
moc_window.cpp: tablemodel.h \
		window.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) window.h -o moc_window.cpp

moc_graphwidget.cpp: graphwidget.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) graphwidget.h -o moc_graphwidget.cpp

moc_tablemodel.cpp: tablemodel.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) tablemodel.h -o moc_tablemodel.cpp

moc_gime_scene.cpp: gime_scene.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) gime_scene.h -o moc_gime_scene.cpp

moc_coordtab.cpp: gime_scene.h \
		coordtab.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) coordtab.h -o moc_coordtab.cpp

moc_characterwidget.cpp: characterwidget.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) characterwidget.h -o moc_characterwidget.cpp

compiler_rcc_make_all: qrc_gime.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_gime.cpp
qrc_gime.cpp: gime.qrc \
		fonts/WeatherFont.ttf \
		icons/cca.png \
		icons/airport2.png \
		icons/eye.png \
		icons/list-remove.png \
		icons/cca128.png \
		icons/clock.png \
		icons/format-text-bold.png \
		icons/mapa.png \
		icons/document-open.png \
		icons/go-up.png \
		icons/go-first.png \
		icons/view-refresh.png \
		icons/go-next.png \
		icons/list-add.png \
		icons/go-previous.png \
		icons/go-last.png \
		icons/start-here.png \
		icons/folder-new.png
	/usr/lib/x86_64-linux-gnu/qt4/bin/rcc -name gime gime.qrc -o qrc_gime.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

####### Compile

main.o: main.cpp window.h \
		tablemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

window.o: window.cpp lines.h \
		labels.h \
		path.h \
		tablemodel.h \
		gime_scene.h \
		window.h \
		graphwidget.h \
		textdialog.h \
		coordtab.h \
		characterwidget.h \
		help.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o window.o window.cpp

graphwidget.o: graphwidget.cpp node.h \
		path.h \
		tablemodel.h \
		lines.h \
		labels.h \
		gime_scene.h \
		graphwidget.h \
		window.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o graphwidget.o graphwidget.cpp

path.o: path.cpp path.h \
		tablemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o path.o path.cpp

node.o: node.cpp node.h \
		path.h \
		tablemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o node.o node.cpp

lines.o: lines.cpp lines.h \
		path.h \
		tablemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lines.o lines.cpp

tablemodel.o: tablemodel.cpp tablemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tablemodel.o tablemodel.cpp

labels.o: labels.cpp labels.h \
		path.h \
		tablemodel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o labels.o labels.cpp

textdialog.o: textdialog.cpp textdialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o textdialog.o textdialog.cpp

gime_scene.o: gime_scene.cpp node.h \
		path.h \
		tablemodel.h \
		lines.h \
		labels.h \
		marker.h \
		gime_scene.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gime_scene.o gime_scene.cpp

coordtab.o: coordtab.cpp coordtab.h \
		gime_scene.h \
		marker.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o coordtab.o coordtab.cpp

marker.o: marker.cpp marker.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o marker.o marker.cpp

exportAPNG.o: exportAPNG.cpp path.h \
		tablemodel.h \
		gime_scene.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o exportAPNG.o exportAPNG.cpp

characterwidget.o: characterwidget.cpp characterwidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o characterwidget.o characterwidget.cpp

moc_window.o: moc_window.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_window.o moc_window.cpp

moc_graphwidget.o: moc_graphwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_graphwidget.o moc_graphwidget.cpp

moc_tablemodel.o: moc_tablemodel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_tablemodel.o moc_tablemodel.cpp

moc_gime_scene.o: moc_gime_scene.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_gime_scene.o moc_gime_scene.cpp

moc_coordtab.o: moc_coordtab.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_coordtab.o moc_coordtab.cpp

moc_characterwidget.o: moc_characterwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_characterwidget.o moc_characterwidget.cpp

qrc_gime.o: qrc_gime.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_gime.o qrc_gime.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

