#ifndef UNPACK_H
#define UNPACK_H

#include <QProcess>

class Unpack : public QObject
{
    Q_OBJECT
public:
    Unpack(int taskNum);
    void wolf(QString path);
signals:
    void onComplete();
private:
    int taskNum = 0;
    QProcess *process;
private slots:
    void onFinished(int exitCode, QProcess::ExitStatus exitStatus);
};

#endif // UNPACK_H
