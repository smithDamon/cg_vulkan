#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

#define APP_NAME
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

void createinstance(VkInstance *instance)
{
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	unsigned int glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;	createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&createInfo, nullptr, instance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create instance!");
	}
}


void initVulkan()
{
	VkInstance instance;
	createinstance(&instance);
}

void initWindow(GLFWwindow **window)
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	*window = glfwCreateWindow(WIN_WIDTH,
		WIN_HEIGHT, "cg vulkan", nullptr, nullptr);

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr,
		&extensionCount, nullptr);

	printf("%d extensions supported\n", extensionCount);

	glm::mat4 matrix;
	glm::vec4 vec;

	auto test = matrix * vec;
}

void mainloop(GLFWwindow *window)
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}

void cleanup(GLFWwindow *window)
{
	initWindow(&window);
	initVulkan();
	glfwDestroyWindow(window);
	glfwTerminate();
}

int main() {
	try {
		GLFWwindow *window;

		initWindow(&window);
		mainloop(window);
		cleanup(window);
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return 0;
}