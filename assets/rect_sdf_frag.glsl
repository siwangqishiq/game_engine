precision highp float;

uniform vec2 uSize;
uniform vec4 uColor;
uniform vec2 uRectPos;
uniform vec2 uRectSize;

out vec4 FragColor;

const float AA_SIZE = 4.0f; //Anti Alitas

float sdRect(vec2 p , vec2 rectSize){
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

void main(){
    vec2 pos = gl_FragCoord.xy;
    float alphaValue = sdRect(pos - uRectPos.xy , uRectSize);
    alphaValue = (1.0f - smoothstep(0.0f - AA_SIZE, 0.0f + AA_SIZE , alphaValue));
    FragColor = vec4(uColor.rgb , uColor.a * alphaValue);
}
