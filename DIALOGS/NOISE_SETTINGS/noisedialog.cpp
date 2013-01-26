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

#include "noisedialog.h"
#include "ui_noisedialog.h"

NoiseDialog::NoiseDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NoiseDialog)
{
	ui->setupUi(this);

	m_noise = Noise::CONSTANT;
	m_amplitude = 0;
	m_noiseTypesMap.clear();
	m_posOfAbsRandNoise = ERROR;

	Init();
}

NoiseDialog::~NoiseDialog()
{
	delete ui;
}

void NoiseDialog::Init()
{
	this->setAttribute(Qt::WA_DeleteOnClose);

	FindGUIElements();
	SetNoiseTypesList();
	FindAbsRandNoise();
}

void NoiseDialog::FindGUIElements()
{
	QList<QComboBox *> cbList = this->findChildren<QComboBox *>("noiseTypeCB");
	if ( true == cbList.isEmpty() )
	{
		qDebug() << "NoiseDialog::FindGUIElements(): Error - can't find combobox with noise types!";
		emit rejected();
	}
	else
	{
		m_noiseTypeCB = cbList.at(0);
	}

	QList<QLineEdit *> lineList = this->findChildren<QLineEdit *>("ampLE");
	if ( true == lineList.isEmpty() )
	{
		qDebug() << "NoiseDialog::FindGUIElements(): Error - can't find line with amplitude value!";
		emit rejected();
	}
	else
	{
		m_ampLE = lineList.at(0);
	}
}

void NoiseDialog::SetNoiseTypesList()
{
	m_noiseTypesMap.insert(Noise::CONSTANT, STR_CONST);
	m_noiseTypesMap.insert(Noise::RANDOM, STR_RAND);
	m_noiseTypesMap.insert(Noise::ABS_RANDOM, STR_ABS_RAND);

	FillNoiseTypesCB();
}

void NoiseDialog::FillNoiseTypesCB()
{
	if ( true == m_noiseTypesMap.isEmpty() )
	{
		qDebug() << "NoiseDialog::FillNoiseTypesCB(): Error - map is empty";
		reject();
	}

	QList<QString> listOfTypes = m_noiseTypesMap.values();
	for (int type = 0; type < listOfTypes.size(); type++)
	{
		m_noiseTypeCB->addItem(listOfTypes.at(type));
	}
}

void NoiseDialog::FindAbsRandNoise()
{
	int position = m_noiseTypeCB->findText(STR_ABS_RAND);
	if ( ERROR == position )
	{
		qDebug() << "NoiseDialog::FindAbsRandNoise(): Error - can't find position of" << STR_ABS_RAND;
		reject();
	}
	else
	{
		m_posOfAbsRandNoise = position;
	}
}

void NoiseDialog::SetNoiseParams(Noise::NoiseType t_type, const int &t_ampl)
{
	m_noise = t_type;
	m_amplitude = t_ampl;

	SetNoiseType();
	SetNoiseAmp();
}

void NoiseDialog::SetNoiseType()
{
	QString typeName = m_noiseTypesMap.value(m_noise);
	int posOfType = m_noiseTypeCB->findText(typeName);
	if ( ERROR == posOfType )
	{
		qDebug() << "NoiseDialog::SetCurrentNoiseParams(): Error - can't find noise type:" << m_noise;
		reject();
	}
	else
	{
		m_noiseTypeCB->setCurrentIndex(posOfType);
	}
}

void NoiseDialog::SetNoiseAmp()
{
	m_ampLE->setText(QString::number(m_amplitude));
}

void NoiseDialog::on_noiseTypeCB_currentIndexChanged(int index)
{
	if ( m_posOfAbsRandNoise == index )
	{
		m_ampLE->setEnabled(false);
	}
	else
	{
		m_ampLE->setEnabled(true);
	}
}

void NoiseDialog::on_noiseTypeCB_currentIndexChanged(const QString &arg1)
{
	QList<QString> listOfTypes = m_noiseTypesMap.values();
	for (int type = 0; type < listOfTypes.size(); type++)
	{
		if ( arg1 == listOfTypes.at(type) )
		{
			m_noise = m_noiseTypesMap.key(listOfTypes.at(type));
			break;
		}
	}
}

void NoiseDialog::on_ampLE_editingFinished()
{
	bool transformed = false;
	int amplitude = m_ampLE->displayText().toInt(&transformed);
	if ( false == transformed )
	{
		// Set previous value
		SetNoiseAmp();
	}
	else
	{
		m_amplitude = amplitude;
	}
}

void NoiseDialog::on_okBtn_clicked()
{
	emit SignalNewNoiseType(m_noise);
	emit SignalNewNoiseAmp(m_amplitude);

	accept();
}

void NoiseDialog::on_cancelBtn_clicked()
{
	reject();
}

void NoiseDialog::accept()
{
	this->done(QDialog::Accepted);
}

void NoiseDialog::reject()
{
	this->done(QDialog::Rejected);
}
