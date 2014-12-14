#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->tableWidget->setRowCount(8);
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setVerticalHeaderLabels(QStringList() << "Track" << "Artist" << "Album" << "Year" << "Genre"
                                                           << "Bitrate" << "Frequency" << "Length");

    QIcon ico;
    ico.addFile("D:/___project/MyMusic/img/mp3_16.png", QSize(16, 16));
    ico.addFile("D:/___project/MyMusic/img/mp3_32.png", QSize(32, 32));
    setWindowIcon(ico);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("Audio Files (*.mp3);"));
    flag = false;
    if (fileName.isEmpty() == false) {
        myTag.Link(fileName.toStdString().c_str());

        ui->tableWidget->setItem(0, 0, new QTableWidgetItem(QString::fromLocal8Bit(ID3_GetTitle(&myTag))));
        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString::fromLocal8Bit(ID3_GetArtist(&myTag))));
        ui->tableWidget->setItem(0, 2, new QTableWidgetItem(QString::fromLocal8Bit(ID3_GetAlbum(&myTag))));
        ui->tableWidget->setItem(0, 3, new QTableWidgetItem(QString::fromLocal8Bit(ID3_GetYear(&myTag))));
        ui->tableWidget->setItem(0, 4, new QTableWidgetItem(QString::fromLocal8Bit(ID3_GetGenre(&myTag))));

        const Mp3_Headerinfo* mp3info;
        mp3info = myTag.GetMp3HeaderInfo();
        if (mp3info) {
            ui->tableWidget->setItem(0, 5, new QTableWidgetItem(QString::number(mp3info->bitrate/1000) + " KBps"));
            ui->tableWidget->setItem(0, 6, new QTableWidgetItem(QString::number(mp3info->frequency/1000) + " KHz"));
            ui->tableWidget->setItem(0, 7, new QTableWidgetItem(QString::number(mp3info->time/60) + " min " + QString::number(mp3info->time%60) + " s"));
        }
        flag = true;
    }

}



void MainWindow::on_tableWidget_cellChanged(int row, int column)
{  
    if (flag) {
        QTableWidgetItem* item = ui->tableWidget->item(row, column);

        switch (row) {
        case 0:
            ID3_AddTitle(&myTag, item->text().toStdString().c_str(), true);
            break;
        case 1:
            ID3_AddArtist(&myTag, item->text().toStdString().c_str(), true);
            break;
        case 2:
            ID3_AddAlbum(&myTag, item->text().toStdString().c_str(), true);
            break;
        case 3:
            ID3_AddYear(&myTag, item->text().toStdString().c_str(), true);
            break;
        case 4:
            ID3_AddGenre(&myTag, item->text().toStdString().c_str(), true);
            break;
        }

    }
}

void MainWindow::on_pushButton_2_clicked()
{
    myTag.Update();

    QMessageBox msgBox;
    msgBox.setText("Tags are successfully saved");
    msgBox.exec();
}
