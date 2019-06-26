
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_creator.h"
#include "vertex_creator.h"

static constexpr const int WIDTH{800};
static constexpr const int HEIGHT{600};

static constexpr const char *vertexShaderSource{
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"uniform mat4 transform;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = transform * vec4(aPos, 1.0f);\n"
	//"   gl_Position = vec4(aPos, 1.0f);\n"

	"}"};

static constexpr const char *fragmentShaderSource{
	"#version 330 core\n"
	"out vec4 fragmentColor;\n"
	"void main()\n"
	"{\n"
	"   fragmentColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}"};

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

static void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
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
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Sphere", nullptr, nullptr);
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
	//glEnable(GL_DEPTH_TEST); //depth testing.

	ShaderCreator earthShader{};
	earthShader.createShadersAndLink(vertexShaderSource, fragmentShaderSource);

	const std::vector<float> earthVertexesData{VertexCreator::getSephereVertexPos(50, 50, 0.5f)};

	GLuint earthVAO{};
	GLuint earthVBO{};

	glGenVertexArrays(1, &earthVAO);
	glGenBuffers(1, &earthVBO);

	glBindVertexArray(earthVAO);

	glBindBuffer(GL_ARRAY_BUFFER, earthVBO);
	glBufferData(GL_ARRAY_BUFFER, earthVertexesData.size() * sizeof(float), earthVertexesData.data(), GL_STATIC_DRAW);

	std::size_t offset{0};
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void *>(offset));
	glEnableVertexAttribArray(0);

	//just draw lines.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// create transformations
		glm::mat4 transform(1.0f); // make sure to initialize matrix to identity matrix first
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 5.0f, 1.0f));

		// draw our first triangle
		glUseProgram(earthShader.getProgramId());
		GLint transformLoc{glGetUniformLocation(earthShader.getProgramId(), "transform")};
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		glBindVertexArray(earthVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, earthVertexesData.size() / 3);
		// glBindVertexArray(0); // no need to unbind it every time

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &earthVAO);
	glDeleteBuffers(1, &earthVBO);

	glfwTerminate();

	return 0;
}