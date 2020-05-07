precision highp float;

attribute vec2 _texture;
attribute vec4 _position;

void main()
{
    v_texture = _texture;
    gl_Position = _position;
}