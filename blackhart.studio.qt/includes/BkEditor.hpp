#ifndef __BK_EDITOR_HPP__
#define __BK_EDITOR_HPP__

#include <QMainWindow>

class BkEditor : public QMainWindow
{
public:
    BkEditor();
    ~BkEditor() override;
private:
    void    createViewport();
};

#endif