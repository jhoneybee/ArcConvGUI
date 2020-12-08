#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "filetree.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    // 当前选择的目录
    QString directory;
    FileTree *fileTree;
private slots:
    void onMenuBarTriggeredMenu(QAction *action);
    void onFileSelected(QString path);

};
#endif // MAINWINDOW_H
