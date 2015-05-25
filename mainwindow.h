#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>

#include "DIALOGS/FILTER_SETTINGS/settingsdialog.h"
#include "DIALOGS/FILTER_SETTINGS/maskdialog.h"
#include "DIALOGS/NOISE_SETTINGS/noisedialog.h"
#include "imghandler.h"

namespace Ui {
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
//	// Construct Settings window
//	void on_actionSettings_triggered();
    // Slot for destroing Settings for Aggreg Operators window on close
    void SlotAggrOpSettingsClosed();
//	// Construct Mask Settings window
//	void on_actionMask_settings_triggered();
    // Slot for destroing Mask Settings dialog
    void SlotMaskSettingsClosed();
    // Construct Noise Settings window
    void on_actionNoise_settings_triggered();
    // Slot for destroing Noise Settings dialog
    void SlotNoiseSettingsClosed();

    // == DATA ==
private:
    Ui::MainWindow *ui;
    SettingsDialog *m_settings;
    MaskDialog *m_maskTable;
    NoiseDialog *m_noise;
    ImgHandler m_imgHandler;
};

#endif // MAINWINDOW_H
