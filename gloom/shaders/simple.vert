#version 430 core

in vec3 position;
out vec3 frag_position;

void main()
{
    gl_Position = vec4(-position.xy, position.z, 1.0f);

    // Passing on to fragment shader
    frag_position = gl_Position.xyz;
}


