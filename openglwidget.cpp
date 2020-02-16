#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QGLWidget(parent),
      cut_size(100, 100),
      blend(GL_ONE, GL_ONE_MINUS_SRC_ALPHA),
      atest_func(GL_ALWAYS),
      atest_ref(0),
      cur_primitive_name("GL_POINTS"),
      drawing(false)
{
    //init gl vars map
    this->gl_vars.insert({"GL_POINTS", GL_POINTS});
    this->gl_vars.insert({"GL_LINES", GL_LINES});
    this->gl_vars.insert({"GL_LINE_STRIP", GL_LINE_STRIP});
    this->gl_vars.insert({"GL_LINE_LOOP", GL_LINE_LOOP});
    this->gl_vars.insert({"GL_TRIANGLES", GL_TRIANGLES});
    this->gl_vars.insert({"GL_TRIANGLE_STRIP", GL_TRIANGLE_STRIP});
    this->gl_vars.insert({"GL_TRIANGLE_FAN", GL_TRIANGLE_FAN});
    this->gl_vars.insert({"GL_QUADS", GL_QUADS});
    this->gl_vars.insert({"GL_QUAD_STRIP", GL_QUAD_STRIP});
    this->gl_vars.insert({"GL_POLYGON", GL_POLYGON});
    this->gl_vars.insert({"GL_NEVER", GL_NEVER});
    this->gl_vars.insert({"GL_LESS", GL_LESS});
    this->gl_vars.insert({"GL_EQUAL", GL_EQUAL});
    this->gl_vars.insert({"GL_LEQUAL", GL_LEQUAL});
    this->gl_vars.insert({"GL_GREATER", GL_GREATER});
    this->gl_vars.insert({"GL_NOTEQUAL", GL_NOTEQUAL});
    this->gl_vars.insert({"GL_GEQUAL", GL_GEQUAL});
    this->gl_vars.insert({"GL_ALWAYS", GL_ALWAYS});
    this->gl_vars.insert({"GL_ZERO", GL_ZERO});
    this->gl_vars.insert({"GL_ONE", GL_ONE});
    this->gl_vars.insert({"GL_SRC_COLOR", GL_SRC_COLOR});
    this->gl_vars.insert({"GL_DST_COLOR", GL_DST_COLOR});
    this->gl_vars.insert({"GL_ONE_MINUS_DST_COLOR", GL_ONE_MINUS_DST_COLOR});
    this->gl_vars.insert({"GL_SRC_ALPHA", GL_SRC_ALPHA});
    this->gl_vars.insert({"GL_ONE_MINUS_SRC_ALPHA", GL_ONE_MINUS_SRC_ALPHA});
    this->gl_vars.insert({"GL_DST_ALPHA", GL_DST_ALPHA});
    this->gl_vars.insert({"GL_ONE_MINUS_DST_ALPHA", GL_ONE_MINUS_DST_ALPHA});
    this->gl_vars.insert({"GL_SRC_ALPHA_SATURATE", GL_SRC_ALPHA_SATURATE});
    //start timer

    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(60);
}

void OpenGLWidget::draw()
{
    QColor color;
    glBegin(gl_vars.at(cur_primitive_name));
    for(int i = 0; i < points.length(); i++){
        color = QColor::fromHsl(i * 10 % 360, 250, 128);
        glColor4f(static_cast<float>(color.red()) / 255,
                  static_cast<float>(color.green()) / 255,
                  static_cast<float>(color.blue()) / 255,
                  static_cast<float>(i * 15 + 30) / 255);

        glVertex2f((points.begin()+i)->x(), (points.begin()+i)->y());
    }
    glEnd();
}

void OpenGLWidget::set_primitive(const QString& primitive_name)
{
    this->cur_primitive_name = primitive_name;
}

void OpenGLWidget::set_cutx(int x)
{
    this->cut_coords.first = x;
}

void OpenGLWidget::set_cuty(int y)
{
    this->cut_coords.second = y;
}

void OpenGLWidget::set_cutw(int w)
{
    this->cut_size.first = w;
}

void OpenGLWidget::set_cuth(int h)
{
    this->cut_size.second = h;
}

void OpenGLWidget::set_blend1(const QString& glvar_name)
{
    this->blend.first = gl_vars.at(glvar_name);
}

void OpenGLWidget::set_blend2(const QString& glvar_name)
{
    this->blend.second = gl_vars.at(glvar_name);
}

void OpenGLWidget::set_alphatest_func(const QString& glvar_name)
{
    this->atest_func = gl_vars.at(glvar_name);
}

void OpenGLWidget::set_alphatest_ref(int val)
{
    this->atest_ref = static_cast<float>(val) / 100;
}

void OpenGLWidget::initializeGL()
{
    qglClearColor(Qt::white);
//    glEnable(GL_NORMALIZE);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_ALPHA_TEST);

    glBlendFunc(blend.first, blend.second);
    glAlphaFunc(atest_func, atest_ref);

    glPointSize(10.f);
    glLineWidth(10.f);
    glScissor(window_size.first*cut_coords.first / 100,
              window_size.first*cut_coords.second / 100,
              window_size.first*cut_size.first / 100,
              window_size.second*cut_size.second / 100) ;
    draw();
    swapBuffers();
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    window_size = {w, h};
    glViewport(0, 0, w, h);//вывод во всей области виджета
    glMatrixMode(GL_PROJECTION);//задает матрицу(проекций)
    glLoadIdentity();//заменяет текущую матрицу на единичную
    glOrtho(0.0, this->width(), this->height(), 0, 0, 1);//умножает текущую матрицу на ортогональную ей
    glMatrixMode(GL_MODELVIEW);//применяет послед операции в стек матричного представления
    glLoadIdentity();//заменяет текущую матрицу на единичную
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        points.append(event->pos());
    }

    if (event->button() == Qt::RightButton) {
        points.clear();
    }
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{

}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{

}
