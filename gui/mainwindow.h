#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>

#include "gui/aggregfiltersettingsdialog.h"
#include "gui/maskdialog.h"
#include "gui/noisedialog.h"
#include "imghandler.h"

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
    void Init();
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
//	// Construct Mask Settings window
//	void on_actionMask_settings_triggered();
    // Slot for destroing Mask Settings dialog
    void SlotMaskSettingsClosed();
    // Construct Noise Settings window
    void on_actionNoise_settings_triggered();
    // Slot for destroing Noise Settings dialog
    void SlotNoiseSettingsClosed();
    void on_saveNoisedImgPB_clicked();
    void on_saveFilteredImgPB_clicked();

    // == DATA ==
private:
    Ui::MainWindow *ui;
    AggregFilterSettingsDialog m_aggregFilterSettings;
    MaskDialog *m_maskTable;
    NoiseDialog *m_noise;
    ImgHandler m_imgHandler;
};

#endif // MAINWINDOW_H
