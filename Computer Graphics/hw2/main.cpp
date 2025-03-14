 #define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stb_image.h>

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path);
void renderScene(GLuint shaderProgram, std::vector<unsigned int>& VAOs, unsigned int texture1, unsigned int texture2);
void createSphere(std::vector<float>& vertices, float radius, unsigned int rings, unsigned int sectors);
void createCylinder(std::vector<float>& vertices, float radius, float height, unsigned int sectors);
bool checkCollision(glm::vec3 pos1, glm::vec3 size1, glm::vec3 pos2, glm::vec3 size2);

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const glm::vec3 WORLD_BOUNDS_MIN = glm::vec3(-5.0f, -5.0f, -5.0f);
const glm::vec3 WORLD_BOUNDS_MAX = glm::vec3(5.0f, 5.0f, 5.0f);
std::vector<float> sphereVertices;
std::vector<float> cylinderVertices;
// Camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float lastX = SCR_WIDTH / 2.0;
float lastY = SCR_HEIGHT / 2.0;
float yaw = -90.0f;
float pitch = 0.0f;
float fov = 45.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// Light properties
// Lighting
struct Light {
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;
    bool isDirectional;
    bool isPoint;
};

std::vector<Light> lights = {
    {glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, true, false},
    {glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, false, true},
    {glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, false, true}
};

// Material properties
struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

Material materials[4] = {
    {glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f},
    {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 64.0f},
    {glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.3f, 0.3f, 0.3f), 16.0f},
    {glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.1f, 0.1f, 0.1f), 8.0f}
};

