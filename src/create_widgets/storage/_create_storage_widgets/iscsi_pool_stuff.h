#ifndef ISCSI_POOL_STUFF_H
#define ISCSI_POOL_STUFF_H

#include "_pool_stuff.h"

class iSCSI_Pool_Stuff : public _Pool_Stuff
{
    Q_OBJECT
public:
    explicit iSCSI_Pool_Stuff(QWidget *parent = NULL);

signals:

public slots:
    QDomDocument getStorageXMLDesc() const;
};

#endif // ISCSI_POOL_STUFF_H
