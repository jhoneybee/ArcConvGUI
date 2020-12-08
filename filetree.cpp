#include "filetree.h"

FileTree::FileTree(QTreeView *treeView) {
    this->treeView = treeView;
    model->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("路径信息"));
}

// 重新填充数据
void FileTree::reload(QString path, QStandardItem *item) {
    QDir current(path);
    if (!current.exists()) return;
    current.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    current.setSorting(QDir::DirsFirst);
    QFileInfoList list = current.entryInfoList();
    for (int i=0; i < list.length(); i += 1) {
        QFileInfo fileInfo = list.at(i);
        QStandardItem *newItem = new QStandardItem(fileInfo.fileName());
        newItem->setData(fileInfo.path());
        newItem->setEditable(false);

        if (fileInfo.suffix() != "wolf") {
            if (item == NULL) {
                model->appendRow(newItem);
            }else {
                item->appendRow(newItem);
            }
        }

        QFile testWolfFile(fileInfo.path() + QDir::separator() + fileInfo.fileName() + ".wolf");
        if (fileInfo.isDir()) {
            if (testWolfFile.exists()) {
                newItem->setForeground(QColor(51,102,153));
            }
            reload(fileInfo.filePath(), newItem);
        }else {
            if (fileInfo.suffix() == "wolf") {
                Unpack::wolf(fileInfo.filePath());
            }
        }
    }
}


