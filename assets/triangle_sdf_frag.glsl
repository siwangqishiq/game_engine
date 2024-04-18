precision highp float;

uniform vec2 uSize;
uniform vec4 uColor;

uniform vec2 uP1;
uniform vec2 uP2;
uniform vec2 uP3;

out vec4 FragColor;

const float AA_SIZE = 4.0f; //Anti Alitas

const float eps = 0.01f;

bool isFloatEqual(float v1 , float v2){
    return abs(v1 - v2) < eps;
}

bool isFloatLarger(float v1 , float v2){
    return v1 - v2 > eps;
}

float sdSegment(vec2 q , vec2 p1 , vec2 p2){
    vec2 p1_p2 = p2 - p1;
    vec2 p1_q = q - p1;
    return length(clamp(dot(p1_q , p1_p2) / dot(p1_p2 , p1_p2) , 0.0f , 1.0f) * p1_p2 - p1_q );
}

float triArea(vec2 p , vec2 p1 , vec2 p2){
    vec2 p1p = p - p1;
    vec2 p1p2 = p2 - p1;
    vec2 p1h = p1p2 * (dot(p1p , p1p2) / dot(p1p2 , p1p2));
    vec2 ph = p1h - p1p;
    return length(ph) * length(p1p2) / 2.0f;
}

float isInTriangle(vec2 p ,vec2 p1 , vec2 p2 , vec2 p3){
    float s = triArea(p1 , p2 , p3);
    float s3 = triArea(p , p1 , p2);
    float s2 = triArea(p , p1 , p3);
    float s1 = triArea(p , p2 , p3);
    return sign(s1 + s2 + s3 - s - eps);
}

float sdTriangle(vec2 p ,vec2 p1 , vec2 p2 , vec2 p3){
    vec2 ab = p2 - p1;
    vec2 bc = p3 - p2;
    float s = isInTriangle(p , p1 , p2 , p3);
    float d1 = s * sdSegment(p , p1 , p2);
    float d2 = s * sdSegment(p , p1 , p3);
    float d3 = s * sdSegment(p , p2 , p3);
    return min(min(d1 , d2) , min(d2 , d3));
}

void main(){
    vec2 pos = gl_FragCoord.xy;
    float alphaValue = sdTriangle(pos , uP1 , uP2 , uP3);
    // FragColor = vec4(uColor.rgb , uColor.a * alphaValue);
    alphaValue = (1.0f - smoothstep(0.0f - AA_SIZE, 0.0f + AA_SIZE , alphaValue));
    FragColor = vec4(uColor.rgb , uColor.a * alphaValue);
}
