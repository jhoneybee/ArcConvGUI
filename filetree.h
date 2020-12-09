#ifndef FILETREE_H
#define FILETREE_H

#include <QObject>
#include <QTreeView>
#include <QDir>
#include <QStandardItemModel>
#include <QColor>
#include <QMenu>
#include <QDesktopServices>
#include <QUrl>
#include <QVariant>

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
    QString path;
    QStandardItem *item;
    QTreeView *treeView;
    Unpack *pack;
    QStringList findWolf(QString path);
    void reloadTree(QString path, QStandardItem *item);
private slots:
    void onComplete();
    void slotCustomContextMenu(const QPoint &);
    void triggeredOpen();
};

#endif // FILETREE_H
