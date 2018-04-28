#version 330 core
/*
   the default vertex shader that everything shares.
 */
layout(location=0) in vec2 vPos;
layout(location=1) in vec2 vUvs;
layout(location=2) in vec4 vColors;

// up to the fragment shader to decide what these do.
out vec4 aColors;
out vec2 aUvs;
out vec2 aPos;

uniform mat4 projection;
uniform mat4 model; // couldn't calculate rotated vertices well enough in the renderer.
uniform mat4 view;

void main(){
	gl_Position = projection*view*model*vec4( vPos, 0.0, 1.0 );
	aColors = vColors;
	aPos    = vPos;
	aUvs    = vUvs;
}
