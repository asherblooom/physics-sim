#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

void main() {
    color = vec4(spriteColor, 1.0);
}

// // uniform vec2 resolution;
// uniform vec3 spriteColor;
// // uniform float radius; ??? is this provided by transformations??
// in vec2 TexCoords;
// out vec4 fragColor;
//
// vec4 circleColor(in vec2 texCoord, in float radius){
//     float disty = length(texCoord - vec2(0.5));
// 	float dist = disty / fwidth(disty);
//
// 	// Use screenspace derivatives to compute how quickly this value changes
// 	// as we move one pixel left or right / up or down:
//
// 	// dist (dot) dist = length(dist)^2 (but faster than calculating length using sqrt)
// 	float color = 1.0 - smoothstep(radius - (radius * 0.03), radius + (radius * 0.03), disty);
//
// 	float alpha = 0.0;
//     if (color > 0){
//         alpha = 1.0;
//     }
// 	return vec4(color, color, color, alpha);
// }
//
// // void main(){
// // 	// tex coords s and t
// // 	// vec2 st = gl_FragCoord.xy / resolution.xy;
// // 	vec2 st = TexCoords;
// //
// // 	fragColor = circleColor(st, 0.5) * vec4(spriteColor, 1.0);
// // }
// void main(){
// 	float R = 1.0;
//     float R2 = 0.5;
//     float dist = length(TexCoords - vec2(0.5));
//     if (dist >= R || dist <= R2) {
//         discard;
//     }
//     float sm = smoothstep(R,R-0.01,dist);
//     float sm2 = smoothstep(R2,R2+0.01,dist);
//     float alpha = sm*sm2;
//     gl_FragColor = vec4(0.0, 0.0, 1.0, alpha);
// }
