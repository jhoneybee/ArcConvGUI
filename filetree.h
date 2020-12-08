#ifndef FILETREE_H
#define FILETREE_H

#include <QObject>
#include <QTreeView>
#include <QDir>
#include <QStandardItemModel>
#include <QColor>
#include "unpack.h"

class FileTree : public QObject
{
    Q_OBJECT
public:
    FileTree(QTreeView *treeView);
    // 重新
    void reload(QString path, QStandardItem *model = nullptr);
    QStandardItemModel *model = new QStandardItemModel();
private:
    QTreeView *treeView;
};

#endif // FILETREE_H
