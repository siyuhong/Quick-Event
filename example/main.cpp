#include "quickapplication.h"
#include "dialog.h"
#include "quickcontroller.h"

int main(int argc, char **argv)
{
    QuickApplication a(argc,argv);

    QuickController controller;
    Q_UNUSED(controller)

    Dialog dialog;
    dialog.show();

    return a.exec();
}
