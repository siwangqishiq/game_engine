precision highp float;

uniform vec2 uSize;
uniform vec4 uColor;

out vec4 FragColor;

const float AA_SIZE = 4.0f; //Anti Alitas

float smin(float a,float b,float k){
    float h = clamp(0.5+0.5*(a-b)/k,0.0,1.0);
    return mix(a,b,h)-k*h*(1.0-h);
}

float smax(float a,float b,float k){
    return -smin(-a,-b,k);
}

float diff(float a , float b){
    return -min(a , -b);
}

float sdiff(float a , float b , float k){
    return -smin(a , -b , k);
}

float sdCircle(vec2 p, vec2 center, float radius){
    return (length(p - center) - radius);
}

float sdRect(vec2 p ,vec2 rectPos , vec2 rectSize){
    float half_width = rectSize.x / 2.0f;
    float half_height = rectSize.y / 2.0f;
    vec2 absP = vec2(abs(p.xy));
    
    float dx = absP.x - half_width;
    float dy = absP.y - half_height;

    float dxClamped = max(dx, 0.0);
    float dyClamped = max(dy, 0.0);
    float distanceInside = length(vec2(dxClamped, dyClamped));
    float distanceOutside = min(max(dx, dy), 0.0);
    return distanceInside + distanceOutside;
}

float opSdfUnion(vec2 p){
    vec2 center = uSize / 2.0f;
    float radius = uSize.y / 4.0f;
    vec2 c1 = center + vec2(radius / 2.0f , 0.0f);
    float sd = sdCircle(p , c1 , radius);

    vec2 c2 = center + vec2(-radius / 2.0f , 0.0f);
    float sd2 = sdCircle(p , c2 , radius);
    sd = min(sd , sd2);
    return sd;
}

float opSdfIntersection(vec2 p){
    vec2 center = uSize / 2.0f;
    float radius = uSize.y / 4.0f;
    vec2 c1 = center + vec2(radius / 2.0f , 0.0f);
    float sd = sdCircle(p , c1 , radius);

    vec2 c2 = center + vec2(-radius / 2.0f , 0.0f);
    float sd2 = sdCircle(p , c2 , radius);
    sd = max(sd , sd2);
    return sd;
}

float opSdfDiff(vec2 p){
    vec2 center = uSize / 2.0f;
    float radius = uSize.y / 4.0f;
    vec2 c1 = center + vec2(radius / 2.0f , 0.0f);
    float sd = sdCircle(p , c1 , radius);

    vec2 c2 = center + vec2(-radius / 2.0f , 0.0f);
    float sd2 = sdCircle(p , c2 , radius);
    sd = diff(sd , sd2);
    return sd;
}

void main(){
    vec2 pos = gl_FragCoord.xy;
    // float alphaValue = opSdfUnion(pos);
    // float alphaValue = opSdfIntersection(pos);
    float alphaValue = opSdfDiff(pos);

    alphaValue = (1.0f - smoothstep(0.0f - AA_SIZE, 0.0f + AA_SIZE , alphaValue));
    FragColor = vec4(uColor.rgb , uColor.a * alphaValue);
}
