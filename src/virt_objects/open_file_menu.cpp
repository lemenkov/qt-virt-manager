#include "open_file_menu.h"

OpenFileMenu::OpenFileMenu(QWidget *parent, QString str, QString src) :
    QMenu(parent), method(str), source(src)
{
    fullMethodName = QString("%1_FromXML").arg(method.toLower());
    icon = QIcon::fromTheme( QString("%1-%2").arg(source).arg(method) );
    examples = new QAction(this);
    examples->setText(QString("%1 Virtual %2 from example XML description").arg(method).arg(source));
    examples->setIcon(icon);
    custom = new QAction(this);
    custom->setText(QString("%1 Virtual %2 from custom XML description").arg(method).arg(source));
    custom->setIcon(icon);
    manual = new QAction(this);
    manual->setText(QString("%1 Virtual %2 manually").arg(method).arg(source));
    manual->setIcon(icon);
    connect(examples, SIGNAL(triggered()), this, SLOT(exampleChoised()));
    connect(custom, SIGNAL(triggered()), this, SLOT(customChoised()));
    connect(manual, SIGNAL(triggered()), this, SLOT(manualChoised()));
    addAction(examples);
    addAction(custom);
    addSeparator();
    addAction(manual);
}
OpenFileMenu::~OpenFileMenu()
{
    disconnect(examples, SIGNAL(triggered()), this, SLOT(exampleChoised()));
    disconnect(custom, SIGNAL(triggered()), this, SLOT(customChoised()));
    delete examples;
    examples = NULL;
    delete custom;
    custom = NULL;
    delete manual;
    manual = NULL;
}
void OpenFileMenu::exampleChoised()
{
    QString path = QString("%1/%2").arg(EXAMPLES).arg(source.toLower());
    emitParameters("Get Example Source XML", path);
}
void OpenFileMenu::customChoised()
{
    emitParameters("Get Custom Source XML", "~");
}
void OpenFileMenu::manualChoised()
{
    QStringList parameters;
    parameters << fullMethodName << "manually" << source;
    emit fileForMethod(parameters);
}
void OpenFileMenu::emitParameters(const QString &title, const QString &dirPath)
{
    QString path;
    path = QFileDialog::getOpenFileName(this, title, dirPath);
    if ( !path.isEmpty() ) {
        QStringList parameters;
        parameters << fullMethodName << path;
        emit fileForMethod(parameters);
    };
}
