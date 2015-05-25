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

#ifndef NOISEDIALOG_H
#define NOISEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QMap>
#include <QDebug>
#include "DEFINES/common.h"
#include "DEFINES/enums.h"

#define STR_CONST "Constant"
#define STR_RAND "Random"
#define STR_ABS_RAND "Absolute Random"

namespace Ui {
	class NoiseDialog;
}

class NoiseDialog : public QDialog
{
	Q_OBJECT

	// == DATA ==
private:
	Ui::NoiseDialog *ui;
	QComboBox *m_noiseTypeCB;
	QLineEdit *m_ampLE;
	Noise::NoiseType m_noise;
	int m_amplitude;
	QMap<Noise::NoiseType, QString> m_noiseTypesMap;
	int m_posOfAbsRandNoise;

	// == METHODS ==
public:
	explicit NoiseDialog(QWidget *parent);
	~NoiseDialog();
	void SetNoiseParams(Noise::NoiseType t_type, const int &t_ampl);

private:
	void Init();
	void FindGUIElements();
	void SetNoiseTypesList();
	void FillNoiseTypesCB();
	void FindAbsRandNoise();
	void SetNoiseType();
	void SetNoiseAmp();

signals:
	void SignalNewNoiseType(Noise::NoiseType t_noise);
	void SignalNewNoiseAmp(int t_amp);

private slots:
	void on_noiseTypeCB_currentIndexChanged(int index);
	void on_noiseTypeCB_currentIndexChanged(const QString &arg1);
	void on_ampLE_editingFinished();
	void on_okBtn_clicked();
	void on_cancelBtn_clicked();
	virtual void accept();
	virtual void reject();


};

#endif // NOISEDIALOG_H
