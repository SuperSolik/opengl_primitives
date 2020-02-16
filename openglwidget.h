#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>
#include <QtMath>

#include <map>

class OpenGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);

    void draw();

public slots:
    void set_primitive(const QString& primitive_name);
    void set_cutx(int x);
    void set_cuty(int y);
    void set_cutw(int w);
    void set_cuth(int h);
    void set_blend1(const QString& glvar_name);
    void set_blend2(const QString& glvar_name);
    void set_alphatest_func(const QString& glvar_name);
    void set_alphatest_ref(int val);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    std::pair<float, float> cut_coords; // first = start_x, second = start_y
    std::pair<float, float> cut_size; // first = width, second = height
    std::pair<float, float> window_size; // same
    std::pair<GLenum, GLenum> blend;

    GLenum atest_func;
    GLclampf atest_ref;

    QTimer timer;
    QString cur_primitive_name;
    QString cur_atest;
    QString cur_fact;

    bool drawing;
    QVector<QPointF> points;
    QVector<QRgb> colors;
    std::map<QString, GLenum> gl_vars;
};

#endif // OPENGLWIDGET_H
