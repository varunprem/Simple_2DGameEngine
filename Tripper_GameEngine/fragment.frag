#version 330
in vec3 ourColor; 
out vec4 color;
in vec2 textureCords;
uniform sampler2D ourtexture;
uniform int is_debug=0;

void main(){


	color = texture(ourtexture,textureCords);

	if(is_debug==1) 
	{
		color = vec4(color.x,color.y,color.z, 0.5);
	} 
}
