#include "unpack.h"

Unpack::Unpack() {
}

void Unpack::wolf(QString path){
    QStringList params;
    params << path;
    QProcess::startDetached("WolfDec", params);
}
