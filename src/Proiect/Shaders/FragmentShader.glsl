#pragma once
#version 410

layout(location = 0) in vec2 texture_coord;
uniform sampler2D textureImage;
vec2 textureCoord = vec2(texture_coord.x,  texture_coord.y);

layout(location = 0) out vec4 out_color;

void main()
{
	out_color = texture(textureImage, textureCoord);
}