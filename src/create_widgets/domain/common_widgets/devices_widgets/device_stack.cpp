#include "device_stack.h"

#define DEV_LIST QStringList()\
    <<"Emulator"\
    <<"Disk"<<"FileSystem"<<"Controller"<<"Host Devices"\
    <<"USB Redirection"<<"SmartCard"<<"Network"\
    <<"Input"<<"Hub"<<"Graphics"<<"Video"\
    <<"Console"<<"Serial"<<"Parallel"<<"Channel"\
    <<"Sound"<<"WatchDog"<<"Memory Balloon"\
    <<"RNG"<<"TPM"<<"NVRAM"<<"Panic Notifier"
#define DEV_TYPE QStringList()\
    <<"emulator"\
    <<"disk"<<"filesystem"<<"controller"<<"hostdev"\
    <<"redirdev"<<"smartcard"<<"interface"\
    <<"input"<<"hub"<<"graphics"<<"video"\
    <<"console"<<"serial"<<"parallel"<<"channel"\
    <<"sound"<<"watchdog"<<"memballoon"\
    <<"rng"<<"tpm"<<"nvram"<<"panic"

#define QEMU_DEVICE_LIST QStringList()\
    <<"emulator"\
    <<"disk"<<"filesystem"<<"hostdev"\
    <<"redirdev"<<"smartcard"<<"interface"\
    <<"input"<<"hub"<<"graphics"<<"video"\
    <<"console"<<"serial"<<"parallel"<<"channel"\
    <<"sound"<<"watchdog"<<"memballoon"<<"rng"\
    <<"tpm"<<"nvram"<<"panic"

#define LXC_DEVICE_LIST QStringList()\
    <<"emulator"\
    <<"disk"<<"filesystem"<<"hostdev"\
    <<"smartcard"<<"interface"<<"input"\
    <<"hub"<<"graphics"<<"video"\
    <<"console"<<"serial"<<"parallel"<<"channel"\
    <<"sound"<<"rng"<<"nvram"

#define XEN_DEVICE_LIST QStringList()\
    <<"emulator"\
    <<"disk"<<"filesystem"<<"controller"<<"hostdev"\
    <<"smartcard"<<"interface"\
    <<"input"<<"hub"<<"graphics"<<"video"\
    <<"console"<<"serial"<<"parallel"<<"channel"\
    <<"sound"<<"memballoon"\
    <<"rng"<<"nvram"

#define VBOX_DEVICE_LIST QStringList()\
    <<"emulator"\
    <<"disk"<<"filesystem"<<"controller"<<"hostdev"\
    <<"smartcard"<<"interface"\
    <<"input"<<"hub"<<"graphics"<<"video"\
    <<"console"<<"serial"<<"parallel"<<"channel"\
    <<"sound"<<"rng"<<"nvram"

#define VMWARE_DEVICE_LIST QStringList()\
    <<"emulator"\
    <<"disk"<<"filesystem"<<"controller"<<"hostdev"\
    <<"smartcard"<<"interface"\
    <<"input"<<"hub"<<"graphics"<<"video"\
    <<"console"<<"serial"<<"parallel"<<"channel"\
    <<"sound"<<"rng"<<"nvram"

#define OPENVZ_DEVICE_LIST QStringList()\
    <<"emulator"\
    <<"disk"<<"filesystem"<<"controller"<<"hostdev"\
    <<"smartcard"<<"interface"\
    <<"input"<<"hub"<<"graphics"<<"video"\
    <<"console"<<"serial"<<"parallel"<<"channel"\
    <<"sound"<<"rng"<<"nvram"

