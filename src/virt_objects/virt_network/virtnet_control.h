#ifndef VIRTNET_CONTROL_H
#define VIRTNET_CONTROL_H

#include "virt_objects/virt_entity_control.h"
#include "virtnet_model.h"
#include "virtnet_toolbar.h"
#include "virtnet_control_menu.h"
#include "create_widgets/network/create_virt_network.h"

class VirtNetControl : public VirtEntityControl
{
    Q_OBJECT
public:
    explicit VirtNetControl(QWidget *parent = NULL);
    ~VirtNetControl();

private:
    VirtNetModel        *virtNetModel = NULL;
    VirtNetToolBar      *toolBar;

public slots:
    bool                 getThreadState() const;
    void                 stopProcessing();
    bool                 setCurrentWorkConnect(virConnect*);
    void                 setListHeader(QString&);
    void                 resultReceiver(Result);

private slots:
    void                 changeDockVisibility();
    void                 entityClicked(const QPoint&);
    void                 entityDoubleClicked(const QModelIndex&);
    void                 execAction(const QStringList&);
    void                 newVirtEntityFromXML(const QStringList&);
};

#endif // VIRTNET_CONTROL_H
