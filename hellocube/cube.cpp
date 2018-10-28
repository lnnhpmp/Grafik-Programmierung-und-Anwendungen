#include "cube.h"

//#include <QVector2D>
#include <QVector3D>

struct VertexData
{
    QVector3D position;

};

Cube::Cube()
{
    // set cube vertices
    GLfloat x = 0.5f;

    std::vector<GLfloat> position0 = {-x, -x, +x};
    std::vector<GLfloat> position1 = {+x, -x, +x};
    std::vector<GLfloat> position2 = {+x, -x, -x};
    std::vector<GLfloat> position3 = {-x, -x, -x};
    std::vector<GLfloat> position4 = {-x, +x, +x};
    std::vector<GLfloat> position5 = {+x, +x, +x};
    std::vector<GLfloat> position6 = {+x, +x, -x};
    std::vector<GLfloat> position7 = {-x, +x, -x};

    // front initVertices[0:3]
    initVertices.push_back(position0);
    initVertices.push_back(position1);
    initVertices.push_back(position5);
    initVertices.push_back(position4);

    // right initVertices[4:7]
    initVertices.push_back(position2);
    initVertices.push_back(position6);
    initVertices.push_back(position5);
    initVertices.push_back(position1);

    // back initVertices[8:11]
    initVertices.push_back(position3);
    initVertices.push_back(position2);
    initVertices.push_back(position6);
    initVertices.push_back(position7);

    // left initVertices[12:15]
    initVertices.push_back(position3);
    initVertices.push_back(position0);
    initVertices.push_back(position4);
    initVertices.push_back(position7);

    // bottom initVertices[16:19]
    initVertices.push_back(position3);
    initVertices.push_back(position0);
    initVertices.push_back(position1);
    initVertices.push_back(position2);

    // top initVertices[20:23]
    initVertices.push_back(position7);
    initVertices.push_back(position4);
    initVertices.push_back(position5);
    initVertices.push_back(position6);

    vertices = initVertices;

    // set indices list
    for (uint i = 0; i < vertices.size(); i++) {
        indicesList_.push_back(i);
    }

    // set cube colors
    std::vector<GLfloat> color0 = {0, 0, 1};
    std::vector<GLfloat> color1 = {1, 0, 0};
    std::vector<GLfloat> color2 = {1, 1, 0};
    std::vector<GLfloat> color3 = {0, 1, 1};
    std::vector<GLfloat> color4 = {1, 0, 1};
    std::vector<GLfloat> color5 = {0, 1, 0};

    colors.push_back(color0);
    colors.push_back(color1);
    colors.push_back(color2);
    colors.push_back(color3);
    colors.push_back(color4);
    colors.push_back(color5);
}

void Cube::draw()
{
    // Generate a new array.
   // VAO_ = new QOpenGLVertexArrayObject();
    glDrawElements(
            GL_QUADS,      // mode
            indicesList_.size(),    // count
            GL_UNSIGNED_INT,       // type
            (void*)0           // element array buffer offset
        );
}
