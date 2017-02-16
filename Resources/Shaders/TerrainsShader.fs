precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;

void main()
{
vec4 txtBlend = texture2D(u_texture0, v_uv);
vec4 txtColor1 = texture2D(u_texture1, v_uv);
vec4 txtColor2 = texture2D(u_texture2, v_uv);
vec4 txtColor3 = texture2D(u_texture3, v_uv);

//FinalColor = (BT.r * Tex1 + BT.g * Tex2 + BT.b * Tex3) / (BT.r + BT.g + BT.b)
vec4 color = txtBlend.r * txtColor1 + txtBlend.g * txtColor2 + txtBlend.b * txtColor3;
color = color / (txtBlend.r + txtBlend.g + txtBlend.b);
gl_FragColor = vec4(color.rgb,1.0);
}
