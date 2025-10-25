#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QIODevice>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);

    setWindowTitle("Notepad");

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::on_actionNew_triggered);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::on_actionOpen_triggered);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::on_actionSave_triggered);
    connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::on_actionSaveAs_triggered);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    if(ui->textEdit->document()->isModified() == true)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Unsaved Changes","Do you want to save change to ?",QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if(reply == QMessageBox::Save)
        {
            saveFile();
        }
        else if (reply == QMessageBox::Discard)
        {
         ui->textEdit->clear();
         currentFile.clear();
         setWindowTitle("Untitled - Notepad");
        }
        else if (reply == QMessageBox::Cancel)
        {
            return;
        }
    } else
    {
        ui->textEdit->clear();
        currentFile.clear();
        setWindowTitle("Untitled - Notepad");
    }
}

void MainWindow::on_actionOpen_triggered()
{
    if(ui->textEdit->document()->isModified() == true)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Unsaved Changes","Do you want to save the change?",QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if(reply == QMessageBox::Save)
        {
            saveFile();
        }
        else if (reply == QMessageBox::Cancel)
        {
            return;
        }
    }

    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt);;All Files (*)");

    if (fileName.isEmpty())
        return; //the user click Cancel

    //Read the file content
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString text = in.readAll();
    file.close();

    ui->textEdit->setPlainText(text);

    currentFile = fileName;
    setWindowTitle(QFileInfo(currentFile).fileName()+ " - Notepad");
    ui->textEdit->document()->setModified(false);

}

void MainWindow::on_actionSave_triggered()
{
    saveFile();
}

void MainWindow::on_actionSaveAs_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this ,"Save As","","Text Files (*.txt);;All Files (*)");
    if (fileName.isEmpty())
        return;
    currentFile = fileName;
    saveFile();
}

void MainWindow::on_actionExit_triggered()
{
    if(ui->textEdit->document()->isModified() == true)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Unsaved Changes","Do you want to save change before exit?",QMessageBox::Save | QMessageBox::Cancel | QMessageBox::Discard);
        if(reply == QMessageBox::Save)
        {
            saveFile();
            this->close();
        }
        else if (reply == QMessageBox::Discard)
        {
            this->close();
        }
        else if (reply == QMessageBox::Cancel)
        {
            return;
        }
    } else
        this->close();
}

void MainWindow::saveFile()
{
    QString fileName = currentFile;
    if(fileName.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(this ,"Save As","","Text Files (*.txt);;All Files (*)");
        if (fileName.isEmpty())
            return;
    }

        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&file);
        out << ui->textEdit->toPlainText();
        file.close();

        currentFile = fileName;
        setWindowTitle(QFileInfo(currentFile).fileName()+ " - Notepad");
        ui->textEdit->document()->setModified(false);
}


