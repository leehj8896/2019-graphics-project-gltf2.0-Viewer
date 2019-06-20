#version 120                  // GLSL 1.20

uniform sampler2D u_diffuse_texture;

uniform vec3 u_view_position_wc;
uniform vec3 u_light_position_wc;

uniform vec4 u_light_diffuse;
uniform vec4 u_light_specular;

uniform vec4 u_material_specular;
uniform float u_material_shininess;

varying vec3 v_position_wc;
varying vec3 v_normal_wc;
varying vec2 v_texcoord;

vec4 calc_color()
{
  vec4 color = vec4(0.0);

  vec3 n_wc = normalize(v_normal_wc);
  vec3 l_wc = normalize(u_light_position_wc - v_position_wc);
  vec3 r_wc = reflect(-l_wc, n_wc);
  vec3 v_wc = u_view_position_wc;

  vec4 material_diffuse = texture2D(u_diffuse_texture, v_texcoord);
      
  float ndotl = max(0.0, dot(n_wc, l_wc));
  color += (ndotl * u_light_diffuse * material_diffuse);

  float rdotv = max(0.0, dot(r_wc, v_wc) );
  color += (pow(rdotv, u_material_shininess) * u_light_specular * u_material_specular);

  return color;
}

void main()
{
    gl_FragColor = calc_color();	
}