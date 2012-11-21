#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QFileDialog>
#include <QLineEdit>
#include <QActionGroup>
#include <QProgressBar>
#include <QSlider>
#include <QPushButton>
#include <QDebug>
#include "DIALOGS/FILTER_SETTINGS/settingsdialog.h"
#include "imghandler.h"
#include "DEFINES/common.h"
#include "DEFINES/enums.h"

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

	// == DATA ==
private:
	SettingsDialog *m_settings;
	ImgHandler m_imgHandler;
	QLabel m_origImgLbl;
	QLabel m_resultImgLbl;
	QActionGroup *m_modeGroup;
	QProgressBar *m_progrBar;
	QSlider *m_noiseLeveler;
	QPushButton *m_noiseBtn;
	QPushButton *m_filterBtn;
	QLineEdit *m_lineSKO;
	QLabel *m_noiseLbl;

	// == METHODS ==
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	void Init();
	// Put on mainscreen labels for images
	void SetLabels();
	// Creating exclusive group of actions, which defines mode of input image: gray or color
	void SetModeActionGroup();
	// Find GUI elements, which could be enabled/disabled/changed
	void FindGUIElements();
	void SetConnections();
	void EnableUI();
	void DisableUI();
	// Enable/disable functional UI elements (such as button for adding noise to img, etc.)
	void SetUIMode(const bool &t_mode);
	void SetImgOnOrigLbl(const QImage &t_origImg);
	void SetImgOnResultLbl(const QImage &t_resultImg);

signals:
	void SignalResetProgrBar();

public slots:
	// Set value to LineEdit SKO
	void SlotSetSKO(const double &t_sko);

private slots:
	// Slot for opening original image
	void on_actionOpen_triggered();
	// Private slot for changing noise level. Called by MainWindow
	void on_noiseLeveler_valueChanged(int value);
	// Set type of original image: grayscale
	void on_actionGrayscale_images_triggered();
	// Set type of original image: color
	void on_actionColor_images_triggered();
	// Apply noise to result image
	void on_NoiseButton_clicked();
	// Start filtration
	void on_FilterButton_clicked();
	// Construct Settings window
	void on_actionSettings_triggered();
	// Slot for destroing Settings for Aggreg Operators window on close
	void SlotAggrOpSettingsClosed();

	void on_actionMask_settings_triggered();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
