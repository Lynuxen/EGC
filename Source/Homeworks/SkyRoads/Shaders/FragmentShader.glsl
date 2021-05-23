#version 330

out vec3 fragcolor;
in vec3 frag_color;

void main()
{
    fragcolor = frag_color;
}