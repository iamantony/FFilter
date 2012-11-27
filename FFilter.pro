#-------------------------------------------------
#
# Project created by QtCreator 2012-10-18T19:18:11
#
#-------------------------------------------------

QT       += core gui
CONFIG += warn_on
QMAKE_CXXFLAGS_WARN_ON += -Wall -Wextra -Werror

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FFilter
TEMPLATE = app


SOURCES += main.cpp\
		mainwindow.cpp \
	imghandler.cpp \
	imgservice.cpp \
	FILTERS/powerfilter.cpp \
	AGGR_OP/aggrophandler.cpp \
	AGGR_OP/defaultaggregoperator.cpp \
	AGGR_OP/minaggregoperator.cpp \
	AGGR_OP/maxaggregoperator.cpp \
	AGGR_OP/meanaggregoperator.cpp \
	AGGR_OP/geomeanaggregoperator.cpp \
	AGGR_OP/harmmeanaggregoperator.cpp \
	AGGR_OP/medaggregoperator.cpp \
	AGGR_OP/funcaggregoperator.cpp \
	DIALOGS/FILTER_SETTINGS/settingsdialog.cpp \
	MASKS/maskstructure.cpp \
	DIALOGS/FILTER_SETTINGS/maskdialog.cpp \
	DIALOGS/NOISE_SETTINGS/noisedialog.cpp \
	MASKS/activemask.cpp

HEADERS  += mainwindow.h \
	imghandler.h \
	imgservice.h \
	FILTERS/powerfilter.h \
	AGGR_OP/aggrophandler.h \
	AGGR_OP/defaultaggregoperator.h \
	AGGR_OP/minaggregoperator.h \
	AGGR_OP/maxaggregoperator.h \
	AGGR_OP/meanaggregoperator.h \
	AGGR_OP/geomeanaggregoperator.h \
	AGGR_OP/harmmeanaggregoperator.h \
	AGGR_OP/medaggregoperator.h \
	AGGR_OP/funcaggregoperator.h \
	DEFINES/common.h \
	DEFINES/enums.h \
	DEFINES/mask.h \
	DIALOGS/FILTER_SETTINGS/settingsdialog.h \
	MASKS/maskstructure.h \
	DIALOGS/FILTER_SETTINGS/maskdialog.h \
	DIALOGS/NOISE_SETTINGS/noisedialog.h \
	MASKS/activemask.h

FORMS    += mainwindow.ui \
	DIALOGS/FILTER_SETTINGS/maskdialog.ui \
	DIALOGS/NOISE_SETTINGS/noisedialog.ui \
	DIALOGS/FILTER_SETTINGS/settingsdialog.ui
