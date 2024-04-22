precision highp float;
precision highp sampler2DArray;

out vec4 outColor;

in vec3 vUvw;
uniform sampler2DArray sdfTexture;
// uniform vec4 textColor;

void main(){
    vec3 color = vec3(0.0f ,0.0f , 0.0f);
    float fontAlpha = texture(sdfTexture , vec3(vUvw.x , vUvw.y , vUvw.z)).r;
    outColor = vec4(color, 1.0f * (fontAlpha));
}
