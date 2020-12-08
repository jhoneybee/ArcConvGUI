#ifndef UNPACK_H
#define UNPACK_H

#include <QProcess>

class Unpack : public QObject{
public:
    Unpack();
    void static wolf(QString path);
};

#endif // UNPACK_H
