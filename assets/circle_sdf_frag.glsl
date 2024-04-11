precision highp float;

uniform vec2 uSize;
uniform vec4 uColor;

out vec4 FragColor;

const float aaSize = 8.0f; //Anti Alitas

float sdCircle(vec2 pos , vec2 center, float radius){
    return (length(pos - center) - radius);
}

void main(){
    vec2 pos = gl_FragCoord.xy;
    float radius = min(uSize.x, uSize.y) / 4.0f;
    vec2 center = uSize / 2.0f;
    float alphaValue = sdCircle(pos , center , radius);
    FragColor = vec4(uColor.rgb , 1.0f - smoothstep(0.0f - aaSize, 0.0f + aaSize , alphaValue));
}