#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QMenu>
#include <QDebug>

class ToolBar : public QToolBar
{
  Q_OBJECT
public:
  ToolBar(QWidget *parent);
  ~ToolBar();

  QAction    *_hideAction;
  QAction    *_createAction;
  QAction    *_editAction;
  QAction    *_deleteAction;
  QAction    *_openAction;
  QAction    *_showAction;
  QAction    *_closeAction;
  QAction    *_closeAllAction;
  QAction    *_docsUpAction;
  QAction    *_closeOverview;
  QAction    *_exitAction;

  QAction    *_logUpAction;
  QAction    *_domUpAction;
  QAction    *_netUpAction;
  QAction    *_storageUpAction;

signals:
  void        warningShowed();

private:
  QAction    *itemControlAction;
  QMenu      *itemControlMenu;

  QMenu      *showDocksControlMenu;

private slots:
  void initActions();
  void addItemControlMenu();
  void addDocksControlMenu();
  void mainWindowUp();
  void showHoveredMenu();
  void showMenu();

public slots:
  Qt::ToolBarArea get_ToolBarArea(int) const;
};
#endif   // TOOLBAR_H
