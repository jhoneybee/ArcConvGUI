#include "filetree.h"

FileTree::FileTree(QTreeView *treeView) {
    this->treeView = treeView;
    treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(treeView,SIGNAL(customContextMenuRequested(const QPoint &)),this, SLOT(slotCustomContextMenu(const QPoint &)));
    model->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("路径信息"));
}

void FileTree::reload(QString path, QStandardItem *item) {
    this->path = path;
    this->item = item;
    QStringList wolfs = findWolf(path);
    pack = new Unpack(wolfs.length());
    connect(pack, SIGNAL(onComplete()), this, SLOT(onComplete()));
    for (int i=0; i<wolfs.length() ; i += 1) {
        pack->wolf(wolfs[i]);
    }
}

void FileTree::reloadTree(QString path, QStandardItem *item) {
    QDir current(path);
    if (!current.exists()) return;
    current.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    current.setSorting(QDir::DirsFirst);
    QFileInfoList list = current.entryInfoList();
    for (int i=0; i < list.length(); i += 1) {
        QFileInfo fileInfo = list.at(i);
        QStandardItem *newItem = new QStandardItem(fileInfo.fileName());

        newItem->setData(fileInfo.filePath(), Qt::UserRole);
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
            reloadTree(fileInfo.filePath(), newItem);
        }
    }
}

QStringList FileTree::findWolf(QString path){
    QStringList paths;
    QDir current(path);
    if (!current.exists()) return paths;
    current.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    current.setSorting(QDir::DirsFirst);
    QFileInfoList list = current.entryInfoList();
    for (int i=0; i < list.length(); i += 1) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.isDir()) {
            paths.append(findWolf(fileInfo.filePath()));
        }else if(fileInfo.suffix() == "wolf") {
            paths << fileInfo.filePath();
        }
    }
    return paths;
}

void FileTree::onComplete() {
    reloadTree(path, item);
}

void FileTree::slotCustomContextMenu(const QPoint &point) {
    QMenu *menu = new QMenu(treeView);
    QAction *showAction = new QAction(QString::fromLocal8Bit("查看"));
    menu->addAction(showAction);
    // connect(showAction, SIGNAL(triggered()), this, SLOT(triggered()));

    QAction *openAction=new QAction(QString::fromLocal8Bit("打开文件夹"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(triggeredOpen()));
    menu->addAction(openAction);
    menu->exec(treeView->mapToGlobal(point));
}

void FileTree::triggeredOpen() {
    QModelIndex mi = treeView->currentIndex();
    QString data = mi.data(Qt::UserRole).toString();
    QDesktopServices::openUrl(QUrl(data, QUrl::TolerantMode));
}

