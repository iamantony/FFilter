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
 *	along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);

	Init();
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}

void SettingsDialog::Init()
{
	SetDefaults();
	FindGUIElements();
	SetAggrOpList();
	SetAggrOpFuncList();
	FindMeanAgOp();
	FindFunctionalAgOp();

	this->setAttribute(Qt::WA_DeleteOnClose);
}

void SettingsDialog::SetDefaults()
{
	m_currAggrOpType = AggregOperatorType::MIN;
	m_currAggrOpFunc = AggregOperatorFunc::EXP;
	m_currAggrOpPower = 1;

	m_posOfFuncAggrOp = ERROR;
	m_posOfMeanAggrOp = ERROR;
}

void SettingsDialog::FindGUIElements()
{
	QList<QComboBox *> agrrOpTypeList = this->findChildren<QComboBox *>("aggrOpCB");
	if ( true == agrrOpTypeList.isEmpty() )
	{
		qDebug() << "SettingsDialog::FindGUIElements(): Error - can't find list of arrgeg operators types";
		reject();
	}
	else
	{
		m_aggrOpTypes = agrrOpTypeList.at(0);
	}

	QList<QLineEdit *> powerLEList = this->findChildren<QLineEdit *>("powerLE");
	if ( true == powerLEList.isEmpty() )
	{
		qDebug() << "SettingsDialog::FindGUIElements(): Error - can't find line for power value";
		reject();
	}
	else
	{
		m_power = powerLEList.at(0);
	}

	QList<QComboBox *> aggrOpFuncList = this->findChildren<QComboBox *>("funcCB");
	if ( true == aggrOpFuncList.isEmpty() )
	{
		qDebug() << "SettingsDialog::FindGUIElements(): Error - can't find list of functions types";
		reject();
	}
	else
	{
		m_funcType = aggrOpFuncList.at(0);
	}
}

// Fill list of aggregation operators types
void SettingsDialog::SetAggrOpList()
{
	m_aggrOpTypesMap.insert(AggregOperatorType::MIN, STR_MIN);
	m_aggrOpTypesMap.insert(AggregOperatorType::MAX, STR_MAX);
	m_aggrOpTypesMap.insert(AggregOperatorType::MEAN, STR_MEAN);
	m_aggrOpTypesMap.insert(AggregOperatorType::GEOMETRIC_MEAN, STR_GEOM_MEAN);
	m_aggrOpTypesMap.insert(AggregOperatorType::HARMONC_MAEN, STR_HARM_MEAN);
	m_aggrOpTypesMap.insert(AggregOperatorType::MEDIAN, STR_MEDIAN);
	m_aggrOpTypesMap.insert(AggregOperatorType::FUNCTIONAL, STR_FUNC);

	FillAggrOpCB();
}

// Fill ComboBox for aggregation operators types
void SettingsDialog::FillAggrOpCB()
{
	if ( true == m_aggrOpTypesMap.isEmpty() )
	{
		qDebug() << "SettingsDialog::FillAggrOpCB(): Error - map is empty";
		reject();
	}

	QList<QString> listOfTypes = m_aggrOpTypesMap.values();
	for (int type = 0; type < listOfTypes.size(); type++)
	{
		m_aggrOpTypes->addItem(listOfTypes.at(type));
	}
}

// Fill list of functions for functional aggregation operator
void SettingsDialog::SetAggrOpFuncList()
{
	m_aggrOpFuncsMap.insert(AggregOperatorFunc::EXP, STR_EXP);
	m_aggrOpFuncsMap.insert(AggregOperatorFunc::LOG_NATURAL, STR_LN);

	FillAggrOpFuncsCB();
}

// Fill ComboBox for functions for functional aggregation operator
void SettingsDialog::FillAggrOpFuncsCB()
{
	if ( true == m_aggrOpFuncsMap.isEmpty() )
	{
		qDebug() << "FillAggrOpFuncsCB(): Error - map is empty";
		reject();
	}

	QList<QString> listOfFuncs = m_aggrOpFuncsMap.values();
	for (int func = 0; func < listOfFuncs.size(); func++)
	{
		m_funcType->addItem(listOfFuncs.at(func));
	}
}

