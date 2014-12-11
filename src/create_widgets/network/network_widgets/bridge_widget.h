#ifndef BRIDGE_WIDGET_H
#define BRIDGE_WIDGET_H

#include "create_widgets/domain/_qwidget.h"

class Bridge_Widget : public _QWidget
{
    Q_OBJECT
public:
    explicit Bridge_Widget(QWidget *parent = 0);
    QCheckBox       *title;
    QLineEdit       *bridgeName;
    QCheckBox       *stp;
    QSpinBox        *delay;

private:
    QLabel          *delayLabel;
    QWidget         *bridge;
    QGridLayout     *bridgeLayout;
    QVBoxLayout     *commonLayout;
};

#endif // BRIDGE_WIDGET_H