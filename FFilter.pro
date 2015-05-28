QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += warn_on
QMAKE_CXXFLAGS_WARN_ON += -Werror -Wformat=2 -Wuninitialized -Winit-self \
        -Wmissing-include-dirs -Wswitch-enum -Wundef -Wpointer-arith \
        -Wdisabled-optimization -Wcast-align -Wcast-qual

TARGET = FFilter
TEMPLATE = app

SOURCES += main.cpp\
    image/imghandler.cpp \
    image/imgservice.cpp \
    filters/powerfilter.cpp \
    aggreg_operators/aggrophandler.cpp \
    aggreg_operators/defaultaggregoperator.cpp \
    aggreg_operators/minaggregoperator.cpp \
    aggreg_operators/maxaggregoperator.cpp \
    aggreg_operators/meanaggregoperator.cpp \
    aggreg_operators/geomeanaggregoperator.cpp \
    aggreg_operators/harmmeanaggregoperator.cpp \
    aggreg_operators/medaggregoperator.cpp \
    aggreg_operators/funcaggregoperator.cpp \
    masks/maskstructure.cpp \
    masks/activemask.cpp \
    noise/noisegenerator.cpp \
    noise/absrandnoise.cpp \
    noise/defaultnoise.cpp \
    noise/randnoise.cpp \
    noise/constnoise.cpp \
    gui/mainwindow.cpp \
    gui/maskdialog.cpp \
    gui/noisedialog.cpp \
    gui/aggregfiltersettingsdialog.cpp

HEADERS  += \
    image/imghandler.h \
    image/imgservice.h \
    filters/powerfilter.h \
    aggreg_operators/aggrophandler.h \
    aggreg_operators/defaultaggregoperator.h \
    aggreg_operators/minaggregoperator.h \
    aggreg_operators/maxaggregoperator.h \
    aggreg_operators/meanaggregoperator.h \
    aggreg_operators/geomeanaggregoperator.h \
    aggreg_operators/harmmeanaggregoperator.h \
    aggreg_operators/medaggregoperator.h \
    aggreg_operators/funcaggregoperator.h \
    common/common.h \
    masks/mask.h \
    masks/maskstructure.h \
    masks/activemask.h \
    noise/noisegenerator.h \
    noise/defaultnoise.h \
    noise/absrandnoise.h \
    noise/randnoise.h \
    noise/constnoise.h \
    gui/mainwindow.h \
    gui/maskdialog.h \
    gui/noisedialog.h \
    gui/aggregfiltersettingsdialog.h \
    aggreg_operators/aggreg_operators.h \
    noise/noise.h \
    image/image.h

FORMS    += \
    gui/mainwindow.ui \
    gui/maskdialog.ui \
    gui/noisedialog.ui \
    gui/aggregfiltersettingsdialog.ui
