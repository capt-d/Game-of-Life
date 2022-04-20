#include <QtWidgets/QApplication>
#include "GoLWindow.h"

int main(int argc, char *argv[])
{
  //Q_INIT_RESOURCE(application);
  
  QApplication a(argc, argv);
  Ui::GoLWindow okno;
  QObject::connect(&a, SIGNAL(focusChanged(QWidget*,QWidget*)), &okno, SLOT(focusChanged(QWidget*,QWidget*)));
  okno.show();
  return a.exec();
}
