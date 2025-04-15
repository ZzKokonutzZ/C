#version 450
uniform vec2 resolution; 
out vec4 fragColor;
uniform float time;
void main() {
    vec2 uv = gl_FragCoord.xy/resolution;
    uv=2*uv-1;
    float ratio=resolution.x/resolution.y;
    uv.x=uv.x*ratio;
    float r=sin(10*uv.x);
    float g=sin(20*uv.x);
    float b=sin(5*(uv.x-uv.y));
    float a=1.0;
    vec3 col=vec3(r,g,b);
    if (length(col)<1.0) col=vec3(1.0);
    else col=vec3(0.0);
    fragColor=vec4(col,a);
}