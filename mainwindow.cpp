#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	m_progrBar = NULL;
	m_settings = NULL;

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
	if ( false == listGray.isEmpty() )
	{
		m_modeGroup->addAction(listGray.at(0));
	}

	QList<QAction *> listColor = this->findChildren<QAction *>("actionColor_images");
	if ( false == listColor.isEmpty() )
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
	if ( false == progrBarList.isEmpty() )
	{
		m_progrBar = progrBarList.at(0);
	}

	QList<QSlider *> sliderList = this->findChildren<QSlider *>("noiseLeveler");
	if ( false == sliderList.isEmpty() )
	{
		m_noiseLeveler = sliderList.at(0);
	}

	QList<QPushButton *> noiseBtnList = this->findChildren<QPushButton *>("NoiseButton");
	if ( false == noiseBtnList.isEmpty() )
	{
		m_noiseBtn = noiseBtnList.at(0);
	}

	QList<QPushButton *> filterBtnList = this->findChildren<QPushButton *>("FilterButton");
	if ( false == filterBtnList.isEmpty() )
	{
		m_filterBtn = filterBtnList.at(0);
	}

	QList<QLineEdit *> lineSKOList = this->findChildren<QLineEdit *>("lineSKO");
	if ( false == lineSKOList.isEmpty() )
	{
		m_lineSKO = lineSKOList.at(0);
	}

	QList<QLabel *> noiseLblList = this->findChildren<QLabel *>("labelNoisePrc");
	if ( false == noiseLblList.isEmpty() )
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

void MainWindow::on_actionMask_settings_triggered()
{

}
