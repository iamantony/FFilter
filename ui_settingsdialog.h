/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created: Tue 27. Nov 09:58:29 2012
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
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QLabel *aggrOpLbl;
    QComboBox *aggrOpCB;
    QLabel *powerLbl;
    QLineEdit *powerLE;
    QLabel *funcLbl;
    QComboBox *funcCB;
    QPushButton *cancelBtn;
    QPushButton *okBtn;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->resize(339, 137);
        SettingsDialog->setFocusPolicy(Qt::TabFocus);
        SettingsDialog->setModal(true);
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
        cancelBtn = new QPushButton(SettingsDialog);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setGeometry(QRect(250, 100, 75, 23));
        okBtn = new QPushButton(SettingsDialog);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setGeometry(QRect(170, 100, 75, 23));

        retranslateUi(SettingsDialog);

        aggrOpCB->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Settings", 0, QApplication::UnicodeUTF8));
        aggrOpLbl->setText(QApplication::translate("SettingsDialog", "Aggregation Operator type:", 0, QApplication::UnicodeUTF8));
        powerLbl->setText(QApplication::translate("SettingsDialog", "Power:", 0, QApplication::UnicodeUTF8));
        funcLbl->setText(QApplication::translate("SettingsDialog", "Function type:", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("SettingsDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("SettingsDialog", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
