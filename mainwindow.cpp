#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->menuBar, SIGNAL(triggered(QAction*)),this, SLOT(onMenuBarTriggeredMenu(QAction*)));
    fileTree = new FileTree(ui->treeView);
}

MainWindow::~MainWindow() {
    delete ui;
}

// 选择当前路径
void MainWindow::onMenuBarTriggeredMenu(QAction *action) {
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    connect(&dialog, SIGNAL(fileSelected(QString)), this, SLOT(onFileSelected(QString)));
    dialog.exec();
}

void MainWindow::onFileSelected(QString path) {
    directory = path;
    fileTree->reload(path);
    ui->treeView->setModel(fileTree->model);
}