int main() {
    // Initialize and configure GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Assignment", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    // Configure global OpenGL state
    glEnable(GL_DEPTH_TEST);

    // Build and compile our shader program
    GLuint shaderProgram = loadShaders("vertex_shader.vert", "fragment_shader.frag");

    // Set up vertex data, buffers, and configure vertex attributes
    float cubeVertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f
    };

    // Pyramid vertex data
    float pyramidVertices[] = {
        // positions          // normals           // texture coords
        // Front face
         0.0f,  0.5f,  0.0f,  0.0f,  0.4472f,  0.8944f,  0.5f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.4472f,  0.8944f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.4472f,  0.8944f,  1.0f,  0.0f,

        // Right face
         0.0f,  0.5f,  0.0f,  0.8944f,  0.4472f,  0.0f,  0.5f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.8944f,  0.4472f,  0.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.8944f,  0.4472f,  0.0f,  1.0f,  0.0f,

        // Back face
         0.0f,  0.5f,  0.0f,  0.0f,  0.4472f, -0.8944f,  0.5f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.4472f, -0.8944f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.4472f, -0.8944f,  1.0f,  0.0f,

        // Left face
         0.0f,  0.5f,  0.0f, -0.8944f,  0.4472f,  0.0f,   0.5f,  1.0f,
        -0.5f, -0.5f, -0.5f, -0.8944f,  0.4472f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -0.8944f,  0.4472f,  0.0f,  1.0f,  0.0f
    };

    createSphere(sphereVertices, 0.5f, 20, 20);
    createCylinder(cylinderVertices, 0.5f, 1.0f, 20);

    // VAO and VBO setup
    std::vector<unsigned int> VAOs(5), VBOs(5);
    glGenVertexArrays(5, VAOs.data());
    glGenBuffers(5, VBOs.data());

    // Cube VAO
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Pyramid VAO
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertices), pyramidVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Sphere VAO
    glBindVertexArray(VAOs[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(float), sphereVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Cylinder VAO
    glBindVertexArray(VAOs[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
    glBufferData(GL_ARRAY_BUFFER, cylinderVertices.size() * sizeof(float), cylinderVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Second Sphere VAO
    glBindVertexArray(VAOs[4]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[4]);
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(float), sphereVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Load and create textures
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char *data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("specular.jpeg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // Set texture units
    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        processInput(window);

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Change the background color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader program
        glUseProgram(shaderProgram);

        // Set up the view and projection matrices
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Bind textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // Render the scene
        renderScene(shaderProgram, VAOs, texture1, texture2);

        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up and exit
    glDeleteVertexArrays(5, VAOs.data());
    glDeleteBuffers(5, VBOs.data());
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}

// Process all input
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5f * deltaTime;
    glm::vec3 newPos = cameraPos;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        newPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        newPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        newPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        newPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        newPos += cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        newPos -= cameraSpeed * cameraUp;

    // Check boundaries
    if (newPos.x >= WORLD_BOUNDS_MIN.x && newPos.x <= WORLD_BOUNDS_MAX.x &&
        newPos.y >= WORLD_BOUNDS_MIN.y && newPos.y <= WORLD_BOUNDS_MAX.y &&
        newPos.z >= WORLD_BOUNDS_MIN.z && newPos.z <= WORLD_BOUNDS_MAX.z) {
        // Check for collisions with objects
        std::vector<glm::vec3> objectPositions = {
            glm::vec3(0.0f, 0.0f, 0.0f),  // Cube position
            glm::vec3(2.0f, 0.0f, 0.0f),  // Another Cube position
            glm::vec3(2.0f, 1.5f, 0.0f),  // Pyramid position
            glm::vec3(0.0f, 2.0f, -2.0f), // Cylinder position
            glm::vec3(-1.5f, 0.0f, 1.5f)  // Sphere position
        };

        glm::vec3 objectSize = glm::vec3(1.0f); // Approximate size for all objects
        bool collisionDetected = false;

        for (const auto& pos : objectPositions) {
            if (checkCollision(newPos, glm::vec3(0.5f), pos, objectSize)) {
                collisionDetected = true;
                break;
            }
        }

        if (!collisionDetected) {
            cameraPos = newPos;
        }
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}

GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path) {
    // Read vertex shader code from file
    std::string vertexCode;
    std::ifstream vertexShaderFile(vertex_file_path);
    if (vertexShaderFile) {
        std::stringstream vertexShaderStream;
        vertexShaderStream << vertexShaderFile.rdbuf();
        vertexShaderFile.close();
        vertexCode = vertexShaderStream.str();
    } else {
        std::cerr << "ERROR::SHADER::VERTEX::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return 0;
    }

    // Read fragment shader code from file
    std::string fragmentCode;
    std::ifstream fragmentShaderFile(fragment_file_path);
    if (fragmentShaderFile) {
        std::stringstream fragmentShaderStream;
        fragmentShaderStream << fragmentShaderFile.rdbuf();
        fragmentShaderFile.close();
        fragmentCode = fragmentShaderStream.str();
    } else {
        std::cerr << "ERROR::SHADER::FRAGMENT::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return 0;
    }

    // Compile shaders
    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Check for compile-time errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Check for compile-time errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void renderScene(GLuint shaderProgram, std::vector<unsigned int>& VAOs, unsigned int texture1, unsigned int texture2) {
    // Bind textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // Set material properties
    glUniform3fv(glGetUniformLocation(shaderProgram, "material.ambient"), 1, glm::value_ptr(materials[0].ambient));
    glUniform3fv(glGetUniformLocation(shaderProgram, "material.diffuse"), 1, glm::value_ptr(materials[0].diffuse));
    glUniform3fv(glGetUniformLocation(shaderProgram, "material.specular"), 1, glm::value_ptr(materials[0].specular));
    glUniform1f(glGetUniformLocation(shaderProgram, "material.shininess"), materials[0].shininess);

    // Set light properties
    for (int i = 0; i < lights.size(); ++i) {
        glUniform3fv(glGetUniformLocation(shaderProgram, ("lights[" + std::to_string(i) + "].position").c_str()), 1, glm::value_ptr(lights[i].position));
        glUniform3fv(glGetUniformLocation(shaderProgram, ("lights[" + std::to_string(i) + "].ambient").c_str()), 1, glm::value_ptr(lights[i].ambient));
        glUniform3fv(glGetUniformLocation(shaderProgram, ("lights[" + std::to_string(i) + "].diffuse").c_str()), 1, glm::value_ptr(lights[i].diffuse));
        glUniform3fv(glGetUniformLocation(shaderProgram, ("lights[" + std::to_string(i) + "].specular").c_str()), 1, glm::value_ptr(lights[i].specular));
    }

    // Render cube and its copies
    for (int i = 0; i < 3; ++i) {
        glBindVertexArray(VAOs[0]);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(i * 1.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // Render pyramid and its copies
    for (int i = 0; i < 3; ++i) {
        glBindVertexArray(VAOs[1]);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, i * 1.5f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 12);
    }

    // Render first sphere
    glBindVertexArray(VAOs[2]);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 1.5f));
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, sphereVertices.size() / 8);

    // Render cylinder
    glBindVertexArray(VAOs[3]);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 2.0f, -2.0f));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, cylinderVertices.size() / 8);

    // Render second sphere rotating around the cube
    glBindVertexArray(VAOs[4]);
    model = glm::mat4(1.0f);
    float angle = (float)glfwGetTime() * glm::radians(50.0f);
    float radius = 2.0f;
    float x = cos(angle) * radius;
    float z = sin(angle) * radius;
    model = glm::translate(model, glm::vec3(x, 0.0f, z));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, sphereVertices.size() / 8);

    // Unbind VAO
    glBindVertexArray(0);
}

