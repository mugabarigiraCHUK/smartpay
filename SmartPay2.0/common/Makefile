#############################################################################
# Makefile for building: libcommon.a
# Generated by qmake (2.01a) (Qt 4.7.2) on: Sat Feb 11 15:40:33 2012
# Project:  common.pro
# Template: lib
# Command: /usr/bin/qmake -o Makefile common.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DMAKELIB -DQT_NO_DEBUG -DQT_SQL_LIB -DQT_XML_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -fPIC -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -fPIC -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtXml -I/usr/include/qt4/QtSql -I/usr/include/qt4 -I. -Itmp -Itmp
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
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

OBJECTS_DIR   = tmp/

####### Files

SOURCES       = data.cpp \
		parameter.cpp \
		dbtools.cpp \
		xsqlquery.cpp \
		quuencode.cpp \
		login.cpp \
		loginOptions.cpp \
		xvariant.cpp \
		languageoptions.cpp \
		parameterproperties.cpp \
		paramlistedit.cpp \
		parameteredit.cpp \
		parsexmlutils.cpp \
		querysource.cpp \
		reportpageoptions.cpp \
		memdbloader.cpp tmp/moc_login.cpp \
		tmp/moc_loginOptions.cpp \
		tmp/moc_languageoptions.cpp \
		tmp/moc_parameterproperties.cpp \
		tmp/moc_paramlistedit.cpp \
		tmp/moc_parameteredit.cpp \
		tmp/moc_querysource.cpp \
		tmp/moc_reportpageoptions.cpp \
		qrc_OpenRPTCommon.cpp
OBJECTS       = tmp/data.o \
		tmp/parameter.o \
		tmp/dbtools.o \
		tmp/xsqlquery.o \
		tmp/quuencode.o \
		tmp/login.o \
		tmp/loginOptions.o \
		tmp/xvariant.o \
		tmp/languageoptions.o \
		tmp/parameterproperties.o \
		tmp/paramlistedit.o \
		tmp/parameteredit.o \
		tmp/parsexmlutils.o \
		tmp/querysource.o \
		tmp/reportpageoptions.o \
		tmp/memdbloader.o \
		tmp/moc_login.o \
		tmp/moc_loginOptions.o \
		tmp/moc_languageoptions.o \
		tmp/moc_parameterproperties.o \
		tmp/moc_paramlistedit.o \
		tmp/moc_parameteredit.o \
		tmp/moc_querysource.o \
		tmp/moc_reportpageoptions.o \
		tmp/qrc_OpenRPTCommon.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		../global.pri \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/staticlib.prf \
		/usr/share/qt4/mkspecs/features/static.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		common.pro
QMAKE_TARGET  = common
DESTDIR       = ../lib/
TARGET        = libcommon.a

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

all: Makefile ../lib/$(TARGET) 

staticlib: ../lib/$(TARGET)

../lib/$(TARGET): tmp/ui_parameterproperties.h tmp/ui_paramlistedit.h tmp/ui_login.h tmp/ui_loginOptions.h tmp/ui_parameteredit.h $(OBJECTS) $(OBJCOMP) 
	@$(CHK_DIR_EXISTS) ../lib/ || $(MKDIR) ../lib/ 
	-$(DEL_FILE) $(TARGET)
	$(AR) $(TARGET) $(OBJECTS)
	-$(DEL_FILE) ../lib/$(TARGET)
	-$(MOVE) $(TARGET) ../lib/


Makefile: common.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		../global.pri \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/staticlib.prf \
		/usr/share/qt4/mkspecs/features/static.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/lib/libQtSql.prl \
		/usr/lib/libQtXml.prl \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -o Makefile common.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
../global.pri:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/staticlib.prf:
/usr/share/qt4/mkspecs/features/static.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/lib/libQtSql.prl:
/usr/lib/libQtXml.prl:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile common.pro

