#include "control_thread.h"

ControlThread::ControlThread(QObject *parent) :
    QThread(parent)
{
    qRegisterMetaType<Result>("Result");
    qRegisterMetaType<Actions>("Actions");
}
ControlThread::~ControlThread()
{
    if ( currWorkConnect!=NULL ) {
        // release the reference because no longer required
        virConnectClose(currWorkConnect);
        // for reject the multiple releasing the reference
        currWorkConnect = NULL;
    };
}

/* public slots */
bool ControlThread::setCurrentWorkConnect(virConnectPtr conn, uint i, QString _name)
{
    keep_alive = true;
    number = i;
    currConnName = _name;
    currWorkConnect = conn;
    // for new virConnect usage create the new virConnectRef[erence]
    if ( virConnectRef(currWorkConnect)<0 ) {
        currWorkConnect = NULL;
        sendConnErrors();
        keep_alive = false;
    };
    //qDebug()<<"net_thread"<<currWorkConnect;
    return keep_alive;
}
void ControlThread::execAction(Actions i, QStringList _str)
{
    return;
}
void ControlThread::stop() { keep_alive = false; }
void ControlThread::run()
{
    return;
}

void ControlThread::sendConnErrors()
{
    virtErrors = virConnGetLastError(currWorkConnect);
    if ( virtErrors!=NULL && virtErrors->code>0 ) {
        QString msg = QString("VirtError(%1) : %2").arg(virtErrors->code)
                .arg(QString().fromUtf8(virtErrors->message));
        emit errorMsg( msg );
        virResetError(virtErrors);
    } else sendGlobalErrors();
}
void ControlThread::sendGlobalErrors()
{
    virtErrors = virGetLastError();
    if ( virtErrors!=NULL && virtErrors->code>0 ) {
        QString msg = QString("VirtError(%1) : %2").arg(virtErrors->code)
                .arg(QString().fromUtf8(virtErrors->message));
        emit errorMsg( msg );
    };
    virResetLastError();
}
