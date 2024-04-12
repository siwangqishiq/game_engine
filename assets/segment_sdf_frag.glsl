precision highp float;

uniform vec2 uSize;
uniform vec4 uColor;

uniform vec2 uP1;
uniform vec2 uP2;

out vec4 FragColor;

const float AA_SIZE = 4.0f; //Anti Alitas

float sdSegment(vec2 q , vec2 p1 , vec2 p2){
    vec2 p1_p2 = p2 - p1;
    vec2 p1_q = q - p1;
    return length(clamp(dot(p1_q , p1_p2) / dot(p1_p2 , p1_p2) , 0.0f , 1.0f) * p1_p2 - p1_q );
}

void main(){
    vec2 pos = gl_FragCoord.xy;
    vec2 center = uSize / 2.0f;
    float alphaValue = sdSegment(pos , uP1 , uP2);
    FragColor = vec4(uColor.rgb , 
        uColor.a * (1.0f - smoothstep(0.0f - AA_SIZE, 0.0f + AA_SIZE , alphaValue)));
}
