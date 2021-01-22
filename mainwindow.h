#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mygraphicview.h"
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Обработка события нажатия на кнопку загрузки данных
    void on_pushButton_clicked();
    // Обработка события измненеия значения слайдера X
    void on_horizontalSlider_valueChanged(int value);
    // Обработка события измненеия значения слайдера Y
    void on_horizontalSlider_2_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    // Указатель на объект сцены для отрисовки
    MyGraphicView* myGraphicView;
};
#endif // MAINWINDOW_H



