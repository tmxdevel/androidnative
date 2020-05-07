#ifndef NATIVEANDROID_CRENDERER_H
#define NATIVEANDROID_CRENDERER_H


#include <string>

class CRenderer
{
public:
    explicit CRenderer();

    void setShaders(const std::string &vertex, const std::string &fragment);
    void onCreate();
    void onChanged(int width, int height);
    void onDraw();

    int width() const;
    int height() const;
    std::string errorString() const;

private:
    int createProgram();

    char* _vertexShaderRaw = nullptr;
    char* _fragmentShaderRaw = nullptr;

    int _width = 1;
    int _height = 1;

    std::string _errorString = "";
};


#endif //NATIVEANDROID_CRENDERER_H
