#ifndef NAT_MODE_WIDGET_H
#define NAT_MODE_WIDGET_H

#include "create_widgets/domain/_qwidget.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>

class NAT_Mode_widget : public _QWidget
{
    Q_OBJECT
public:
    explicit NAT_Mode_widget(QWidget *parent = 0);
    QLineEdit       *ipStart, *ipEnd;
    QSpinBox        *portStart, *portEnd;
    QCheckBox       *addrRange, *portRange;

private:
    QHBoxLayout     *addrLayout, *portLayout;
    QWidget         *addrWdg, *portWdg;
    QVBoxLayout     *commonLayout;

private slots:
    void             portStartChanged(int);
    void             portEndChanged(int);
};

#endif // NAT_MODE_WIDGET_H
