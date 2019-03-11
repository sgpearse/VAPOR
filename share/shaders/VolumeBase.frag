
#include RayMath.frag

in vec2 ST;
out vec4 fragColor;

uniform mat4 MVP;
uniform vec3 cameraPos;
uniform vec3 dataBoundsMin;
uniform vec3 dataBoundsMax;
uniform vec3 userExtsMin;
uniform vec3 userExtsMax;
uniform float LUTMin;
uniform float LUTMax;
uniform bool hasMissingData;

uniform sampler3D data;
uniform sampler1D LUT;
uniform sampler2D sceneDepth;
uniform sampler3D missingMask;

vec3 lightDir = vec3(0,0,-1);
bool readDepthBuffer = true;


#define ALPHA_BREAK 0.999


vec4 ROYGBV(float v, float minV, float maxV)
{
    vec3 colors[6];
    colors[0] = vec3(1.00, 0.00, 0.00);
    colors[1] = vec3(1.00, 0.60, 0.00);
    colors[2] = vec3(1.00, 1.00, 0.00);
    colors[3] = vec3(0.00, 1.00, 0.00);
    colors[4] = vec3(0.00, 0.00, 1.00);
    colors[5] = vec3(0.32, 0.00, 0.32);
    float ratio = 5.0 * clamp((v-minV)/(maxV-minV), 0, 1);
    int indexMin=int(floor(ratio));
    int indexMax=min(int(indexMin)+1,5);
    vec3 c = mix(colors[indexMin], colors[indexMax], ratio-indexMin);
    return vec4(c, 1);
}

bool DoesSampleHaveMissingData(vec3 dataSTR)
{
    return texture(missingMask, dataSTR).r > 0;
}

bool ShouldRenderSample(const vec3 sampleSTR)
{
    if (hasMissingData)
        if (DoesSampleHaveMissingData(sampleSTR))
            return false;
    return true;
}

float GetDepthBuffer()
{
    if (readDepthBuffer) {
        float depth = texture(sceneDepth, ST).r;
        return depth * 2 - 1; // back to NDC
    } else {
        return 1;
    }
}

#define AMBIENT 0.2
#define DIFFUSE 0.5
#define SPECULAR 0.25
#define SHININESS 8

float PhongLighting(vec3 normal, vec3 viewDir)
{
    float diffuse = abs(dot(normal, -lightDir)) * DIFFUSE;

    float specularStrength = SPECULAR;
    vec3 reflectDir = reflect(lightDir, normal);
    float spec = pow(abs(dot(viewDir, reflectDir)), SHININESS);
    float specular = specularStrength * spec;

    return AMBIENT + diffuse + specular;
}

vec3 GetNormal(vec3 p)
{
    vec3 dims = vec3(textureSize(data, 0));
    vec3 d = 1/dims * 0.5;
    vec3 s0, s1;
    s1.x = texture(data, p + d*vec3(1,0,0)).r;
    s1.y = texture(data, p + d*vec3(0,1,0)).r;
    s1.z = texture(data, p + d*vec3(0,0,1)).r;
    s0.x = texture(data, p - d*vec3(1,0,0)).r;
    s0.y = texture(data, p - d*vec3(0,1,0)).r;
    s0.z = texture(data, p - d*vec3(0,0,1)).r;
    return normalize(s1-s0);
    //return s1-s0;
}

vec4 PremultiplyAlpha(vec4 color)
{
    return vec4(color.rgb * color.a, color.a);
}

// GL_ONE_MINUS_DST_ALPHA, GL_ONE
void BlendToBack(inout vec4 accum, vec4 color)
{
    accum = color * (1-accum.a) + accum * (1);
}

void GetRayParameters(out vec3 dir, out float maxT)
{
	vec2 screen = ST*2-1;
    vec4 world = inverse(MVP) * vec4(screen, GetDepthBuffer(), 1);
    world /= world.w;
    dir = normalize(world.xyz - cameraPos);
    maxT = length(world.xyz - cameraPos);
}