void createSphere(std::vector<float>& vertices, float radius, unsigned int rings, unsigned int sectors) {
    float const R = 1.0f / (float)(rings - 1);
    float const S = 1.0f / (float)(sectors - 1);
    int r, s;

    for (r = 0; r < rings; r++) {
        for (s = 0; s < sectors; s++) {
            float const y = sin(-M_PI_2 + M_PI * r * R);
            float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
            float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

            vertices.push_back(x * radius);
            vertices.push_back(y * radius);
            vertices.push_back(z * radius);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            vertices.push_back(s * S);
            vertices.push_back(r * R);
        }
    }

    std::vector<unsigned int> indices;
    for (r = 0; r < rings - 1; r++) {
        for (s = 0; s < sectors; s++) {
            indices.push_back(r * sectors + s);
            indices.push_back(r * sectors + (s + 1));
            indices.push_back((r + 1) * sectors + (s + 1));

            indices.push_back(r * sectors + s);
            indices.push_back((r + 1) * sectors + (s + 1));
            indices.push_back((r + 1) * sectors + s);
        }
    }

    std::vector<float> newVertices;
    for (unsigned int i = 0; i < indices.size(); i++) {
        newVertices.push_back(vertices[indices[i] * 8 + 0]);
        newVertices.push_back(vertices[indices[i] * 8 + 1]);
        newVertices.push_back(vertices[indices[i] * 8 + 2]);
        newVertices.push_back(vertices[indices[i] * 8 + 3]);
        newVertices.push_back(vertices[indices[i] * 8 + 4]);
        newVertices.push_back(vertices[indices[i] * 8 + 5]);
        newVertices.push_back(vertices[indices[i] * 8 + 6]);
        newVertices.push_back(vertices[indices[i] * 8 + 7]);
    }
    vertices = newVertices;
}

void createCylinder(std::vector<float>& vertices, float radius, float height, unsigned int sectors) {
    float const S = 1.0f / (float)(sectors - 1);
    int s;

    for (s = 0; s < sectors; s++) {
        float const x = cos(2 * M_PI * s * S);
        float const z = sin(2 * M_PI * s * S);

        vertices.push_back(x * radius);
        vertices.push_back(height / 2.0f);
        vertices.push_back(z * radius);

        vertices.push_back(x);
        vertices.push_back(0.0f);
        vertices.push_back(z);

        vertices.push_back(s * S);
        vertices.push_back(0.0f);

        vertices.push_back(x * radius);
        vertices.push_back(-height / 2.0f);
        vertices.push_back(z * radius);

        vertices.push_back(x);
        vertices.push_back(0.0f);
        vertices.push_back(z);

        vertices.push_back(s * S);
        vertices.push_back(1.0f);
    }

    std::vector<unsigned int> indices;
    for (s = 0; s < sectors - 1; s++) {
        indices.push_back(s * 2);
        indices.push_back(s * 2 + 1);
        indices.push_back(s * 2 + 2);

        indices.push_back(s * 2 + 1);
        indices.push_back(s * 2 + 3);
        indices.push_back(s * 2 + 2);
    }

    std::vector<float> newVertices;
    for (unsigned int i = 0; i < indices.size(); i++) {
        newVertices.push_back(vertices[indices[i] * 8 + 0]);
        newVertices.push_back(vertices[indices[i] * 8 + 1]);
        newVertices.push_back(vertices[indices[i] * 8 + 2]);
        newVertices.push_back(vertices[indices[i] * 8 + 3]);
        newVertices.push_back(vertices[indices[i] * 8 + 4]);
        newVertices.push_back(vertices[indices[i] * 8 + 5]);
        newVertices.push_back(vertices[indices[i] * 8 + 6]);
        newVertices.push_back(vertices[indices[i] * 8 + 7]);
    }
    vertices = newVertices;
}

bool checkCollision(glm::vec3 pos1, glm::vec3 size1, glm::vec3 pos2, glm::vec3 size2) {
    bool collisionX = pos1.x + size1.x >= pos2.x && pos2.x + size2.x >= pos1.x;
    bool collisionY = pos1.y + size1.y >= pos2.y && pos2.y + size2.y >= pos1.y;
    bool collisionZ = pos1.z + size1.z >= pos2.z && pos2.z + size2.z >= pos1.z;
    return collisionX && collisionY && collisionZ;
}
