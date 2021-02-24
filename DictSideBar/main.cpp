#include "widget.h"
#include <QApplication>
#include "headerbar.h"
#include "headerbarsearch.h"
#include "sidebar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SideBar sidebar;

    //w.show();
//    HeaderBar headerBar;
    //HeaderBarSearch bar;
    //headerBar.show ();
    sidebar.show ();
    return a.exec();
}
