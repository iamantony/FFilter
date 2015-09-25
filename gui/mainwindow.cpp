#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SetConnections();
    EnableGUI(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Set up connections to GUI elements
void MainWindow::SetConnections()
{
    connect(&m_imgHandler, SIGNAL(SignalUIProgrBarValue(int)),
            ui->progressBar, SLOT(setValue(int)));

    connect(&m_imgHandler, SIGNAL(SignalUIResetProgrBar()),
            ui->progressBar, SLOT(reset()));

    connect(&m_imgHandler, SIGNAL(SignalUISetSD(double)),
            this, SLOT(SlotSetSD(double)));

    // Aggregation operators settings dialog connections
    connect(&m_aggregFilterSettings,
            SIGNAL(SignalAggrOpType(AggregOperator::Type)),
            &m_imgHandler,
            SLOT(SlotAggrOpTypeChanged(AggregOperator::Type)));

    connect(&m_aggregFilterSettings, SIGNAL(SignalAggrOpPower(double)),
            &m_imgHandler, SLOT(SlotAggrOpPowerChanged(double)));

    connect(&m_aggregFilterSettings,
            SIGNAL(SignalAggrOpFunc(AggregOperator::Func)),
            &m_imgHandler,
            SLOT(SlotAggrOpFuncChanged(AggregOperator::Func)));

    // Noise settings dialog connections
    connect(&m_noiseSettings, SIGNAL(SignalNoiseType(Noise::Type)),
            &m_imgHandler, SLOT(SlotRecieveNoiseType(Noise::Type)));

    connect(&m_noiseSettings, SIGNAL(SignalNoiseAmplitude(int)),
            &m_imgHandler, SLOT(SlotRecieveNoiseAmp(int)));
}

// Enable/disable functional GUI elements
// @input:
// - t_mode - desired mode og GUI elements. True if elements should be enabled,
// False otherwise
void MainWindow::EnableGUI(const bool& t_mode)
{
    ui->noiseLeveler->setEnabled(t_mode);
    ui->filterPB->setEnabled(t_mode);

    ui->progressBar->reset();
}

// Set original image on label
// @input:
// - t_origImg - valid image object
void MainWindow::SetOriginalImg(const QImage& t_origImg)
{
    if ( false == t_origImg.isNull() )
    {
        ui->originalImgLbl->setPixmap( QPixmap::fromImage(t_origImg) );
    }
}

// Set noised image on label
// @input:
// - t_noisedImg - valid image object
void MainWindow::SetNoisedImg(const QImage& t_noisedImg)
{
    if ( false == t_noisedImg.isNull() )
    {
        ui->noisedImgLbl->setPixmap( QPixmap::fromImage(t_noisedImg) );
    }
}

// Set filtered image on label
// @input:
// - t_resultImg - valid image object
void MainWindow::SetFilteredImg(const QImage& t_filteredImg)
{
    if ( false == t_filteredImg.isNull() )
    {
        ui->resultImgLbl->setPixmap( QPixmap::fromImage(t_filteredImg) );
    }
}

// Slot to set Standart Deviation value
// @input:
// - t_sko - calculated value of SD
void MainWindow::SlotSetSD(const double& t_sd)
{
    ui->sdLE->setText( QString::number(t_sd) );
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

    SetOriginalImg( m_imgHandler.GetOriginalImg() );
    SetNoisedImg( m_imgHandler.GetFilteredImg() );
    SetFilteredImg( m_imgHandler.GetFilteredImg() );

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
    SetNoisedImg( m_imgHandler.GetNoisyImg() );
}

// Start filtration
void MainWindow::on_filterPB_clicked()
{
    EnableGUI(false);

    SetFilteredImg( m_imgHandler.FilterTargetImg() );

    EnableGUI(true);
}

// Show Agrreg Filter Settings dialog
void MainWindow::on_actionAggregFilterSettings_triggered()
{
    m_aggregFilterSettings.SetCurrAggrOpType( m_imgHandler.GetAggrOpType() );
    m_aggregFilterSettings.SetCurrAggrOpFunc( m_imgHandler.GetAggrOpFunc() );
    m_aggregFilterSettings.SetCurrAggrOpPower( m_imgHandler.GetAggrOpPower() );

    m_aggregFilterSettings.exec();
}

// Show Noise Settings dialog
void MainWindow::on_actionNoiseSettings_triggered()
{
    m_noiseSettings.SetNoiseParams(m_imgHandler.GetNoiseType(),
                                   m_imgHandler.GetNoiseAmp());

    m_noiseSettings.exec();
}

// Show Mask Settings dialog
void MainWindow::on_actionMaskFilterSettings_triggered()
{
    if ( m_maskSettings.isNull() )
    {
        m_maskSettings = QSharedPointer<MaskSettingsDialog>(
                             new MaskSettingsDialog(m_imgHandler.GetMask()));
    }

    m_maskSettings->exec();
}

void MainWindow::on_saveNoisedImgPB_clicked()
{
    QString imgName = QFileDialog::getSaveFileName(this,
                                    "Save noised image to...",
                                    QDir::currentPath(),
                                    "IMG files (*.png *.jpg *.jpeg *.bmp)");

    if ( imgName.isEmpty() )
    {
        return;
    }

    QImage noisedImg = m_imgHandler.GetNoisyImg();
    if ( false == noisedImg.save(imgName) )
    {
        QMessageBox::critical(this,
                              "Fail",
                              "Program failed to save noised image. Sorry.");
    }
}

void MainWindow::on_saveFilteredImgPB_clicked()
{
    QString imgName = QFileDialog::getSaveFileName(this,
                                    "Save filtered image to...",
                                    QDir::currentPath(),
                                    "IMG files (*.png *.jpg *.jpeg *.bmp)");

    if ( imgName.isEmpty() )
    {
        return;
    }

    QImage filteredImg = m_imgHandler.GetFilteredImg();
    if ( false == filteredImg.save(imgName) )
    {
        QMessageBox::critical(this,
                              "Fail",
                              "Program failed to save filtered image. Sorry.");
    }
}
