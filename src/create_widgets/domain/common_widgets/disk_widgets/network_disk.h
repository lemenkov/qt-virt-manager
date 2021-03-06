#ifndef NETWORK_DISK_H
#define NETWORK_DISK_H

#include "_disk.h"
#include "create_widgets/storage/_create_storage_widgets/_auth.h"

class Network_Disk : public _Disk
{
    Q_OBJECT
public:
    explicit Network_Disk(
            QWidget *parent = NULL,
            virConnectPtr conn = NULL);

private:
    QLabel          *protocolLabel, *sourceNameLabel,
                    *authLabel;
    QComboBox       *protocol;
    QLineEdit       *sourceName;
    _Storage_Auth   *auth;

public slots:
    QDomDocument     getDataDocument() const;
    void             setDataDescription(QString&);

private slots:
    void             protocolTypeChanged(int);
    void             protocolTypeChanged(QString);
    void             authUsageTypeChanged();
};

#endif // NETWORK_DISK_H
