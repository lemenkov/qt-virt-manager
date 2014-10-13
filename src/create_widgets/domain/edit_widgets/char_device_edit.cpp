#include "char_device_edit.h"

CharDevice_Edit::CharDevice_Edit(
        QWidget *parent,
        virConnectPtr conn,
        virDomainPtr domain,
        QString _tag) :
    CharDevice(parent, conn, domain, _tag)
{
    connect(devType, SIGNAL(currentIndexChanged(int)),
            this, SIGNAL(dataChanged()));
    for (uint i=0; i<charDevWdg->count(); i++) {
        connect(charDevWdg->widget(i), SIGNAL(dataChanged()),
                this, SLOT(stateChanged()));
    };
}

/* public slots */
void CharDevice_Edit::setDataDescription(QString &xmlDesc)
{
    //qDebug()<<xmlDesc;
    QDomDocument doc;
    doc.setContent(xmlDesc);
    QDomElement _device;
    _device = doc.firstChildElement("device")
            .firstChildElement(tag);
    QString _type = _device.attribute("type", "unix");
    int idx = devType->findText(_type, Qt::MatchEndsWith);
    devType->setCurrentIndex( (idx<0)? 0:idx );
    static_cast<_QWidget*>(charDevWdg->currentWidget())->setDataDescription(xmlDesc);
}