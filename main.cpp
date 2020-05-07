#include "event/quickapplication.h"
#include "example/dialog.h"
#include "event/quickcontroller.h"

int main(int argc, char **argv)
{
    QuickApplication a(argc,argv);

    QuickController controller;
    Q_UNUSED(controller)

    Dialog dialog;
    dialog.show();

    return a.exec();
}
