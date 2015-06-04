#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QSharedPointer>

#include "gui/aggregfiltersettingsdialog.h"
#include "gui/masksettingsdialog.h"
#include "gui/noisesettingsdialog.h"
#include "image/imghandler.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    // == METHODS ==
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    // Slot to set Standart Deviation value
    void SlotSetSD(const double &t_sko);

private:
    // Set up connections to GUI elements
    void SetConnections();
    // Enable/disable functional UI elements
    void EnableGUI(const bool &t_mode);
    // Set original image on label
    void SetOriginalImg(const QImage &t_origImg);
    // Set result (filtered) image on label
    void SetResultImg(const QImage &t_resultImg);

private slots:
    // Slot for opening original image
    void on_openImgPB_clicked();
    // Slot for changing noise level
    void on_noiseLeveler_valueChanged(int value);
    // Start filtration
    void on_filterPB_clicked();
    // Show Agrreg Filter Settings dialog
    void on_actionAggregFilterSettings_triggered();
    // Show Noise Settings dialog
    void on_actionNoiseSettings_triggered();
    // Show Mask Settings dialog
    void on_actionMaskFilterSettings_triggered();
    void on_saveNoisedImgPB_clicked();
    void on_saveFilteredImgPB_clicked();

    // == DATA ==
private:
    Ui::MainWindow *ui;
    ImgHandler m_imgHandler;
    AggregFilterSettingsDialog m_aggregFilterSettings;
    NoiseSettingsDialog m_noiseSettings;
    QSharedPointer<MaskSettingsDialog> m_maskSettings;
};

#endif // MAINWINDOW_H
