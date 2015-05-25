QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += warn_on
QMAKE_CXXFLAGS_WARN_ON += -Werror -Wformat=2 -Wuninitialized -Winit-self \
		-Wmissing-include-dirs -Wswitch-enum -Wundef -Wpointer-arith \
		-Wdisabled-optimization -Wcast-align -Wcast-qual

TARGET = FFilter
TEMPLATE = app

SOURCES += main.cpp\
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
	MASKS/maskstructure.cpp \
	MASKS/activemask.cpp \
    NOISE/noisegenerator.cpp \
    NOISE/absrandnoise.cpp \
    NOISE/defaultnoise.cpp \
    NOISE/randnoise.cpp \
    NOISE/constnoise.cpp \
    gui/mainwindow.cpp \
    gui/maskdialog.cpp \
    gui/noisedialog.cpp \
    gui/settingsdialog.cpp

HEADERS  += \
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
	MASKS/maskstructure.h \
	MASKS/activemask.h \
    NOISE/noisegenerator.h \
    NOISE/defaultnoise.h \
    NOISE/absrandnoise.h \
    NOISE/randnoise.h \
    NOISE/constnoise.h \
    gui/mainwindow.h \
    gui/maskdialog.h \
    gui/noisedialog.h \
    gui/settingsdialog.h

FORMS    += \
    gui/mainwindow.ui \
    gui/maskdialog.ui \
    gui/noisedialog.ui \
    gui/settingsdialog.ui
