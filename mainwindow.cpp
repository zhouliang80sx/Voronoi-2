#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}

void MainWindow::InitModel()
{
    if (nullptr != model)
    {
        delete model;
    }

    QRect rect = ui->graphicsView->rect();
    model = new Model(this, rect.width(), rect.height());
    model->Scene()->setSceneRect(rect);
    ui->graphicsView->setScene(model->Scene());

    model->SetNumOfPoints(ui->sbNumOfPoints->value());

    model->Init();
    model->Display(true);
}

void MainWindow::on_btnGenerate_clicked()
{
    InitModel();
}

void MainWindow::on_hsAnimationParameter_sliderMoved(int position)
{
    // Animation parameter from 0 to 1
    double ap = (double)position / ui->hsAnimationParameter->maximum();

    model->SetAnimationParameter(model->GetYFromAP(ap),
        false /* updateSlider */);

    model->Display();
}

void MainWindow::on_btnStart_clicked()
{
    model->SetAnimationToOngoing(false);

    if (model->AnimationOngoing())
    {
        model->Timer()->stop();
        model->SetAnimationOngoing(false);
        ui->btnStart->setText("Start");
    }
    else
    {
        model->Timer()->start();
        model->SetAnimationOngoing(true);
        ui->btnStart->setText("Stop");
    }
}

void MainWindow::on_btnPrevious_clicked()
{
    model->AnimateToPrevious();
}

void MainWindow::on_btnNext_clicked()
{
    model->AnimateToNext();
}
