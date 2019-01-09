#version 330 core

// Texture Color Output

out vec4 FragColor;
uniform vec3 LampColor;

void main()
{
    FragColor = vec4(LampColor,1.0); // set alle 4 vector values to 1.0
}