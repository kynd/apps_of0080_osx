uniform sampler2DRect tex;
uniform sampler2DRect noise;
uniform sampler2DRect water;

void main (void){
	vec4 noiseTex = texture2DRect(noise, gl_TexCoord[0].st);
	
	float scroll = -0.0;
	vec4 tex0 = texture2DRect(tex, gl_TexCoord[0].st + vec2(0.0, scroll));
	vec2 bleedVec = -(noiseTex.xy - 0.5) * 1.0;
	vec4 tex1 = texture2DRect(tex, gl_TexCoord[0].st + vec2(-1.0, 0.5 + scroll));
	vec4 tex2 = texture2DRect(tex, gl_TexCoord[0].st + vec2(-0.5, -1.0 + scroll));
	vec4 tex3 = texture2DRect(tex, gl_TexCoord[0].st + vec2(1.0, -0.5 + scroll));
	vec4 tex4 = texture2DRect(tex, gl_TexCoord[0].st + vec2(0.5, 1.0 + scroll));
	
	vec4 texOut = texture2DRect(tex, gl_TexCoord[0].st + bleedVec); // out
	vec4 texIn = texture2DRect(tex, gl_TexCoord[0].st - bleedVec); // in
	
	float minFl = min(min(min(tex1.r, tex2.r), tex3.r), tex4.r); 
	
	//blur
	float aveFl = (tex0.r + tex1.r + tex2.r + tex3.r + tex4.r) / 5.0;
	float aveFi = (tex0.g + tex1.g + tex2.g + tex3.r + tex4.g) / 5.0;
	
	float fl = tex0.r;
	float fi = tex0.g;
	
	fl = mix(fl, aveFl, 0.8);
	fi = mix(fi, aveFi, 0.02);
	
	//flow
	float flow = 0.21;
	fl = min(1.0, fl + min(flow, texIn.r) * length(bleedVec));
	fl = max(0.0, fl - flow  * length(bleedVec));

	// dry
	fl = max(0.0, fl - ((minFl == 0.0) ? 0.005   : 0.003));
	fi = max(0.0, fi - ((fl == 0.0) ? 0.001  : -fl * 0.002));
	
	gl_FragColor = vec4(fl, fi ,0.0, 1.0);
}