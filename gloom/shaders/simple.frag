#version 430 core

out vec4 color;
in vec3 frag_position;

void main()
{

    // For gradient
    float x_value = (1+frag_position.x)/2;
    float y_value = (1+frag_position.y)/2;
    vec4 highlight_color = vec4(x_value,y_value,0.0f,1.0f);
    vec4 lowlight_color = vec4(y_value,x_value,1.0f, 1.0f);

    // For checkerboard pattern
    bool x_high = int(gl_FragCoord.x / 100) % 2 == 0;
    bool y_high = int(gl_FragCoord.y / 100) % 2 == 0;
    bool is_checked = (x_high && !y_high) || (!x_high && y_high);

    color = (is_checked) ? highlight_color : lowlight_color;

}
