#ifndef BIND_FSTYPE_H
#define BIND_FSTYPE_H

#include "_fstype.h"

class BindFsType : public _FsType
{
    Q_OBJECT
public:
    explicit BindFsType(
            QWidget *parent = NULL,
            QString _type = "lxc");

public slots:
    QDomDocument     getDataDocument() const;
    void             setDataDescription(QString&);
};

#endif // BIND_FSTYPE_H
