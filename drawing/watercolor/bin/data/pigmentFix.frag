uniform sampler2DRect tex;
uniform sampler2DRect pigment;
uniform float r;
uniform float g;
uniform float b;


void main (void){
	vec4 tex0 = texture2DRect(tex, gl_TexCoord[0].st);
	vec4 pigmentTex = texture2DRect(pigment, gl_TexCoord[0].st);
	
	float fix = pigmentTex.b;
	vec4 color = vec4(r / 255.0, g / 255.0, b / 255.0, 1.0);
	vec4 mixCol = mix(tex0, color, fix / 0.3);
	vec4 outCol = min(mixCol, tex0);
	
	gl_FragColor = vec4(outCol); 
}