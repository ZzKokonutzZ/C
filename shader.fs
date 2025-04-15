#version 450
uniform vec2 resolution; 
out vec4 fragColor;
uniform float time;
void main() {
    vec2 uv = gl_FragCoord.xy/resolution;
    uv=2*uv-1;
    uv.x=uv.x*resolution.x/resolution.y;
    float r=abs(sin(5*3.14*length(uv)-5*time));
    float g=abs(sin(5*3.14*length(uv)-6*time));
    float b=abs(sin(5*3.14*length(uv)-7*time));
    float a=abs(sin(5*3.14*length(uv)-8*time));
    fragColor=vec4(vec3,1.0);
}