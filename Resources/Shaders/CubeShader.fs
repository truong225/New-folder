precision mediump float;
uniform samplerCube u_texture;
varying vec3 v_pos;
void main()
{
	gl_FragColor = textureCube(u_texture,v_pos);
	//gl_FragColor = vec4(color,1.0);
}
