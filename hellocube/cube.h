#ifndef CUBE_H
#define CUBE_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QVector>

class Cube
{
public:
    Cube();
    void draw();
protected:
    std::vector<std::vector<GLfloat>> initVertices;
    std::vector<std::vector<GLfloat>> vertices;
    std::vector<std::vector<GLfloat>> colors;
    std::vector<uint> indicesList_;
    QOpenGLVertexArrayObject m_VAO;


};

#endif // CUBE_H
