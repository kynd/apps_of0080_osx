uniform sampler2DRect tex;
void main (void){
	vec4 tex0 = texture2DRect(tex, gl_TexCoord[0].st);
	
	
	vec4 tex1 = texture2DRect(tex, gl_TexCoord[0].st + vec2(-1.0, 0.5));
	vec4 tex2 = texture2DRect(tex, gl_TexCoord[0].st + vec2(-0.5, -1.0));
	vec4 tex3 = texture2DRect(tex, gl_TexCoord[0].st + vec2(1.0, -0.5));
	vec4 tex4 = texture2DRect(tex, gl_TexCoord[0].st + vec2(0.5, 1.0));
	
	float dx = tex0.r - tex1.r * -1.0 + tex2.r * -0.5 + tex3.r * 1.0 + tex4.r * 0.5;
	float dy = tex0.r - tex1.r * 0.5 + tex2.r * -1.0 + tex3.r * -0.5 + tex4.r * 1.0;
	vec3 normal = vec3(dx, dy, 1.0);
	normal = normalize(normal);
	
	float a = min(0.1, tex0.g);
	a += tex0.r *0.5;
	float lev = 1.0 - a;
	
	
	
	vec3 lightDir = vec3(0.0, 1.5,1.0);
	vec4 ambientColor = vec4(0.2, 0.2, 0.2, 1.0);
	vec4 diffuseColor = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0);

	float diffuse = max(0.0, dot(normalize(normal), normalize(lightDir)));
	vec4 flagColor = diffuse * diffuseColor;
	flagColor += ambientColor;
	vec3 vReflection = normalize(reflect(-normalize(lightDir), normalize(normal)));
	float specular = pow(max(0.0, dot(normalize(normal), vReflection)), 128.0);
	flagColor += specular * specularColor;
	
	lev = mix(max(flagColor.r, lev), flagColor.r, 0.2); ;
	lev = 1.0 - (1.0 - lev) * 0.6;
	
	gl_FragColor = vec4(lev, lev, lev, 1.0);
}