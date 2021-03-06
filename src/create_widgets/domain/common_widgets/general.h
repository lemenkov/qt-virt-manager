#ifndef GENERAL_H
#define GENERAL_H

#include "create_widgets/domain/_tab.h"
#include <QTextEdit>

class General : public _Tab
{
    Q_OBJECT
public:
    explicit General(
            QWidget *parent = NULL,
            QString  _caps  = "",
            QString  _xmlDesc = QString());

signals:

private:
    const QString    xmlDesc;
    QString          capabilities;
    QLabel          *typeLabel;
    QLabel          *archLabel;
    QString          type;
    QString          arch;
    QString          os_type;
    QLabel          *nameLabel;
    QLineEdit       *name;
    QLabel          *uuidLabel;
    QLineEdit       *uuid;
    QLabel          *titleLabel;
    QLineEdit       *title;
    QLabel          *descLabel;
    QTextEdit       *description;

public slots:
    QDomDocument     getDataDocument() const;
    void             changeArch(QString&);

private slots:
    void             readCapabilities();
    void             readXMLDesciption();
    void             readXMLDesciption(QString&);
};

#endif // GENERAL_H
