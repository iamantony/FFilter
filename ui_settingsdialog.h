/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created: Tue 20. Nov 10:49:04 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *aggrOpLbl;
    QComboBox *aggrOpCB;
    QLabel *powerLbl;
    QLineEdit *powerLE;
    QLabel *funcLbl;
    QComboBox *funcCB;
    QPushButton *setWeightBtn;
    QLabel *label_2;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->resize(339, 176);
        SettingsDialog->setFocusPolicy(Qt::TabFocus);
        SettingsDialog->setModal(true);
        buttonBox = new QDialogButtonBox(SettingsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(60, 140, 271, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        aggrOpLbl = new QLabel(SettingsDialog);
        aggrOpLbl->setObjectName(QString::fromUtf8("aggrOpLbl"));
        aggrOpLbl->setGeometry(QRect(10, 10, 191, 20));
        aggrOpCB = new QComboBox(SettingsDialog);
        aggrOpCB->setObjectName(QString::fromUtf8("aggrOpCB"));
        aggrOpCB->setGeometry(QRect(220, 10, 111, 20));
        powerLbl = new QLabel(SettingsDialog);
        powerLbl->setObjectName(QString::fromUtf8("powerLbl"));
        powerLbl->setGeometry(QRect(10, 45, 46, 13));
        powerLE = new QLineEdit(SettingsDialog);
        powerLE->setObjectName(QString::fromUtf8("powerLE"));
        powerLE->setGeometry(QRect(220, 40, 111, 20));
        funcLbl = new QLabel(SettingsDialog);
        funcLbl->setObjectName(QString::fromUtf8("funcLbl"));
        funcLbl->setGeometry(QRect(10, 75, 171, 16));
        funcCB = new QComboBox(SettingsDialog);
        funcCB->setObjectName(QString::fromUtf8("funcCB"));
        funcCB->setGeometry(QRect(220, 70, 111, 22));
        setWeightBtn = new QPushButton(SettingsDialog);
        setWeightBtn->setObjectName(QString::fromUtf8("setWeightBtn"));
        setWeightBtn->setGeometry(QRect(240, 100, 91, 23));
        label_2 = new QLabel(SettingsDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 105, 141, 16));

        retranslateUi(SettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingsDialog, SLOT(reject()));

        aggrOpCB->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Settings", 0, QApplication::UnicodeUTF8));
        aggrOpLbl->setText(QApplication::translate("SettingsDialog", "Aggregation Operator type:", 0, QApplication::UnicodeUTF8));
        powerLbl->setText(QApplication::translate("SettingsDialog", "Power:", 0, QApplication::UnicodeUTF8));
        funcLbl->setText(QApplication::translate("SettingsDialog", "Function type:", 0, QApplication::UnicodeUTF8));
        setWeightBtn->setText(QApplication::translate("SettingsDialog", "Set weights", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SettingsDialog", "Set mask:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
