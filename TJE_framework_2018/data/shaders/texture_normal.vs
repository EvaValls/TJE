//global variables from the CPU
uniform mat4 u_model;
uniform mat4 u_mvp;
uniform mat4 modelt;

//vector Normal i coordenades del punt que es passaran al Pixel Shader
varying vec3 N;
varying vec3 P;

//vars to pass to the pixel shader
varying vec2 v_coord;
uniform sampler2D u_texture;
uniform sampler2D normal_texture;

void main()
{	
	//get the texture coordinates (per vertex) and pass them to the pixel shader
	v_coord = gl_MultiTexCoord0.xy;

	vec4 normal = texture2D(normal_texture, v_coord );
	//passar de coordenades [0,1] a [-1,1]
	N= 2*normal.xyz-1;
	
	P = (u_model*gl_Vertex).xyz;
	P = normalize(P);
	
	vec4 wcoord = vec4(N, 1.0);
	N = (u_model * wcoord).xyz;
	N = normalize(N);

	//project the vertex by the model view projection 
	gl_Position = u_mvp * gl_Vertex; //output of the vertex shader
}

