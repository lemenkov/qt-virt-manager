#ifndef MEMBALLOON_EDIT_H
#define MEMBALLOON_EDIT_H

#include "create_widgets/domain/common_widgets/memballoon.h"

class MemBalloon_Edit : public MemBalloon
{
    Q_OBJECT
public:
    explicit MemBalloon_Edit(
            QWidget *parent = 0,
            virConnectPtr conn = NULL);

signals:

public slots:
    void setDataDescription(QString&);
};

#endif // MEMBALLOON_EDIT_H
