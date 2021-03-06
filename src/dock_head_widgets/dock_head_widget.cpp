#include "dock_head_widget.h"

DockHeadWidget::DockHeadWidget(
        QWidget *parent, const QString _barName) :
    QWidget(parent), name(_barName)
{
    icon = new QLabel(this);
    nameWdg = new BarNameLabel(this);
    nameWdg->setText(name);
    floatIt = new QPushButton("", this);
    floatIt->setFlat(false);
    floatIt->setCheckable(true);
    commonLayout = new QVBoxLayout(this);
    commonLayout->setDirection(QBoxLayout::BottomToTop);
    commonLayout->addWidget(icon, 0, Qt::AlignBottom);
    commonLayout->addWidget(nameWdg);
    commonLayout->addStretch(-1);
    commonLayout->addWidget(floatIt, 0, Qt::AlignTop);
    connect(floatIt, SIGNAL(clicked(bool)),
            this, SIGNAL(floatChanged(bool)));
}

/* public slots */
void DockHeadWidget::setTabBarName(const QString &_name)
{
    int _size = this->fontInfo().pixelSize();
    icon->setPixmap(
                QIcon::fromTheme(_name)
                .pixmap(_size));
    floatStateChanged(false);
    floatIt->setMaximumSize(QSize(_size, _size));
    setLayout(commonLayout);
}
void DockHeadWidget::floatStateChanged(bool _floated)
{
    QString _icon;
    _icon.append((!_floated)? "dock_up":"dock_down");
    floatIt->setIcon(QIcon::fromTheme(_icon));
    floatIt->setChecked(_floated);
    nameWdg->setColor((_floated)? 0x008000:0x000080);
}
