#ifndef __BK_VIEWER_HPP__
#define __BK_VIEWER_HPP__

// Qt headers
#include <QOpenGLWidget>
#include <QTime>

// forward declarations
class QMouseEvent;

class BkViewer : public QOpenGLWidget
{
public:
    explicit BkViewer(QWidget* parent = nullptr);
    virtual ~BkViewer() final;

protected:
    virtual void    initializeGL() final;
    virtual void    paintGL() final;
    virtual void    resizeGL(int width, int height) final;

private:
    QTime   time;
};

#endif
