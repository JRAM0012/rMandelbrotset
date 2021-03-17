#version 100
    #ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
#else
    precision mediump float;
#endif

uniform vec2 resolution;
uniform vec2 location;
uniform float zoom;
uniform float vec4_1;
uniform float vec4_2;
uniform float vec4_3;
uniform float vec4_4;
uniform int maxIter;

vec2 compsquare(vec2 z)
{
    float temp = z.x;
    z.x = z.x * z.x - z.y * z.y;
    z.y = 2.0 * temp * z.y;
    return z;
}

vec3 hsv2rgb(vec3 hue){
    vec4 K = vec4(vec4_1, vec4_2, vec4_3, vec4_4);
    vec3 p = abs(fract(hue.xxx + K.xyz) * 6.0 - K.www);
    return hue.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), hue.y);
}

vec3 mandelbort(vec2 point){
    vec2 z = vec2(0.0);
    float iters = 0.0;
    for (iters = 0.0;   iters < float(maxIter); ++iters)
    {
        z = compsquare(z) + point;
        if(dot(z, z) > 4.0) break;
    }
    float hue = iters / float(maxIter);
    if(hue > 0.98) return vec3(0.0);
    return hsv2rgb(vec3(hue, 1.0, 1.0));
}

void main()
{
    vec2 uv = gl_FragCoord.xy / resolution;
    uv.x *= resolution.x / resolution.y;
    uv -= vec2(0.7, 0.5);
    // uv.x -= 0.5;
    uv *= zoom;
    uv -= location;
    gl_FragColor = vec4(mandelbort(uv), 1.0);
    // gl_FragColor = vec4(uv, 1.0, 1.0);
}