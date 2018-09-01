// blackhart headers
#include "../blackhart/export/cpp/Blackhart.hpp"

// blackhart.studio headers
#include "BkEditor.hpp"
#include "BkViewer.hpp"

// ~~~~~ Def(PUBLIC) ~~~~~

BkEditor::BkEditor() :
    QMainWindow{ nullptr }
{
    BkError_PushContext("When creating editor");
    
    createViewport();
    
    BkError_PopContext();
}

BkEditor::~BkEditor()
{

}

// ~~~~~ Def(INTERNAL) ~~~~~

void    BkEditor::createViewport()
{
    BkError_PushContext("When creating viewport");

    BkViewer* viewer = new BkViewer{};
    BK_ERROR(viewer == nullptr, "Memory system has failed to allocate memory block");

    setCentralWidget(viewer);

    BkError_PopContext();
}