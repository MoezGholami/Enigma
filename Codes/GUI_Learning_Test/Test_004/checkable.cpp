#include "checkable.h"
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>


Checkable::Checkable(QWidget *parent)
    : QMainWindow(parent)
{

  viewst = new QAction("&View statusbar", this);
  viewst->setCheckable(true);
  viewst->setChecked(true);

  QMenu *file;
  file = menuBar()->addMenu("F&ile");
  file->addAction(viewst);
  
  statusBar();
  
  connect(viewst, SIGNAL(triggered()), this, 
    SLOT(toggleStatusbar()));

}

void Checkable::toggleStatusbar()
{
  if (viewst->isChecked())
    statusBar()->show();
  else
    statusBar()->hide();
}
