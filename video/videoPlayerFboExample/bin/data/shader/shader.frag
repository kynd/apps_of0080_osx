uniform sampler2DRect tex;

void main (void){
	vec4 tex0 = texture2DRect(tex, gl_TexCoord[0].st);
	vec4 tex1 = texture2DRect(tex, gl_TexCoord[0].st + vec2(3.0, 0.0));
	gl_FragColor = (distance(tex0.rgb, tex1.rgb) > 0.04) ? vec4(0.0, 0.0, 0.0, 1.0) : vec4(1.0); 
}