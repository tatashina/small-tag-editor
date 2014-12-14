#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <id3/tag.h>
#include <id3/misc_support.h>
#include <QTableWidget>
#include <QString>
#include <QTableWidgetItem>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ID3_Tag myTag;
    bool flag = false;
private slots:
    void on_pushButton_clicked();

    void on_tableWidget_cellChanged(int row, int column);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
