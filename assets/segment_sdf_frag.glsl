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
    float r = dot(p1_q , p1_p2) / dot(p1_p2 , p1_p2);
    vec2 d = r * p1_p2 - p1_q;
    float mid_len = length(d);
    float p1_q_len = length(p1_q);
    float p2_q_len = distance(p2 , q);
    float stepV1 = step(0.0f, r);
    float stepV2 = step(1.0f, r);

    return p1_q_len * (1.0f - stepV1) +
                mid_len * stepV1 * (1.0f - stepV2) + 
                p2_q_len * stepV2;
}

void main(){
    vec2 pos = gl_FragCoord.xy;
    vec2 center = uSize / 2.0f;
    float alphaValue = sdSegment(pos , uP1 , uP2);
    FragColor = vec4(uColor.rgb , 
        uColor.a * (1.0f - smoothstep(0.0f - AA_SIZE, 0.0f + AA_SIZE , alphaValue)));
}
