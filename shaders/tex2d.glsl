#type vertex
#version 450

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;

out vec2 v_texCoord;

void main()
{
    v_texCoord = texCoord;
    gl_Position = vec4(position, 0.0, 1.0);
}

#type fragment
#version 450

in vec2 v_texCoord;
out vec4 fragColor;

uniform sampler2D tex;

void main()
{
    fragColor = texture(tex, v_texCoord);
}
