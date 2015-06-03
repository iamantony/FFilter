#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
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
            SIGNAL(SignalAggrOpType(AggregOperator::Type::Type)),
            &m_imgHandler,
            SLOT(SlotAggrOpTypeChanged(AggregOperator::Type::Type)));

    connect(&m_aggregFilterSettings, SIGNAL(SignalAggrOpPower(double)),
            &m_imgHandler, SLOT(SlotAggrOpPowerChanged(double)));

    connect(&m_aggregFilterSettings,
            SIGNAL(SignalAggrOpFunc(AggregOperator::Func::Type)),
            &m_imgHandler,
            SLOT(SlotAggrOpFuncChanged(AggregOperator::Func::Type)));

    // Noise settings dialog connections
    connect(&m_noiseSettings, SIGNAL(SignalNoiseType(Noise::Type)),
            &m_imgHandler, SLOT(SlotRecieveNoiseType(Noise::Type)));

    connect(&m_noiseSettings, SIGNAL(SignalNoiseAmplitude(int)),
            &m_imgHandler, SLOT(SlotRecieveNoiseAmp(int)));

    // Mask settings dialog connections

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

    SetResultImg( m_imgHandler.FilterTargetImg() );

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
    m_maskSettings.DefineSettings();
}

// TODO
void MainWindow::on_saveNoisedImgPB_clicked()
{

}

// TODO
void MainWindow::on_saveFilteredImgPB_clicked()
{

}
