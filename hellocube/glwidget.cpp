#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
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

    float cubeColor[3] = {1, 0, 0};

}

void GLWidget::initializeGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // enable depth testing
    glEnable(GL_DEPTH_TEST);

    // enable color
    glEnable(GL_COLOR_MATERIAL);

    // init shading model
    glShadeModel(GL_FLAT);

    // enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // lightsource
    float positionLight0[4] = {0.5f, 0.0f, 2.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, positionLight0);

    // set material parameters
    float specularReflection[4] = {0.7, 1.0, 1.0, 1.0};
    int shininess = 60.0f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularReflection);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    // compile and link shaders
    shaderProgram = new QGLShaderProgram(this);

    static const char *fragmentShaderSource =
        "#version 120\n"
        "\n"
        "varying vec3 normal;\n"
        "varying vec3 lightRay;\n"
        "varying vec3 viewRay;\n"
        "void main() {\n"
        "   vec3 N = normalize(normal);\n"
        "   vec3 L = normalize(lightRay);\n"
        "   vec3 V = normalize(viewRay);\n"
        "   float LdotN = dot(L, N);\n"
        "   if (LdotN > 0) {\n"
        "       vec3 R = 2 * LdotN * N - L;\n"
        "       float RdotV = max(0, dot(R,V));\n"
        "       vec4 diffuseColor = gl_Color * LdotN * gl_LightSource[0].diffuse;\n"
        "       vec4 specularColor = gl_FrontMaterial.specular * pow(RdotV, gl_FrontMaterial.shininess) * gl_LightSource[0].specular;\n"
        "       gl_FragColor = diffuseColor + specularColor;\n"
        "   } else {\n"
        "       gl_FragColor = vec4(0,0,0,1);\n"
        "       ;\n"
        "   }\n"
        "}\n";
    static const char *vertexShaderSource =
        "#version 120\n"
        "\n"
        "varying vec3 normal;\n"
        "varying vec3 lightRay;\n"
        "varying vec3 viewRay;\n"
        "void main() {\n"
        "   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
        "   normal = normalize(gl_NormalMatrix * gl_Normal);\n"
        "   lightRay = gl_LightSource[0].position.xyz - vec3(gl_ModelViewMatrix * gl_Vertex);\n"
        "   viewRay = (- gl_ModelViewMatrix * gl_Vertex).xyz;\n"
        "   gl_FrontColor = gl_Color;\n"
        "   gl_BackColor = gl_Color;\n"
        "}\n";

    shaderProgram->addShaderFromSourceCode(QGLShader::Vertex, vertexShaderSource);
    shaderProgram->addShaderFromSourceCode(QGLShader::Fragment, fragmentShaderSource);

    shaderProgram->link();
/*
    shadingVertexShader = new QGLShader(QGLShader::Vertex, this);
    shadingFragmentShader = new QGLShader(QGLShader::Fragment, this);

    //shadingVertexShader->compileSourceFile("/home/claudia/OpenGL Praktikum/Assignment 4/Terrain Modeling Tool/shaders/phongVertexShader.vertexShader");
    //shadingFragmentShader->compileSourceFile("/home/claudia/OpenGL Praktikum/Assignment 4/Terrain Modeling Tool/shaders/phongFragmentShader.fragmentShader");

    shadingProgram->addShader(shadingVertexShader);
    shadingProgram->addShader(shadingFragmentShader);*/
}

void GLWidget::resizeGL(int width, int height) {
    if (height == 0)
        height = 1;
    // set the viewport to be the entire window
    glViewport(0, 0, width, height);

    // reset projection matrix
    glMatrixMode(GL_PROJECTION);
    // reset coordinate system
    glLoadIdentity();
    gluPerspective(45.0f, (double) width / (double) height, 0.01, 100.0);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // set camera position
    glTranslatef(currentTranslation.x(), currentTranslation.y(), current_z);

    // apply rotation
    QMatrix4x4 rotation;
    rotation.rotate(currentRotation);
    glMultMatrix(rotation.constData());
    int nrVerticesSameColor = 4 * tesselationSteps * tesselationSteps;

    glBegin(GL_QUADS);
    // draw all faces of the cube and set color and normal accordingly
    for (uint i = 0; i < vertices.size(); i++) {
        if (i % nrVerticesSameColor == 0) {
            glColor3f(colors[i / nrVerticesSameColor][0], colors[i / nrVerticesSameColor][1], colors[i / nrVerticesSameColor][2]);
            glNormal3f(normals[i / nrVerticesSameColor][0], normals[i / nrVerticesSameColor][1], normals[i / nrVerticesSameColor][2]);
        }
        glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
    }
    glEnd();
}
inline void GLWidget::glMultMatrix(const GLfloat  *m) { glMultMatrixf(m); }
inline void GLWidget::glMultMatrix(const GLdouble *m) { glMultMatrixd(m); }

GLWidget::~GLWidget()
{
    //cleanup();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{

}

void GLWidget::mousePressEvent(QMouseEvent *event)
{

}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

}

