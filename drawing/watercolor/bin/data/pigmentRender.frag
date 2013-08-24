uniform sampler2DRect tex;
uniform float r;
uniform float g;
uniform float b;


void main (void){
	vec4 tex0 = texture2DRect(tex, gl_TexCoord[0].st);
	
	float pigment = tex0.r;
	vec4 color = vec4(r / 255.0, g / 255.0, b / 255.0, 1.0);
	vec4 outCol = mix(vec4(1.0), color, pigment / 1.5);
	
	gl_FragColor = vec4(outCol); 
}