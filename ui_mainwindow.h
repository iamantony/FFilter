/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue 27. Nov 09:58:29 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionAverage;
    QAction *actionMean;
    QAction *actionGrayscale_images;
    QAction *actionColor_images;
    QAction *actionSettings;
    QAction *actionMask_settings;
    QAction *actionNoise_settings;
    QWidget *centralWidget;
    QPushButton *FilterButton;
    QLabel *originalImg;
    QLabel *resultImg;
    QLineEdit *lineSKO;
    QLabel *labelSKO;
    QSlider *noiseLeveler;
    QLabel *labelNoisePrc;
    QLabel *labelNoise;
    QProgressBar *progressBar;
    QPushButton *NoiseButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuFilter;
    QMenu *menuMode;
    QMenu *menuNoise;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(812, 425);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(812, 425));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionAverage = new QAction(MainWindow);
        actionAverage->setObjectName(QString::fromUtf8("actionAverage"));
        actionAverage->setCheckable(true);
        actionAverage->setChecked(true);
        actionMean = new QAction(MainWindow);
        actionMean->setObjectName(QString::fromUtf8("actionMean"));
        actionMean->setCheckable(true);
        actionMean->setChecked(false);
        actionGrayscale_images = new QAction(MainWindow);
        actionGrayscale_images->setObjectName(QString::fromUtf8("actionGrayscale_images"));
        actionGrayscale_images->setCheckable(true);
        actionGrayscale_images->setChecked(true);
        actionColor_images = new QAction(MainWindow);
        actionColor_images->setObjectName(QString::fromUtf8("actionColor_images"));
        actionColor_images->setCheckable(true);
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionMask_settings = new QAction(MainWindow);
        actionMask_settings->setObjectName(QString::fromUtf8("actionMask_settings"));
        actionNoise_settings = new QAction(MainWindow);
        actionNoise_settings->setObjectName(QString::fromUtf8("actionNoise_settings"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        FilterButton = new QPushButton(centralWidget);
        FilterButton->setObjectName(QString::fromUtf8("FilterButton"));
        FilterButton->setEnabled(false);
        FilterButton->setGeometry(QRect(700, 320, 90, 25));
        FilterButton->setContextMenuPolicy(Qt::DefaultContextMenu);
        originalImg = new QLabel(centralWidget);
        originalImg->setObjectName(QString::fromUtf8("originalImg"));
        originalImg->setGeometry(QRect(5, 5, 400, 300));
        resultImg = new QLabel(centralWidget);
        resultImg->setObjectName(QString::fromUtf8("resultImg"));
        resultImg->setGeometry(QRect(401, 5, 400, 300));
        lineSKO = new QLineEdit(centralWidget);
        lineSKO->setObjectName(QString::fromUtf8("lineSKO"));
        lineSKO->setGeometry(QRect(490, 320, 91, 27));
        lineSKO->setReadOnly(true);
        labelSKO = new QLabel(centralWidget);
        labelSKO->setObjectName(QString::fromUtf8("labelSKO"));
        labelSKO->setGeometry(QRect(450, 325, 41, 17));
        noiseLeveler = new QSlider(centralWidget);
        noiseLeveler->setObjectName(QString::fromUtf8("noiseLeveler"));
        noiseLeveler->setEnabled(false);
        noiseLeveler->setGeometry(QRect(90, 320, 160, 29));
        noiseLeveler->setMaximum(100);
        noiseLeveler->setOrientation(Qt::Horizontal);
        noiseLeveler->setTickPosition(QSlider::TicksBelow);
        noiseLeveler->setTickInterval(10);
        labelNoisePrc = new QLabel(centralWidget);
        labelNoisePrc->setObjectName(QString::fromUtf8("labelNoisePrc"));
        labelNoisePrc->setGeometry(QRect(260, 325, 51, 17));
        labelNoise = new QLabel(centralWidget);
        labelNoise->setObjectName(QString::fromUtf8("labelNoise"));
        labelNoise->setGeometry(QRect(20, 325, 81, 17));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setEnabled(true);
        progressBar->setGeometry(QRect(20, 360, 780, 25));
        progressBar->setValue(0);
        NoiseButton = new QPushButton(centralWidget);
        NoiseButton->setObjectName(QString::fromUtf8("NoiseButton"));
        NoiseButton->setEnabled(false);
        NoiseButton->setGeometry(QRect(600, 320, 90, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 812, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFilter = new QMenu(menuBar);
        menuFilter->setObjectName(QString::fromUtf8("menuFilter"));
        menuMode = new QMenu(menuBar);
        menuMode->setObjectName(QString::fromUtf8("menuMode"));
        menuNoise = new QMenu(menuBar);
        menuNoise->setObjectName(QString::fromUtf8("menuNoise"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuNoise->menuAction());
        menuBar->addAction(menuFilter->menuAction());
        menuBar->addAction(menuMode->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionExit);
        menuFilter->addAction(actionSettings);
        menuFilter->addAction(actionMask_settings);
        menuMode->addAction(actionGrayscale_images);
        menuMode->addAction(actionColor_images);
        menuNoise->addAction(actionNoise_settings);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "FFilter", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open image", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionAverage->setText(QApplication::translate("MainWindow", "Averaging", 0, QApplication::UnicodeUTF8));
        actionMean->setText(QApplication::translate("MainWindow", "Mean-square", 0, QApplication::UnicodeUTF8));
        actionGrayscale_images->setText(QApplication::translate("MainWindow", "Grayscale images", 0, QApplication::UnicodeUTF8));
        actionColor_images->setText(QApplication::translate("MainWindow", "Color images", 0, QApplication::UnicodeUTF8));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings for aggreg filter", 0, QApplication::UnicodeUTF8));
        actionMask_settings->setText(QApplication::translate("MainWindow", "Mask settings", 0, QApplication::UnicodeUTF8));
        actionNoise_settings->setText(QApplication::translate("MainWindow", "Noise settings", 0, QApplication::UnicodeUTF8));
        FilterButton->setText(QApplication::translate("MainWindow", "Filter", 0, QApplication::UnicodeUTF8));
        originalImg->setText(QString());
        resultImg->setText(QString());
        labelSKO->setText(QApplication::translate("MainWindow", "SKO", 0, QApplication::UnicodeUTF8));
        labelNoisePrc->setText(QApplication::translate("MainWindow", "0%", 0, QApplication::UnicodeUTF8));
        labelNoise->setText(QApplication::translate("MainWindow", "Noise level", 0, QApplication::UnicodeUTF8));
        NoiseButton->setText(QApplication::translate("MainWindow", "Noise", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuFilter->setTitle(QApplication::translate("MainWindow", "Filter", 0, QApplication::UnicodeUTF8));
        menuMode->setTitle(QApplication::translate("MainWindow", "Mode", 0, QApplication::UnicodeUTF8));
        menuNoise->setTitle(QApplication::translate("MainWindow", "Noise", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
