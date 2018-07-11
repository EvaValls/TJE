
varying vec3 v_position;
varying vec3 v_world_position;
varying vec3 v_normal;
varying vec2 v_uv;
varying vec4 v_color;

uniform vec3 u_camera_pos;
uniform sampler2D u_texture;
uniform sampler2D u_normal_texture;
uniform sampler2D u_sky_texture;
uniform float u_time;

void main()
{
	vec2 uv = v_uv;
	vec4 color = texture2D( u_texture, uv );
	vec4 color_normal = texture2D(u_normal_texture, uv );

	//passar de coordenades [0,1] a [-1,1]

	vec3 N= 2*color_normal.xyz-1.0;

	//intercanviar coordenades Y i Z
	vec3 N_z = vec3(N.x, N.z, N.y);

	
	//Vector que va del punt al centre de la càmera
	vec3 V = (v_world_position - u_camera_pos);
	V = normalize(V);

	//compute eye reflected vector
	vec3 R = -reflect(V,N_z);

	//compute the yaw using arc tangent 
	float yaw =0.0;
	yaw = atan(R.x,R.z) / 6.28318531 -0.25;
	//in case the 0deg doesn’t match our Z axis, we can rotate 90 degrees

	//compute the pitch using arc sinus
	float pitch = asin(R.y) / 1.57079633; //0 means bottom, 1 means top

	//build the UV vector for hemisphere (in case pitch is negative, clamp it to 0)
	vec2 uv_reflection = vec2(yaw, clamp(pitch, 0.0, 1.0) );

	//read the sky texture (ignoring mipmaps to avoid problems)
	vec4 sky_color = texture2DLod( u_sky_texture, uv_reflection, 3.0);


	color = mix(color, sky_color,0.5);
	gl_FragColor = color;
}
