//global variables from the CPU
uniform mat4 model;
uniform mat4 mvp;

//vector Normal i coordenades del punt que es passaran al Pixel Shader
varying vec3 N;
varying vec3 P;

//vars to pass to the pixel shader
varying vec2 v_coord;
uniform sampler2D color_texture;

void main()
{	
	//get the texture coordinates (per vertex) and pass them to the pixel shader
	v_coord = gl_MultiTexCoord0.xy;

	P = (model*gl_Vertex).xyz;
	P = normalize(P);
	
	vec3 normal = gl_Normal.xyz;
	vec4 wcoord = vec4(normal, 0.0);
	N = (model * wcoord).xyz;
	N = normalize(N);

	//project the vertex by the model view projection 
	gl_Position = mvp * gl_Vertex; //output of the vertex shader
}

