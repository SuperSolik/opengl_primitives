#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->primitivesBox, SIGNAL(currentTextChanged(const QString&)), ui->openGLWidget, SLOT(set_primitive(const QString&)));
    connect(ui->alphaFuncBox, SIGNAL(currentTextChanged(const QString&)), ui->openGLWidget, SLOT(set_alphatest_func(const QString&)));
    connect(ui->alphaRefSlider, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(set_alphatest_ref(int)));
    connect(ui->blendBox_1, SIGNAL(currentTextChanged(const QString&)), ui->openGLWidget, SLOT(set_blend1(const QString&)));
    connect(ui->blendBox_2, SIGNAL(currentTextChanged(const QString&)), ui->openGLWidget, SLOT(set_blend2(const QString&)));
    connect(ui->xSlider, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(set_cutx(int)));
    connect(ui->ySlider, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(set_cuty(int)));
    connect(ui->wSlider, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(set_cutw(int)));
    connect(ui->hSlider, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(set_cuth(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

