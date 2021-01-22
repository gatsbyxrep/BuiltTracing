
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphalgs.h"
#include <QDebug>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::cout << std::endl;
    // Передаем на сцену полученные линии сети для отрисовки
    myGraphicView = new MyGraphicView(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this).toStdString();
    if(fileName == "")
    {
        QMessageBox msgBox(this);
        msgBox.setText("File hasn't been selected");
        msgBox.exec();
        return;
    }
    auto loadedData = DataLoader::loadFromFile(fileName);
    BuiltTracing builtTracing(loadedData.startPoint, loadedData.endPoint, loadedData.barriers);
    auto distanceMatrix = builtTracing.getWeightedGraph();
    std::vector<int> restoredPath;
    // Расчет минимального пути от начальной до конечной точки с помощью алгоритма Дейкстры
    auto minPath =  GraphAlgs::dijkstra(distanceMatrix,
                                        distanceMatrix.getVertexesCount() - 2,
                                        distanceMatrix.getVertexesCount() - 1,
                                        restoredPath).back();
    ui->textBrowser->append("Path:");
    for(auto vertex : restoredPath)
        ui->textBrowser->append(QString::number(vertex));
    ui->textBrowser->append("Min path:");
     ui->textBrowser->append(QString::number(minPath));
    myGraphicView->setBarriersLines(builtTracing.getBarriersLines());
    myGraphicView->setPath(restoredPath);
    myGraphicView->setWeightedGraphVisual(distanceMatrix);
    myGraphicView->update();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    myGraphicView->setXScale(value);
    myGraphicView->update();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    myGraphicView->setYScale(value);
    myGraphicView->update();
}
