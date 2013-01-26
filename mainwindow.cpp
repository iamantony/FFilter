/* === This file is part of FFilter ===
 *
 *	Copyright 2012, Antony Cherepanov <antony.cherepanov@gmail.com>
 *
 *	FFilter is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	FFilter is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with FFilter. If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_progrBar = NULL;
	m_settings = NULL;
	m_maskTable = NULL;

	Init();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::Init()
{
	SetLabels();
	SetModeActionGroup();
	FindGUIElements();

	SetConnections();

	DisableUI();
}

// Put on mainscreen labels for images
void MainWindow::SetLabels()
{
	m_origImgLbl.setParent(this);
	m_origImgLbl.setGeometry(X_OFFSET_IMG, Y_OFFSET_IMG, W_IMG, H_IMG);
	QPixmap origPm(W_IMG, H_IMG);
	origPm.fill(Qt::red);
	m_origImgLbl.setPixmap(origPm);
	m_origImgLbl.show();

	m_resultImgLbl.setParent(this);
	m_resultImgLbl.setGeometry(X_OFFSET_IMG + W_IMG + X_OFFSET_BTW_IMGS,
							   Y_OFFSET_IMG, W_IMG, H_IMG);

	QPixmap targPm(W_IMG, H_IMG);
	targPm.fill(Qt::blue);
	m_resultImgLbl.setPixmap(targPm);
	m_resultImgLbl.show();
}

// Creating exclusive group of actions, which defines mode of input image: gray or color
void MainWindow::SetModeActionGroup()
{
	m_modeGroup = new QActionGroup(this);
	m_modeGroup->setExclusive(true);

	QList<QAction *> listGray = this->findChildren<QAction *>("actionGrayscale_images");
	if ( true == listGray.isEmpty() )
	{
		qDebug() << "MainWindow::SetModeActionGroup(): Error - can't find window item";
		this->close();
	}
	else
	{
		m_modeGroup->addAction(listGray.at(0));
	}

	QList<QAction *> listColor = this->findChildren<QAction *>("actionColor_images");
	if ( true == listColor.isEmpty() )
	{
		qDebug() << "MainWindow::SetModeActionGroup(): Error - can't find window item";
		this->close();
	}
	else
	{
		m_modeGroup->addAction(listColor.at(0));
	}

	// By default working with gray images
	listGray.at(0)->setChecked(true);
}

// Find GUI elements, which could be enabled/disabled/changed
void MainWindow::FindGUIElements()
{
	QList<QProgressBar *> progrBarList = this->findChildren<QProgressBar *>("progressBar");
	if ( true == progrBarList.isEmpty() )
	{
		qDebug() << "MainWindow::FindGUIElements(): Error - can't find window item";
		this->close();
	}
	else
	{
		m_progrBar = progrBarList.at(0);
	}

	QList<QSlider *> sliderList = this->findChildren<QSlider *>("noiseLeveler");
	if ( true == sliderList.isEmpty() )
	{
		qDebug() << "MainWindow::FindGUIElements(): Error - can't find window item";
		this->close();
	}
	else
	{
		m_noiseLeveler = sliderList.at(0);
	}

	QList<QPushButton *> noiseBtnList = this->findChildren<QPushButton *>("NoiseButton");
	if ( true == noiseBtnList.isEmpty() )
	{
		qDebug() << "MainWindow::FindGUIElements(): Error - can't find window item";
		this->close();
	}
	else
	{
		m_noiseBtn = noiseBtnList.at(0);
	}

	QList<QPushButton *> filterBtnList = this->findChildren<QPushButton *>("FilterButton");
	if ( true == filterBtnList.isEmpty() )
	{
		qDebug() << "MainWindow::FindGUIElements(): Error - can't find window item";
		this->close();
	}
	else
	{
		m_filterBtn = filterBtnList.at(0);
	}

	QList<QLineEdit *> lineSKOList = this->findChildren<QLineEdit *>("lineSKO");
	if ( true == lineSKOList.isEmpty() )
	{
		qDebug() << "MainWindow::FindGUIElements(): Error - can't find window item";
		this->close();
	}
	else
	{
		m_lineSKO = lineSKOList.at(0);
	}

	QList<QLabel *> noiseLblList = this->findChildren<QLabel *>("labelNoisePrc");
	if ( true == noiseLblList.isEmpty() )
	{
		qDebug() << "MainWindow::FindGUIElements(): Error - can't find window item";
		this->close();
	}
	else
	{
		m_noiseLbl = noiseLblList.at(0);
	}
}

void MainWindow::SetConnections()
{
	// Connections for Progress bar on MainWindow
	connect(&m_imgHandler, SIGNAL(SignalUIProgrBarValue(int)),
			m_progrBar, SLOT(setValue(int)));

	connect(&m_imgHandler, SIGNAL(SignalUIResetProgrBar()), m_progrBar, SLOT(reset()));
	connect(this, SIGNAL(SignalResetProgrBar()), m_progrBar, SLOT(reset()));

	// Connection for LineEdit SKO on MainWindow
	connect(&m_imgHandler, SIGNAL(SignalUISetSKO(double)), this, SLOT(SlotSetSKO(double)));
}

void MainWindow::EnableUI()
{
	SetUIMode(true);
}

void MainWindow::DisableUI()
{
	SetUIMode(false);
}

// Enable/disable functional UI elements (such as button for adding noise to img, etc.)
void MainWindow::SetUIMode(const bool &t_mode)
{
	m_noiseLeveler->setEnabled(t_mode);
	m_noiseBtn->setEnabled(t_mode);
	m_filterBtn->setEnabled(t_mode);

	emit SignalResetProgrBar();
}

void MainWindow::SetImgOnOrigLbl(const QImage &t_origImg)
{
	if ( true == t_origImg.isNull() )
	{
		return;
	}

	QImage img = t_origImg.scaled(W_IMG, H_IMG, Qt::KeepAspectRatio);
	m_origImgLbl.setPixmap(QPixmap::fromImage(img));
}

void MainWindow::SetImgOnResultLbl(const QImage &t_resultImg)
{
	if ( true == t_resultImg.isNull() )
	{
		return;
	}

	QImage img = t_resultImg.scaled(W_IMG, H_IMG, Qt::KeepAspectRatio);
	m_resultImgLbl.setPixmap(QPixmap::fromImage(img));
}

// Set value to LineEdit SKO
void MainWindow::SlotSetSKO(const double &t_sko)
{
	QString strSKO = QString::number(t_sko);
	m_lineSKO->setText(strSKO);
}

// Slot for opening original image
void MainWindow::on_actionOpen_triggered()
{
	DisableUI();

	QString fName = QFileDialog::getOpenFileName(this, "Open target image...", QDir::currentPath(),
														  "IMG files (*.png *.jpg *.bmp)");

	if( true == fName.isEmpty())
	{
		// User didn't choose an image
		return;
	}

	// Save this image in memory
	QImage origImg(fName);
	m_imgHandler.SetOriginalImg(origImg);
	m_imgHandler.SetTargetImg(origImg);

	// Because it's the original image, we put it on both labels: original and result
	QImage newOrigImg = m_imgHandler.GetOriginalImg();
	QImage resultImg = m_imgHandler.GetTargetImg();

	SetImgOnOrigLbl(newOrigImg);
	SetImgOnResultLbl(resultImg);

	// Because images are same, SKO between them is ZERO
	SlotSetSKO(0);

	EnableUI();
}

// Private slot for changing noise level. Called by MainWindow
void MainWindow::on_noiseLeveler_valueChanged(int value)
{
	m_imgHandler.SetNoiseLevelPrc(value);

	QString strNoise = QString::number(value);
	strNoise.append("%");
	m_noiseLbl->setText(strNoise);
}

// Set type of original image: grayscale
void MainWindow::on_actionGrayscale_images_triggered()
{
	m_imgHandler.SetImgMode(ImageMode::GRAYSCALE);
}

// Set type of original image: color
void MainWindow::on_actionColor_images_triggered()
{
	// Because we don't have color image filtration functionality, we set grayscale filtration
	QList<QAction *> list = this->findChildren<QAction *>("actionGrayscale_images");
	if ( false == list.isEmpty() )
	{
		list.at(0)->setChecked(true);
		on_actionGrayscale_images_triggered();
	}

	// Just kidding
	QMessageBox::warning(this, "Sorry...", "This functionality is not accessable in free version",
						 QMessageBox::Ok, QMessageBox::NoButton);
}

// Apply noise to result image
void MainWindow::on_NoiseButton_clicked()
{
	DisableUI();

	QImage noisyImg = m_imgHandler.GetNoisyImg();
	SetImgOnResultLbl(noisyImg);
	m_imgHandler.GetImgsSKO();

	EnableUI();
}

// Start filtration
void MainWindow::on_FilterButton_clicked()
{
	DisableUI();

	// SKO calculated automatically!
	QImage filteredImg = m_imgHandler.PerfFiltration();
	SetImgOnResultLbl(filteredImg);

	EnableUI();
}

// Construct Settings window
void MainWindow::on_actionSettings_triggered()
{
	m_settings = new SettingsDialog(this);

	m_settings->SetCurrAggrOp(m_imgHandler.GetAggrOpType());
	m_settings->SetCurrAggrOpFunc(m_imgHandler.GetAggrOpFunc());
	m_settings->SetCurrAggrOpPower(m_imgHandler.GetAggrOpPower());

	connect(m_settings, SIGNAL(SignalAggrOpType(AggregOperatorType::AggrOpType)),
			&m_imgHandler, SLOT(SlotAggrOpTypeChanged(AggregOperatorType::AggrOpType)));

	connect(m_settings, SIGNAL(SignalAggrOpPower(double)),
			&m_imgHandler, SLOT(SlotAggrOpPowerChanged(double)));

	connect(m_settings, SIGNAL(SignalAggrOpFunc(AggregOperatorFunc::AggrOpFunc)),
			&m_imgHandler, SLOT(SlotAggrOpFuncChanged(AggregOperatorFunc::AggrOpFunc)));

	connect(m_settings, SIGNAL(accepted()), this, SLOT(SlotAggrOpSettingsClosed()));
	connect(m_settings, SIGNAL(rejected()), this, SLOT(SlotAggrOpSettingsClosed()));

	m_settings->show();
}

// Slot for destroing Settings for Aggreg Operators window on close
void MainWindow::SlotAggrOpSettingsClosed()
{
	delete m_settings;
}

// Construct Mask Settings window
void MainWindow::on_actionMask_settings_triggered()
{
	m_maskTable = new MaskDialog(this);

	// Mask transfer
	connect(m_maskTable, SIGNAL(SignalGetMask()), &m_imgHandler, SLOT(SlotTransmitMask()));
	connect(&m_imgHandler, SIGNAL(SignalSendMask(QMap<unsigned int, QList<Mask::MasksPixel> >)),
			m_maskTable, SLOT(SlotRecieveMask(QMap<unsigned int, QList<Mask::MasksPixel> >)));

	connect(m_maskTable, SIGNAL(SignalReturnMask(QMap<uint,QList<Mask::MasksPixel> >)),
			&m_imgHandler, SLOT(SlotRecieveMask(QMap<unsigned int, QList<Mask::MasksPixel> >)));

	// Show window when ready
	connect(m_maskTable, SIGNAL(SignalReadyToShow()), m_maskTable, SLOT(show()));

	// What we should do when user close Mask Settings Dialog
	connect(m_maskTable, SIGNAL(accepted()), this, SLOT(SlotMaskSettingsClosed()));
	connect(m_maskTable, SIGNAL(rejected()), this, SLOT(SlotMaskSettingsClosed()));

	m_maskTable->DefineSettings();
}

// Slot for destroing Mask Settings dialog
void MainWindow::SlotMaskSettingsClosed()
{
	delete m_maskTable;
}

// Construct Noise Settings window
void MainWindow::on_actionNoise_settings_triggered()
{
	m_noise = new NoiseDialog(this);
	m_noise->SetNoiseParams(m_imgHandler.GetNoiseType(), m_imgHandler.GetNoiseAmp());

	// Noise params transfer
	connect(m_noise, SIGNAL(SignalNewNoiseType(Noise::NoiseType)),
			&m_imgHandler, SLOT(SlotRecieveNoiseType(Noise::NoiseType)));

	connect(m_noise, SIGNAL(SignalNewNoiseAmp(int)), &m_imgHandler, SLOT(SlotRecieveNoiseAmp(int)));

	// What we should do when user close Noise Settings Dialog
	connect(m_noise, SIGNAL(accepted()), this, SLOT(SlotNoiseSettingsClosed()));
	connect(m_noise, SIGNAL(rejected()), this, SLOT(SlotNoiseSettingsClosed()));

	m_noise->show();
}

// Slot for destroing Noise Settings dialog
void MainWindow::SlotNoiseSettingsClosed()
{
	delete m_noise;
}