// Find position of mean agrreg. operator in ComboBox
void SettingsDialog::FindMeanAgOp()
{
	int position = m_aggrOpTypes->findText(STR_MEAN);
	if ( ERROR == position )
	{
		qDebug() << "FindFunctionalAgOp(): Error - can't find position of" << STR_MEAN;
		reject();
	}
	else
	{
		m_posOfMeanAggrOp = position;
	}
}

// Find position of functional agrreg. operator in ComboBox
void SettingsDialog::FindFunctionalAgOp()
{
	int position = m_aggrOpTypes->findText(STR_FUNC);
	if ( ERROR == position )
	{
		qDebug() << "FindFunctionalAgOp(): Error - can't find position of" << STR_FUNC;
		reject();
	}
	else
	{
		m_posOfFuncAggrOp = position;
	}
}

void SettingsDialog::SetCurrAggrOp(AggregOperatorType::AggrOpType t_type)
{
	QString typeName = m_aggrOpTypesMap.value(t_type);
	int posOfType = m_aggrOpTypes->findText(typeName);
	if ( ERROR == posOfType )
	{
		qDebug() << "SetCurrAggrOp(): Error - can't find type of aggreg operator:" << t_type;
		reject();
	}
	else
	{
		m_currAggrOpType = t_type;
		m_aggrOpTypes->setCurrentIndex(posOfType);
	}
}

void SettingsDialog::SetCurrAggrOpPower(const double &t_power)
{
	m_currAggrOpPower = t_power;
	m_power->setText(QString::number(m_currAggrOpPower));
}

void SettingsDialog::SetCurrAggrOpFunc(AggregOperatorFunc::AggrOpFunc t_func)
{
	QString funcName = m_aggrOpFuncsMap.value(t_func);
	int posOfFunc = m_funcType->findText(funcName);
	if ( ERROR == posOfFunc )
	{
		qDebug() << "SetCurrAggrOpFunc(): Error - can't find type of function:" << t_func;
		reject();
	}
	else
	{
		m_currAggrOpFunc = t_func;
		m_funcType->setCurrentIndex(posOfFunc);
	}
}

// User changed type of aggreg. operator and we need to enable/disable some UI elements
void SettingsDialog::on_aggrOpCB_currentIndexChanged(int index)
{
	// User should have choise of function only when aggregation operator is functional
	if ( index == m_posOfFuncAggrOp )
	{
		m_funcType->setEnabled(true);
	}
	else
	{
		m_funcType->setEnabled(false);
	}

	// User can change power of function only when aggregation operator is power
	if ( index == m_posOfMeanAggrOp )
	{
		m_power->setEnabled(true);
	}
	else
	{
		m_power->setEnabled(false);
	}
}

// User changed type of aggreg. operator
void SettingsDialog::on_aggrOpCB_currentIndexChanged(const QString &arg1)
{
	QList<QString> listOfTypes = m_aggrOpTypesMap.values();
	for (int type = 0; type < listOfTypes.size(); type++)
	{
		if ( arg1 == listOfTypes.at(type) )
		{
			m_currAggrOpType = m_aggrOpTypesMap.key(listOfTypes.at(type));
			break;
		}
	}
}

// User changed type of function for functional aggreg. operator
void SettingsDialog::on_funcCB_currentIndexChanged(const QString &arg1)
{
	QList<QString> listOfFunc = m_aggrOpFuncsMap.values();

	for (int func = 0; func < listOfFunc.size(); func++)
	{
		if ( arg1 == listOfFunc.at(func) )
		{
			m_currAggrOpFunc = m_aggrOpFuncsMap.key(listOfFunc.at(func));
			break;
		}
	}
}

// User changed value of power
void SettingsDialog::on_powerLE_editingFinished()
{
	bool transformed = false;
	double power = m_power->displayText().toDouble(&transformed);
	if ( false == transformed )
	{
		m_power->setText(QString::number(m_currAggrOpPower));
	}
	else
	{
		m_currAggrOpPower = power;
	}
}

// User pressed "OK" button
void SettingsDialog::on_okBtn_clicked()
{
	emit SignalAggrOpType(m_currAggrOpType);
	emit SignalAggrOpPower(m_currAggrOpPower);
	emit SignalAggrOpFunc(m_currAggrOpFunc);

	accept();
}

// User pressed "Cancel" button
void SettingsDialog::on_cancelBtn_clicked()
{
	reject();
}

void SettingsDialog::accept()
{
	this->done(QDialog::Accepted);
}

void SettingsDialog::reject()
{
	this->done(QDialog::Rejected);
}
