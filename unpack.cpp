#include "unpack.h"

Unpack::Unpack(int taskNum) {
    this->taskNum = taskNum;

}

void Unpack::wolf(QString path){
    QStringList params;
    params << path;
    process = new QProcess();
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onFinished(int, QProcess::ExitStatus)));
    process->start("WolfDec", params);
}

void Unpack::onFinished(int exitCode, QProcess::ExitStatus exitStatus){
    --taskNum;
    if (taskNum < 1) {
        emit onComplete();
    }
}
