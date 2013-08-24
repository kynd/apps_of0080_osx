
uniform sampler2DRect tex;
uniform sampler2DRect noise;
uniform sampler2DRect water;

void main (void){
	vec4 noiseTex = texture2DRect(noise, gl_TexCoord[0].st);
	vec2 bleedVec = -(noiseTex.xy - 0.5) * 2.0;
	vec4 waterTex = texture2DRect(water, gl_TexCoord[0].st);
	vec4 pigTex0 = texture2DRect(tex, gl_TexCoord[0].st);
	vec4 pigTex1 = texture2DRect(tex, gl_TexCoord[0].st + vec2(-1.0, 0.5));
	vec4 pigTex2 = texture2DRect(tex, gl_TexCoord[0].st + vec2(-0.5, -1.0));
	vec4 pigTex3 = texture2DRect(tex, gl_TexCoord[0].st + vec2(1.0, -0.5));
	vec4 pigTex4 = texture2DRect(tex, gl_TexCoord[0].st + vec2(0.5, 1.0));
	
	vec4 texOut = texture2DRect(tex, gl_TexCoord[0].st + bleedVec); // out
	vec4 texIn = texture2DRect(tex, gl_TexCoord[0].st - bleedVec); // in
	
	float avePigment = (pigTex0.r + pigTex1.r + pigTex2.r +pigTex3.r + pigTex4.r) / 5.0;
	
	float waterFl = waterTex.r;
	float waterFi = waterTex.g;
	float pigment = pigTex0.r;
	
	//blur
	pigment = mix(pigment, avePigment, 0.13);
	
	//flow
	float flow = 0.5 * waterFl;
	pigment = min(1.0, pigment + min(flow, texIn.r) * length(bleedVec));
	pigment = max(0.0, pigment - flow  * length(bleedVec));

	
	float fix = max(0.0, pigment - waterFi);
	pigment = max(0.0, min(waterFi, pigment));
	
	gl_FragColor = vec4(pigment, 0.0, fix, 1.0);
}