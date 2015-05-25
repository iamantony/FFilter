#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QPixmap>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QProgressBar>
#include <QFileDialog>
#include <QDebug>

#include "DEFINES/common.h"
#include "DEFINES/enums.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    SetConnections();
    EnableGUI(false);
}

// Set up connections to GUI elements
void MainWindow::SetConnections()
{
    connect(&m_imgHandler, SIGNAL(SignalUIProgrBarValue(int)),
            ui->progressBar, SLOT(setValue(int)));

    connect(&m_imgHandler, SIGNAL(SignalUIResetProgrBar()),
            ui->progressBar, SLOT(reset()));

    connect(&m_imgHandler, SIGNAL(SignalUISetSKO(double)),
            this, SLOT(SlotSetSD(double)));
}

// Enable/disable functional UI elements
void MainWindow::EnableGUI(const bool &t_mode)
{
    ui->noiseLeveler->setEnabled(t_mode);
    ui->filterPB->setEnabled(t_mode);

    ui->progressBar->reset();
}

// Set original image on label
void MainWindow::SetOriginalImg(const QImage &t_origImg)
{
    if ( t_origImg.isNull() )
    {
        return;
    }

    ui->originalImgLbl->setPixmap( QPixmap::fromImage(t_origImg) );
}

// Set result (filtered) image on label
void MainWindow::SetResultImg(const QImage &t_resultImg)
{
    if ( t_resultImg.isNull() )
    {
        return;
    }

    ui->resultImgLbl->setPixmap( QPixmap::fromImage(t_resultImg) );
}

// Slot to set Standart Deviation value
void MainWindow::SlotSetSD(const double &t_sko)
{
    ui->sdLE->setText( QString::number(t_sko) );
}

// Slot for opening original image
void MainWindow::on_openImgPB_clicked()
{
    QString fName = QFileDialog::getOpenFileName(this,
                                       "Open image",
                                       QDir::currentPath(),
                                       "IMG files (*.png *.jpg *.jpeg *.bmp)");

    if( fName.isEmpty())
    {
        return;
    }

    QImage origImg(fName);
    m_imgHandler.SetOriginalImg(origImg);
    m_imgHandler.SetTargetImg(origImg);

    SetOriginalImg( m_imgHandler.GetOriginalImg() );
    SetResultImg( m_imgHandler.GetTargetImg() );

    // Set initial SD
    SlotSetSD(0.0);

    EnableGUI(true);
}

// Slot for changing noise level
void MainWindow::on_noiseLeveler_valueChanged(int value)
{
    QString strNoiseLvl = QString::number(value) + "%";
    ui->noisePrcLbl->setText(strNoiseLvl);

    m_imgHandler.SetNoiseLevelPrc(value);
    SetOriginalImg( m_imgHandler.GetNoisyImg() );
}

// Start filtration
void MainWindow::on_filterPB_clicked()
{
    EnableGUI(false);

    SetResultImg( m_imgHandler.PerfFiltration() );

    EnableGUI(true);
}

//// Construct Settings window
//void MainWindow::on_actionSettings_triggered()
//{
//	m_settings = new SettingsDialog(this);

//	m_settings->SetCurrAggrOp(m_imgHandler.GetAggrOpType());
//	m_settings->SetCurrAggrOpFunc(m_imgHandler.GetAggrOpFunc());
//	m_settings->SetCurrAggrOpPower(m_imgHandler.GetAggrOpPower());

//	connect(m_settings, SIGNAL(SignalAggrOpType(AggregOperatorType::AggrOpType)),
//			&m_imgHandler, SLOT(SlotAggrOpTypeChanged(AggregOperatorType::AggrOpType)));

//	connect(m_settings, SIGNAL(SignalAggrOpPower(double)),
//			&m_imgHandler, SLOT(SlotAggrOpPowerChanged(double)));

//	connect(m_settings, SIGNAL(SignalAggrOpFunc(AggregOperatorFunc::AggrOpFunc)),
//			&m_imgHandler, SLOT(SlotAggrOpFuncChanged(AggregOperatorFunc::AggrOpFunc)));

//	connect(m_settings, SIGNAL(accepted()), this, SLOT(SlotAggrOpSettingsClosed()));
//	connect(m_settings, SIGNAL(rejected()), this, SLOT(SlotAggrOpSettingsClosed()));

//	m_settings->show();
//}

// Slot for destroing Settings for Aggreg Operators window on close
void MainWindow::SlotAggrOpSettingsClosed()
{
    delete m_settings;
}

//// Construct Mask Settings window
//void MainWindow::on_actionMask_settings_triggered()
//{
//	m_maskTable = new MaskDialog(this);

//	// Mask transfer
//	connect(m_maskTable, SIGNAL(SignalGetMask()), &m_imgHandler, SLOT(SlotTransmitMask()));
//	connect(&m_imgHandler, SIGNAL(SignalSendMask(QMap<unsigned int, QList<Mask::MasksPixel> >)),
//			m_maskTable, SLOT(SlotRecieveMask(QMap<unsigned int, QList<Mask::MasksPixel> >)));

//	connect(m_maskTable, SIGNAL(SignalReturnMask(QMap<uint,QList<Mask::MasksPixel> >)),
//			&m_imgHandler, SLOT(SlotRecieveMask(QMap<unsigned int, QList<Mask::MasksPixel> >)));

//	// Show window when ready
//	connect(m_maskTable, SIGNAL(SignalReadyToShow()), m_maskTable, SLOT(show()));

//	// What we should do when user close Mask Settings Dialog
//	connect(m_maskTable, SIGNAL(accepted()), this, SLOT(SlotMaskSettingsClosed()));
//	connect(m_maskTable, SIGNAL(rejected()), this, SLOT(SlotMaskSettingsClosed()));

//	m_maskTable->DefineSettings();
//}

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
