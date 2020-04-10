#version 150

// Passed from our vert shader
in vec3 vecNormal;
in vec3 vecPosition;

// What we send out
out vec4 fragColor;

// this is set in the OF app
uniform vec3 u_materialColor;
uniform vec2 u_resolution;
uniform float u_offset;
uniform float u_amplitude;
uniform float u_time;

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main(){
    // This is where the light is
    vec3 light = vec3(.5, 0.5, 1.);
    light = normalize(light);
    
    // dot product
    // make the minimum 0.6 so we get *some* light everywhere
    float dProd = max(.6, dot(vecNormal, light));
    
    //color
    float normalizedPosition = max(0.0, ((vecPosition.z - u_offset) * 1.5)/u_amplitude);
    normalizedPosition = map(normalizedPosition, 0.0, 1.0, 0.6, 1.0);
    vec3 materialColor = u_materialColor * normalizedPosition;
    vec4 color = vec4(materialColor.r, materialColor.g, materialColor.b, 1.0);
    vec4 col = vec4(vec3(dProd) * vec3(color), 1.);
    fragColor = color;
}
