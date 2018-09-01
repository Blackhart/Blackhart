#include <QApplication>

// blackhart.studio headers
#include "BkEditor.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    BkEditor editor;

    editor.show();

    return app.exec();
}