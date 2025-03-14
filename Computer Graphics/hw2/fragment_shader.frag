#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light lights[3];
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    vec3 ambient = vec3(texture(texture1, TexCoords)) * material.ambient;
    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = ambient;
    for (int i = 0; i < 3; i++) {
        vec3 lightDir = normalize(lights[i].position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = lights[i].diffuse * diff * vec3(texture(texture1, TexCoords));
        
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = lights[i].specular * spec * vec3(texture(texture2, TexCoords));
        
        result += (diffuse + specular);
    }
    
    FragColor = vec4(result, 1.0);
}
