#include <iostream>
#include <cstdlib>
#include <chrono>
#include "imgui/imgui.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "Ditherer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

static const int START_WINDOW_WIDTH = 500;
static const int START_WINDOW_HEIGHT = 700;

int main(int argc, char* argv[])
{
	// init opengl
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(START_WINDOW_WIDTH, START_WINDOW_HEIGHT, "Ditherer", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// init imgui
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// create ditherer
	std::vector<std::unique_ptr<Dithering::IDitherer>> ditherers((int)Dithering::Ditherer::COUNT);
	ditherers[0].reset(new Dithering::JJNDitherer(true));

	std::vector<const char*> ditherers_names((int)Dithering::Ditherer::COUNT);
	for (int i = 0; i < (int)Dithering::Ditherer::COUNT; ++i)
	{
		ditherers_names[i] = ditherers[i]->get_name().c_str();
	}

	// prepare for loop
	auto current_ditherer_id = 0;
	auto current_palette_id = 0;
	char input_file_path[256];
	input_file_path[0] = '\0';
	char output_file_path[256];
	output_file_path[0] = '\0';
	auto current_threads_count = 1;
	std::string dither_time = "Dithering took: 0 milliseconds";

	std::vector<const char*> palettes_names(ditherers[current_ditherer_id]->get_palettes_count());
	{
		const auto& current_ditherer_palettes_names = ditherers[current_ditherer_id]->get_palettes_names();
		for (int i = 0; i < (int)current_ditherer_palettes_names.size(); ++i)
		{
			palettes_names[i] = current_ditherer_palettes_names[i].c_str();
		}
	}

	// main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		processInput(window);

		ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2((float)START_WINDOW_WIDTH, (float)START_WINDOW_HEIGHT), ImGuiCond_Always);

		ImGui::Begin("Ditherer", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize);

		ImGui::Text("Choose ditherer");
		if (ImGui::ListBox("Ditherer", &current_ditherer_id, ditherers_names.data(), (int)ditherers_names.size()))
		{
			palettes_names.resize(ditherers[current_ditherer_id]->get_palettes_count());
			const auto& current_ditherer_palettes_names = ditherers[current_ditherer_id]->get_palettes_names();
			for (int i = 0; i < current_ditherer_palettes_names.size(); ++i)
			{
				palettes_names[i] = current_ditherer_palettes_names[i].c_str();
			}
		}

		ImGui::Text("Choose palette");
		ImGui::ListBox("Palette", &current_palette_id, palettes_names.data(), (int)palettes_names.size());

		ImGui::Text("Choose files");
		ImGui::InputText("Input file", input_file_path, 100);
		ImGui::InputText("Output file", output_file_path, 100);

		ImGui::Text("Threads count");
		ImGui::InputInt("Input threads count", &current_threads_count, 1, 5);
		current_threads_count = std::clamp(current_threads_count, 1, 128);

		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::Button("Dither"))
		{
			try
			{
				Dithering::Image input_image;

				if (!input_image.openImage(input_file_path))
				{
					break;
				}

				auto rows = 0;
				auto columns = 0;
				input_image.getSize(rows, columns);

				Dithering::Image output_image;
				if (!output_image.createImage(output_file_path, rows, columns))
				{
					break;
				}

				const auto start_time = std::chrono::high_resolution_clock::now();

				if (!ditherers[current_ditherer_id]->process(input_image, output_image, current_palette_id, current_threads_count))
				{
					break;
				}

				dither_time = "Dithering took: " +
					std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count()) +
					" milliseconds";

				output_image.saveImage();
			}
			catch (...)
			{
				std::cout << "There was error while dithering" << std::endl;
				dither_time = "Dithering took: 0 milliseconds";
			}
		}

		ImGui::Text(dither_time.c_str());

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, 1);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}