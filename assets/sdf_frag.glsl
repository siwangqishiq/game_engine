precision highp float;

uniform vec2 uSize;

out vec4 FragColor;

float sdCircle(vec2 pos , float radius){
    return length(pos) - radius;
}

void main(){
    // vec2 pos = gl_FragCoord.xy;
    // float alpha = pos.x / uSize.x;
    // FragColor = vec4(1.0f , 0.0f , 0.0f , alpha);
    discard;
}