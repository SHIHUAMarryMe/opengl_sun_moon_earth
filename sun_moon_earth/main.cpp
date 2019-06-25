
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>


#include "shader_creator.h"
#include "vertex_creator.h"

static constexpr const int WIDTH{ 800 };
static constexpr const int HEIGHT{ 600 };

static constexpr const char* sphereVertexShaderSource
{
"#version 330\n"
"layout(location = 0) in vec3 Position;\n"
"uniform mat4 gWVP;\n"
"void main()\n"
"{\n"
"	gl_Position = gWVP * vec4(Position, 1.0);\n"
"}"
};

static constexpr const char* sphereFragmentShaderSource
{
"#version 330\n"
"out vec3 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec3(1.0, 0.0, 0.0);\n"
"}"
};

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


int main()
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Sphere", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//glfw: callbacks.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global OpenGL state.
	glEnable(GL_DEPTH_TEST); //depth testing.


	ShaderCreator earthShader{};
	earthShader.createShadersAndLink(sphereVertexShaderSource, sphereFragmentShaderSource);


	const std::vector<float>& earth_vertexes = VertexCreator::getSephereVertexPos(19, 18, 5.0f);

	GLuint earthVAO{};
	GLuint earthVBO{};

	glGenVertexArrays(1, &earthVAO);
	glGenBuffers(1, &earthVBO);

	glBindVertexArray(earthVAO);

	glBindBuffer(GL_ARRAY_BUFFER, earthVBO);
	glBufferData(GL_ARRAY_BUFFER, earth_vertexes.size() * sizeof(float), &earth_vertexes[0], GL_STATIC_DRAW);


}