DeviceStack::DeviceStack(
        QWidget *parent,
        virConnectPtr conn) :
    QDialog(parent), currWorkConnect(conn)
{
    setModal(true);
    restoreGeometry(settings.value("DeviceStackGeometry").toByteArray());
    infoLayout = new QVBoxLayout(this);
    infoWidget = new QScrollArea(this);
    scrolled = new QWidget(this);
    scrolled->setLayout(infoLayout);
    infoWidget->setWidget(scrolled);
    infoWidget->setWidgetResizable(true);
    QString connType = QString(virConnectGetType(currWorkConnect)).toLower();
    QStringList devSet, devList, devType;
    devList = DEV_LIST;
    devType = DEV_TYPE;
    if ( connType=="qemu" ) {
        devSet = QEMU_DEVICE_LIST;
    } else if ( connType=="lxc" ) {
        devSet = LXC_DEVICE_LIST;
    } else if ( connType=="xen" ) {
        devSet = XEN_DEVICE_LIST;
    } else if ( connType=="vbox" ) {
        devSet = VBOX_DEVICE_LIST;
    } else if ( connType=="vbox" ) {
        devSet = VMWARE_DEVICE_LIST;
    } else if ( connType=="vbox" ) {
        devSet = OPENVZ_DEVICE_LIST;
    };
    deviceList = new QListWidget(this);
    deviceList->setSortingEnabled(false);
    /* set icons & user data */
    for (int i=0; i<devList.count();i++) {
        if ( devSet.contains(devType.at(i)) ) {
            deviceList->addItem(devList.at(i));
            QListWidgetItem *item = deviceList->item(deviceList->count()-1);
            /*
            item->setIcon(
                  QIcon::fromTheme(
                         item->text()
                         .split(" ")
                         .first()
                         .toLower()));
             */
            item->setData(Qt::UserRole, QVariant(devType.at(i)));
            //qDebug()<<item->text();
        };
    };

    // double event for selection item
    //connect(deviceList, SIGNAL(itemClicked(QListWidgetItem*)),
    //        this, SLOT(showDevice(QListWidgetItem*)));
    connect(deviceList, SIGNAL(itemSelectionChanged()),
            this, SLOT(showDevice()));
    listLayout = new QHBoxLayout(this);
    listLayout->addWidget(deviceList, 3);
    listLayout->addWidget(infoWidget, 8);
    listWidget = new QWidget(this);
    listWidget->setLayout(listLayout);

    addDevice = new QPushButton(QIcon::fromTheme("dialog-ok"), "Add Device", this);
    cancel = new QPushButton(QIcon::fromTheme("dialog-cancel"), "Cancel", this);
    connect(addDevice, SIGNAL(clicked()), this, SLOT(set_Result()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(set_Result()));
    buttonlayout = new QHBoxLayout(this);
    buttonlayout->addWidget(addDevice);
    buttonlayout->addWidget(cancel);
    buttons = new QWidget(this);
    buttons->setLayout(buttonlayout);

    commonLayout = new QVBoxLayout(this);
    commonLayout->addWidget(listWidget);
    commonLayout->addWidget(buttons);
    setLayout(commonLayout);
}
DeviceStack::~DeviceStack()
{
    //disconnect(deviceList, SIGNAL(itemClicked(QListWidgetItem*)),
    //           this, SLOT(showDevice(QListWidgetItem*)));
    disconnect(deviceList, SIGNAL(itemSelectionChanged()),
               this, SLOT(showDevice()));
    disconnect(addDevice, SIGNAL(clicked()), this, SLOT(set_Result()));
    disconnect(cancel, SIGNAL(clicked()), this, SLOT(set_Result()));
    delete deviceList;
    deviceList = NULL;

    delete infoLayout;
    infoLayout = NULL;
    if ( scrolled!=NULL ) {
        delete scrolled;
        scrolled = NULL;
    };
    delete infoWidget;
    infoWidget = NULL;

    delete listLayout;
    listLayout = NULL;
    delete listWidget;
    listWidget = NULL;

    delete addDevice;
    addDevice = NULL;
    delete cancel;
    cancel = NULL;

    delete buttonlayout;
    buttonlayout = NULL;
    delete buttons;
    buttons = NULL;

    delete commonLayout;
    commonLayout = NULL;
}

/* public slots */
QDomDocument DeviceStack::getResult() const
{
    //qDebug()<<"DeviceStack result";
    QDomDocument doc;
    if ( device!=NULL ) {
        doc = device->getDataDocument();
    };
    return doc;
}

/* private slots */
void DeviceStack::showDevice(QListWidgetItem *item)
{
    if ( device!=NULL ) {
        infoLayout->removeWidget(device);
        delete device;
        device = NULL;
    };
    QString deviceType = item->data(Qt::UserRole).toString();
    //qDebug()<<item->text()<<deviceType;
    if ( deviceType == "disk" ) {
        device = new Disk(
                    this,
                    currWorkConnect);
    } else if ( deviceType == "interface" ) {
        device = new NetInterfaces(
                    this,
                    currWorkConnect);
    } else if ( deviceType == "serial" ) {
        device = new CharDevice(this, NULL, NULL, deviceType);
    } else if ( deviceType == "parallel" ) {
        device = new CharDevice(this, NULL, NULL, deviceType);
    } else if ( deviceType == "channel" ) {
        device = new ChannelDevice(this);
    } else if ( deviceType == "console" ) {
        device = new ConsoleDevice(
                          this,
                          currWorkConnect);
    } else if ( deviceType == "smartcard" ) {
        device = new SmartCardDevice(this);
    } else if ( deviceType == "input" ) {
        device = new InputDevice(this);
    } else if ( deviceType == "hub" ) {
        device = new HubDevice(this);
    } else if ( deviceType == "video" ) {
        device = new VideoDevice(this);
    } else if ( deviceType == "sound" ) {
        device = new SoundDevice(this);
    } else if ( deviceType == "hostdev" ) {
        device = new HostDevice(
                          this,
                          currWorkConnect);
    } else if ( deviceType == "graphics" ) {
        device = new GraphicsDevice(
                    this,
                    currWorkConnect);
    } else if ( deviceType == "redirdev" ) {
        device = new RedirDevDevice(
                    this,
                    currWorkConnect);
    } else if ( deviceType == "filesystem" ) {
        device = new FileSystems(
                    this,
                    currWorkConnect);
    } else if ( deviceType == "emulator" ) {
        device = new _QWidget(this);
        //device = new Emulator(
        //            this,
        //            currWorkConnect);
    } else if ( deviceType == "rng" ) {
        device = new Random(this);
    } else if ( deviceType == "memballoon" ) {
        device = new MemBalloon(
                    this,
                    currWorkConnect);
    } else {
        device = new _QWidget(this);
    };
    infoLayout->insertWidget(0, device, -1);
}
void DeviceStack::showDevice()
{
    showDevice(deviceList->currentItem());
}
void DeviceStack::set_Result()
{
    setResult( (sender()==addDevice)?
                   QDialog::Accepted : QDialog::Rejected );
    done(result());
    //qDebug()<<"done";
    settings.setValue("DeviceStackGeometry", saveGeometry());
}
