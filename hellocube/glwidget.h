#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <GL/glu.h>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QGLShader>


class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

protected:
    void initializeGL() override;
    void paintGL();
    void resizeGL(int width, int height);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    inline void glMultMatrix(const GLfloat  *m);
    inline void glMultMatrix(const GLdouble *m);

private:
    int tesselationSteps;
    float current_z;
    QVector2D lastTranslationPoint;
    QVector3D lastRotationPoint;
    float trackballRadius;
    QQuaternion currentRotation;
    QVector2D currentTranslation;
    std::vector<std::vector<float>> initVertices;
    std::vector<std::vector<float> > vertices;
    std::vector<std::vector<float> > colors;
    std::vector<std::vector<float> > normals;

    QGLShaderProgram *shaderProgram;
    QGLShader *vertexShader;
    QGLShader *fragmentShader;




};

#endif // GLWIDGET_H
