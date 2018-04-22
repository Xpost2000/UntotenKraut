#version 330 core

in vec4 aColors;
in vec2 aUvs;
in vec2 aPos;

out vec4 FragColor;

uniform sampler2D texture;

void main(){
	FragColor = vec4(aColors.rgb, texture2D(texture, aUvs).r);
}
