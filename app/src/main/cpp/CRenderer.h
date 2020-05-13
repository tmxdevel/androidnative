#ifndef NATIVEANDROID_CRENDERER_H
#define NATIVEANDROID_CRENDERER_H

#include <string>

class CRenderer
{
public:
    explicit CRenderer();
    ~CRenderer();

    void setVertexShader(const std::string &vertex);
    void setFragmentShader(const std::string &fragment);
    bool initShaders();
    void onCreate();
    void onChanged(int width, int height);
    void onDraw();

    int width() const;
    int height() const;
    std::string errorString() const;

    int programId()const{ return program; }

private:
    int createProgram();

    char* _vertexShaderRaw = nullptr;
    char* _fragmentShaderRaw = nullptr;

    int _width = 1;
    int _height = 1;

    std::string _errorString = "";
    int program = -1;
};

#endif //NATIVEANDROID_CRENDERER_H
