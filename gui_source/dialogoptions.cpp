/* Copyright (c) 2019-2021 hors<horsicq@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "dialogoptions.h"
#include "ui_dialogoptions.h"

DialogOptions::DialogOptions(QWidget *pParent, XOptions *pOptions) :
    QDialog(pParent),
    ui(new Ui::DialogOptions)
{
    ui->setupUi(this);

    this->g_pOptions=pOptions;

    pOptions->setCheckBox(ui->checkBoxSaveLastDirectory,XOptions::ID_SAVELASTDIRECTORY);
    pOptions->setCheckBox(ui->checkBoxStayOnTop,XOptions::ID_STAYONTOP);
    pOptions->setCheckBox(ui->checkBoxSaveBackup,XOptions::ID_SAVEBACKUP);
    pOptions->setCheckBox(ui->checkBoxShowLogo,XOptions::ID_SHOWLOGO);
    pOptions->setComboBox(ui->comboBoxStyle,XOptions::ID_STYLE);
    pOptions->setComboBox(ui->comboBoxQss,XOptions::ID_QSS);
    pOptions->setComboBox(ui->comboBoxLanguage,XOptions::ID_LANG);
    pOptions->setLineEdit(ui->lineEditSearchSignatures,XOptions::ID_SEARCHSIGNATURESPATH);

#ifdef WIN32
    ui->checkBoxContext->setChecked(pOptions->checkContext(X_APPLICATIONDISPLAYNAME,"*"));
#else
    ui->checkBoxContext->hide();
#endif
}

DialogOptions::~DialogOptions()
{
    delete ui;
}

void DialogOptions::on_pushButtonOK_clicked()
{
    g_pOptions->getCheckBox(ui->checkBoxSaveLastDirectory,XOptions::ID_SAVELASTDIRECTORY);
    g_pOptions->getCheckBox(ui->checkBoxStayOnTop,XOptions::ID_STAYONTOP);
    g_pOptions->getCheckBox(ui->checkBoxSaveBackup,XOptions::ID_SAVEBACKUP);
    g_pOptions->getCheckBox(ui->checkBoxShowLogo,XOptions::ID_SHOWLOGO);
    g_pOptions->getComboBox(ui->comboBoxStyle,XOptions::ID_STYLE);
    g_pOptions->getComboBox(ui->comboBoxQss,XOptions::ID_QSS);
    g_pOptions->getComboBox(ui->comboBoxLanguage,XOptions::ID_LANG);
    g_pOptions->getLineEdit(ui->lineEditSearchSignatures,XOptions::ID_SEARCHSIGNATURESPATH);

#ifdef WIN32
    if(g_pOptions->checkContext(X_APPLICATIONDISPLAYNAME,"*")!=ui->checkBoxContext->isChecked())
    {
        if(ui->checkBoxContext->isChecked())
        {
            g_pOptions->registerContext(X_APPLICATIONDISPLAYNAME,"*",qApp->applicationFilePath());
        }
        else
        {
            g_pOptions->clearContext(X_APPLICATIONDISPLAYNAME,"*");
        }
    }
#endif

    if(g_pOptions->isRestartNeeded())
    {
        QMessageBox::information(this,tr("Information"),tr("Please restart the application"));
    }

    this->close();
}

void DialogOptions::on_pushButtonCancel_clicked()
{
    this->close();
}

void DialogOptions::on_toolButtonSearchSignatures_clicked()
{
    QString sText=ui->lineEditSearchSignatures->text();
    QString sInitDirectory=XBinary::convertPathName(sText);

    QString sDirectoryName=QFileDialog::getExistingDirectory(this,tr("Open directory")+QString("..."),sInitDirectory,QFileDialog::ShowDirsOnly);

    if(!sDirectoryName.isEmpty())
    {
        ui->lineEditSearchSignatures->setText(sDirectoryName);
    }
}
