#include <QApplication>
#include "BkViewer.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    BkViewer viewer;

    viewer.show();

    return app.exec();
}