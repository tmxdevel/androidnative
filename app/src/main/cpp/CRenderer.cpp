#include "CRenderer.h"
#include "defines.h"

#include <GLES2/gl2.h>

CRenderer::CRenderer() {

}

CRenderer::~CRenderer() {

}

void CRenderer::onCreate() {
    glClearColor(1.0F, 1.0F, 1.0F, 1.0F);
    if(!initShaders()) {
        _errorString = "Cannot create shader";
        LOGE("Error while init shaders %s: ",_errorString.c_str());
    }
}

void CRenderer::onChanged(int width, int height) {
    glViewport(0, 0, width, height);
}

void CRenderer::onDraw() {
    if(program == -1) return;
    glUseProgram(program);
    GLint colorLoc = glGetUniformLocation(program,"_color");
    GLint posLoc = glGetAttribLocation(program,"_position");

    glEnableVertexAttribArray(posLoc);

    GLfloat color[4] = {0.0F, 0.0F, 0.0F, 1.0F};
    float model[12] = {-0.5F, 0.0F, 0.0F, 1.0F, 0.0F, 0.5F, 0.0F, 1.0F, 0.5F, 0.0F, 0.0F, 1.0F,};
    for(int i = 0; i < 60; i++) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniform4fv(colorLoc,1,color);
        for (int j = 0; j < 1000; j++) {
            glVertexAttribPointer(posLoc,4,GL_FLOAT,GL_FALSE,0,model);
            glDrawArrays(GL_TRIANGLES,0,3);
        }
    }
}

int CRenderer::width() const {
    return _width;
}

int CRenderer::height() const {
    return _height;
}

std::string CRenderer::errorString() const {
    return std::string();
}

int CRenderer::createProgram() {
    return 0;
}

void CRenderer::setVertexShader(const std::string &vertex) {
    if(_vertexShaderRaw != nullptr) delete _vertexShaderRaw;
    _vertexShaderRaw = new char[vertex.length()];
    strcpy(_vertexShaderRaw,vertex.c_str());
}

void CRenderer::setFragmentShader(const std::string &fragment) {
    if(_fragmentShaderRaw != nullptr) delete _fragmentShaderRaw;
    _fragmentShaderRaw = new char[fragment.length()];
    strcpy(_fragmentShaderRaw,fragment.c_str());
}

int createShader(GLenum type, char* source) {
    auto vertexShaderId = glCreateShader(type);
    if(vertexShaderId == 0) {
        return -1;
    }
    glShaderSource(vertexShaderId,1,&source,nullptr);
    glCompileShader(vertexShaderId);
    GLint success = 0;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

    GLint logSize = 0;
    glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &logSize);

    char* log = new char[logSize];
    glGetShaderInfoLog(vertexShaderId,logSize,nullptr,log);
    LOGD("Creating shader: %s",log);

    if(success == GL_TRUE) return vertexShaderId;
    glDeleteShader(vertexShaderId);
    return -1;
}

bool CRenderer::initShaders() {
    int vertexShader = createShader(GL_VERTEX_SHADER,_vertexShaderRaw);
    int fragmentShader = createShader(GL_FRAGMENT_SHADER,_fragmentShaderRaw);
    if(vertexShader == -1 || fragmentShader == -1) return false;

    auto programId = glCreateProgram();
    glAttachShader(programId, static_cast<GLuint>(vertexShader));
    glAttachShader(programId,static_cast<GLuint>(fragmentShader));
    glLinkProgram(programId);

    GLint isLinked = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);

    GLint logSize = 0;
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logSize);
    char* log = new char[logSize];

    glGetProgramInfoLog(programId, logSize, nullptr, log);
    LOGD("Linking program: %s",log);

    if (isLinked == GL_FALSE) {
        glDeleteProgram(programId);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }
    glDetachShader(programId, vertexShader);
    glDetachShader(programId, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    program = programId;
    return true;
}