dist: 
	@$(CHK_DIR_EXISTS) tmp/common1.0.0 || $(MKDIR) tmp/common1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) tmp/common1.0.0/ && $(COPY_FILE) --parents data.h parameter.h dbtools.h xsqlquery.h quuencode.h login.h loginOptions.h xvariant.h languageoptions.h parameterproperties.h paramlistedit.h parameteredit.h parsexmlutils.h querysource.h reportpageoptions.h memdbloader.h tmp/common1.0.0/ && $(COPY_FILE) --parents ../OpenRPT/images/OpenRPTCommon.qrc tmp/common1.0.0/ && $(COPY_FILE) --parents data.cpp parameter.cpp dbtools.cpp xsqlquery.cpp quuencode.cpp login.cpp loginOptions.cpp xvariant.cpp languageoptions.cpp parameterproperties.cpp paramlistedit.cpp parameteredit.cpp parsexmlutils.cpp querysource.cpp reportpageoptions.cpp memdbloader.cpp tmp/common1.0.0/ && $(COPY_FILE) --parents parameterproperties.ui paramlistedit.ui login.ui loginOptions.ui parameteredit.ui tmp/common1.0.0/ && (cd `dirname tmp/common1.0.0` && $(TAR) common1.0.0.tar common1.0.0 && $(COMPRESS) common1.0.0.tar) && $(MOVE) `dirname tmp/common1.0.0`/common1.0.0.tar.gz . && $(DEL_FILE) -r tmp/common1.0.0


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

compiler_moc_header_make_all: tmp/moc_login.cpp tmp/moc_loginOptions.cpp tmp/moc_languageoptions.cpp tmp/moc_parameterproperties.cpp tmp/moc_paramlistedit.cpp tmp/moc_parameteredit.cpp tmp/moc_querysource.cpp tmp/moc_reportpageoptions.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) tmp/moc_login.cpp tmp/moc_loginOptions.cpp tmp/moc_languageoptions.cpp tmp/moc_parameterproperties.cpp tmp/moc_paramlistedit.cpp tmp/moc_parameteredit.cpp tmp/moc_querysource.cpp tmp/moc_reportpageoptions.cpp
tmp/moc_login.cpp: parameter.h \
		tmp/ui_login.h \
		login.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) login.h -o tmp/moc_login.cpp

tmp/moc_loginOptions.cpp: parameter.h \
		tmp/ui_loginOptions.h \
		loginOptions.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) loginOptions.h -o tmp/moc_loginOptions.cpp

tmp/moc_languageoptions.cpp: languageoptions.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) languageoptions.h -o tmp/moc_languageoptions.cpp

tmp/moc_parameterproperties.cpp: tmp/ui_parameterproperties.h \
		parameterproperties.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) parameterproperties.h -o tmp/moc_parameterproperties.cpp

tmp/moc_paramlistedit.cpp: tmp/ui_paramlistedit.h \
		paramlistedit.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) paramlistedit.h -o tmp/moc_paramlistedit.cpp

tmp/moc_parameteredit.cpp: parameter.h \
		tmp/ui_parameteredit.h \
		parameteredit.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) parameteredit.h -o tmp/moc_parameteredit.cpp

tmp/moc_querysource.cpp: querysource.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) querysource.h -o tmp/moc_querysource.cpp

tmp/moc_reportpageoptions.cpp: reportpageoptions.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) reportpageoptions.h -o tmp/moc_reportpageoptions.cpp

compiler_rcc_make_all: qrc_OpenRPTCommon.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_OpenRPTCommon.cpp
qrc_OpenRPTCommon.cpp: ../OpenRPT/images/OpenRPTCommon.qrc \
		../OpenRPT/images/openrpt_login.png \
		../OpenRPT/images/viewzoomin.png \
		../OpenRPT/images/viewzoomout.png
	/usr/bin/rcc -name OpenRPTCommon ../OpenRPT/images/OpenRPTCommon.qrc -o qrc_OpenRPTCommon.cpp

compiler_image_collection_make_all: tmp/qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) tmp/qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: tmp/ui_parameterproperties.h tmp/ui_paramlistedit.h tmp/ui_login.h tmp/ui_loginOptions.h tmp/ui_parameteredit.h
compiler_uic_clean:
	-$(DEL_FILE) tmp/ui_parameterproperties.h tmp/ui_paramlistedit.h tmp/ui_login.h tmp/ui_loginOptions.h tmp/ui_parameteredit.h
tmp/ui_parameterproperties.h: parameterproperties.ui
	/usr/bin/uic-qt4 parameterproperties.ui -o tmp/ui_parameterproperties.h

tmp/ui_paramlistedit.h: paramlistedit.ui
	/usr/bin/uic-qt4 paramlistedit.ui -o tmp/ui_paramlistedit.h

