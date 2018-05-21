#ifndef __BK_EDITOR_HPP__
#define __BK_EDITOR_HPP__

// Qt headers
#include <QOpenGLWidget>

class BkViewer : public QOpenGLWidget
{
public:
    BkViewer(QWidget* parent = nullptr);
    ~BkViewer();

protected:
    virtual void    initializeGL() final;
    virtual void    paintGL() final;
    virtual void    resizeGL(int width, int height) final;
};

#endif
