#include "event/quickapplication.h"
#include "example/dialog.h"
#include "event/quickcontroller.h"
#include <QThread>

int main(int argc, char **argv)
{
    QuickApplication a(argc,argv);

    QuickController controller;

    Dialog dialog;
    dialog.show();

    return a.exec();
}