tmp/ui_login.h: login.ui
	/usr/bin/uic-qt4 login.ui -o tmp/ui_login.h

tmp/ui_loginOptions.h: loginOptions.ui
	/usr/bin/uic-qt4 loginOptions.ui -o tmp/ui_loginOptions.h

tmp/ui_parameteredit.h: parameteredit.ui
	/usr/bin/uic-qt4 parameteredit.ui -o tmp/ui_parameteredit.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

tmp/data.o: data.cpp data.h \
		languageoptions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/data.o data.cpp

tmp/parameter.o: parameter.cpp parameter.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/parameter.o parameter.cpp

tmp/dbtools.o: dbtools.cpp dbtools.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/dbtools.o dbtools.cpp

tmp/xsqlquery.o: xsqlquery.cpp xsqlquery.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/xsqlquery.o xsqlquery.cpp

tmp/quuencode.o: quuencode.cpp quuencode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/quuencode.o quuencode.cpp

tmp/login.o: login.cpp login.h \
		parameter.h \
		tmp/ui_login.h \
		dbtools.h \
		xsqlquery.h \
		loginOptions.h \
		tmp/ui_loginOptions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/login.o login.cpp

tmp/loginOptions.o: loginOptions.cpp loginOptions.h \
		parameter.h \
		tmp/ui_loginOptions.h \
		dbtools.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/loginOptions.o loginOptions.cpp

tmp/xvariant.o: xvariant.cpp xvariant.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/xvariant.o xvariant.cpp

tmp/languageoptions.o: languageoptions.cpp languageoptions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/languageoptions.o languageoptions.cpp

tmp/parameterproperties.o: parameterproperties.cpp parameterproperties.h \
		tmp/ui_parameterproperties.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/parameterproperties.o parameterproperties.cpp

tmp/paramlistedit.o: paramlistedit.cpp paramlistedit.h \
		tmp/ui_paramlistedit.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/paramlistedit.o paramlistedit.cpp

tmp/parameteredit.o: parameteredit.cpp parsexmlutils.h \
		querysource.h \
		reportpageoptions.h \
		xsqlquery.h \
		parameteredit.h \
		parameter.h \
		tmp/ui_parameteredit.h \
		paramlistedit.h \
		tmp/ui_paramlistedit.h \
		parameterproperties.h \
		tmp/ui_parameterproperties.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/parameteredit.o parameteredit.cpp

tmp/parsexmlutils.o: parsexmlutils.cpp parsexmlutils.h \
		querysource.h \
		reportpageoptions.h \
		memdbloader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/parsexmlutils.o parsexmlutils.cpp

tmp/querysource.o: querysource.cpp querysource.h \
		xsqlquery.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/querysource.o querysource.cpp

tmp/reportpageoptions.o: reportpageoptions.cpp reportpageoptions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/reportpageoptions.o reportpageoptions.cpp

tmp/memdbloader.o: memdbloader.cpp memdbloader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/memdbloader.o memdbloader.cpp

tmp/moc_login.o: tmp/moc_login.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_login.o tmp/moc_login.cpp

tmp/moc_loginOptions.o: tmp/moc_loginOptions.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_loginOptions.o tmp/moc_loginOptions.cpp

tmp/moc_languageoptions.o: tmp/moc_languageoptions.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_languageoptions.o tmp/moc_languageoptions.cpp

tmp/moc_parameterproperties.o: tmp/moc_parameterproperties.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_parameterproperties.o tmp/moc_parameterproperties.cpp

tmp/moc_paramlistedit.o: tmp/moc_paramlistedit.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_paramlistedit.o tmp/moc_paramlistedit.cpp

tmp/moc_parameteredit.o: tmp/moc_parameteredit.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_parameteredit.o tmp/moc_parameteredit.cpp

tmp/moc_querysource.o: tmp/moc_querysource.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_querysource.o tmp/moc_querysource.cpp

tmp/moc_reportpageoptions.o: tmp/moc_reportpageoptions.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_reportpageoptions.o tmp/moc_reportpageoptions.cpp

tmp/qrc_OpenRPTCommon.o: qrc_OpenRPTCommon.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/qrc_OpenRPTCommon.o qrc_OpenRPTCommon.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

