#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QActionGroup>

#include "DIALOGS/FILTER_SETTINGS/settingsdialog.h"
#include "DIALOGS/FILTER_SETTINGS/maskdialog.h"
#include "DIALOGS/NOISE_SETTINGS/noisedialog.h"
#include "imghandler.h"

#define W_IMG 400
#define H_IMG 300
#define X_OFFSET_IMG 5
#define Y_OFFSET_IMG 35
#define X_OFFSET_BTW_IMGS 2

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
	void SlotSetSKO(const double &t_sko);

private:
	void Init();
	// Put on mainscreen labels for images
	void SetLabels();
	// Creating exclusive group of actions, which defines mode of input image:
	// gray or color
	void SetModeActionGroup();
	void SetConnections();
	void EnableUI();
	void DisableUI();
	// Enable/disable functional UI elements (such as button for adding noise to img, etc.)
	void SetUIMode(const bool &t_mode);
	void SetImgOnOrigLbl(const QImage &t_origImg);
	void SetImgOnResultLbl(const QImage &t_resultImg);

private slots:
	// Slot for opening original image
	void on_actionOpen_triggered();
	// Slot for changing noise level
	void on_noiseLeveler_valueChanged(int value);
//	// Set type of original image: grayscale
//	void on_actionGrayscale_images_triggered();
//	// Set type of original image: color
//	void on_actionColor_images_triggered();
//	// Apply noise to result image
//	void on_NoiseButton_clicked();
//	// Start filtration
//	void on_FilterButton_clicked();
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
	QLabel m_origImgLbl;
	QLabel m_resultImgLbl;
	QActionGroup m_modeGroup;
};

#endif // MAINWINDOW_H
