uniform sampler2DRect tex;
uniform sampler2DRect water;
uniform sampler2DRect noise;

void main (void){
	vec4 noiseTex = texture2DRect(noise, gl_TexCoord[0].st);
	vec4 waterTex = texture2DRect(water, gl_TexCoord[0].st);
	float scroll = (waterTex.r * noiseTex.b * - 1.0) * 0.8;
	vec4 tex0 = texture2DRect(tex, gl_TexCoord[0].st + vec2(0.0, scroll));
	vec4 tex1 = texture2DRect(tex, gl_TexCoord[0].st + vec2(-1.0, 0.5 + scroll));
	vec4 tex2 = texture2DRect(tex, gl_TexCoord[0].st + vec2(-0.5, -1.0 + scroll));
	vec4 tex3 = texture2DRect(tex, gl_TexCoord[0].st + vec2(1.0, -0.5 + scroll));
	vec4 tex4 = texture2DRect(tex, gl_TexCoord[0].st + vec2(0.5, 1.0 + scroll));
	
	vec4 ave = (tex1 + tex2 + tex3 + tex4) / 4.0;
	vec4 mixCol = mix(tex0, ave, min(0.8, waterTex.r *3.0));
	mixCol = min(vec4(1.0), mixCol +vec4(0.004));
	
	vec4 outCol = min(mixCol, tex0);
	
	gl_FragColor = outCol; 
}