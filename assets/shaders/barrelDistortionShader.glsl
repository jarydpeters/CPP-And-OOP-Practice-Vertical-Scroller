#version 330 core
in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D texture1;
uniform float distortionAmount;
uniform vec2 screenSize;

void main() {
    // Barrel distortion code here
    vec2 normalizedCoords = (TexCoord - 0.5) * 2.0;
    float r = length(normalizedCoords);
    float distortion = 1.0 + distortionAmount * (r * r);
    vec2 distortedCoords = normalizedCoords * distortion;
    vec2 uv = distortedCoords * 0.5 + 0.5;

    if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0)
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    else
        FragColor = texture(texture1, uv);
}
