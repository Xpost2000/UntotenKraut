#version 330 core

in vec4 aColors;
in vec2 aUvs;
in vec2 aPos;

out vec4 FragColor;

uniform sampler2D texture;

void main(){
	FragColor = texture2D( texture , aUvs ) * aColors;
}
