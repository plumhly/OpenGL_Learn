#version 410 core

in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 viewPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;
in vec2 texCoords;

struct DirectionLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirectionLight dirLight;

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_POINT_LIGHT 4
uniform PointLight pointLights[NR_POINT_LIGHT];

struct SpotLight {
    vec3 direction;
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
    
    float cutOff;
    float outerCutOff;
};

uniform SpotLight spotLight;

vec3 calculateDirLight(DirectionLight light, vec3 normal, vec3 viewDir);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {

    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);

    // 定向光
    vec3 result = calculateDirLight(dirLight, norm, viewDir);

    // 点光源
    for(int i = 0; i < NR_POINT_LIGHT; i++){
        result += calculatePointLight(pointLights[i], norm, fragPos, viewDir);
    }

    // 聚光
    result += calculateSpotLight(spotLight, norm, fragPos, viewDir);

    FragColor = vec4(result, 1.0);
}


vec3 calculateDirLight(DirectionLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    //漫反射
    float diff = max(dot(normal, lightDir), 0.0);

    // 镜面光
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    vec3 ambient = vec3(texture(material.diffuse, texCoords)) * light.ambient;
    vec3 diffuse = (diff * vec3(texture(material.diffuse, texCoords))) * light.diffuse;
    vec3 specular = (spec * vec3(texture(material.specular, texCoords))) * light.specular;

    return ambient + diffuse + specular;
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    
    // 漫反射
    float diff = max(dot(normal, lightDir), 0.0);

    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // 衰减
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // 合并
    vec3 ambient = vec3(texture(material.diffuse, texCoords)) * light.ambient;
    vec3 diffuse = (diff * vec3(texture(material.diffuse, texCoords))) * light.diffuse;
    vec3 specular = (spec * vec3(texture(material.specular, texCoords))) * light.specular;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}

vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    
    // 漫反射
    float diff = max(dot(normal, lightDir), 0.0);

    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // 衰减
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // 聚光
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // 合并
    vec3 ambient = vec3(texture(material.diffuse, texCoords)) * light.ambient;
    vec3 diffuse = (diff * vec3(texture(material.diffuse, texCoords))) * light.diffuse;
    vec3 specular = (spec * vec3(texture(material.specular, texCoords))) * light.specular;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    ambient *= intensity;
    diffuse *= intensity;
    specular *= intensity;

    return ambient + diffuse + specular;
}
