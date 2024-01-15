// ----------------------------------------------
// Copyright (c) 2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include <Windows.h>

#include <memory>

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <algorithm>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_stdlib.h>

// =================================================
// Callbacks
// ---

void glfwErrorCallback(int error, const char* description)
{
	//TODO: GlfwErrorCallback
}

static void framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}	
}

// =================================================
// Utilities
// ---

void setIMGUIStyle(float multiplier)
{
	ImGui::StyleColorsDark();

	ImGui::GetStyle().WindowPadding = ImVec2(10*multiplier, 20*multiplier);
	ImGui::GetStyle().FramePadding = ImVec2(10*multiplier, 5*multiplier);
	ImGui::GetStyle().CellPadding = ImVec2(10*multiplier, 5*multiplier);
	ImGui::GetStyle().ItemSpacing = ImVec2(10*multiplier, 5*multiplier);
	ImGui::GetStyle().ItemInnerSpacing = ImVec2(4*multiplier, 4*multiplier);
	ImGui::GetStyle().TouchExtraPadding = ImVec2(2*multiplier, 2*multiplier);
	ImGui::GetStyle().IndentSpacing = 30*multiplier;
	ImGui::GetStyle().ScrollbarSize = 15*multiplier;
	ImGui::GetStyle().GrabMinSize = 11*multiplier;

	ImGui::GetStyle().WindowBorderSize = 0;
	ImGui::GetStyle().ChildBorderSize = 0;
	ImGui::GetStyle().PopupBorderSize = 0;
	ImGui::GetStyle().FrameBorderSize = 0;
	ImGui::GetStyle().TabBorderSize = 0;

	ImGui::GetStyle().WindowRounding = 0;
	ImGui::GetStyle().ChildRounding = 0;
	ImGui::GetStyle().FrameRounding = 2;
	ImGui::GetStyle().PopupRounding = 0;
	ImGui::GetStyle().ScrollbarRounding = 1;
	ImGui::GetStyle().GrabRounding = 2;
	ImGui::GetStyle().LogSliderDeadzone = 2;
	ImGui::GetStyle().TabRounding = 2;

	ImGui::GetStyle().WindowTitleAlign = ImVec2(0.5f, 0.5f);
	ImGui::GetStyle().ButtonTextAlign = ImVec2(0, 0.5f);
	ImGui::GetStyle().SelectableTextAlign = ImVec2(0, 0);

	ImGui::GetStyle().DisplaySafeAreaPadding = ImVec2(3, 1);

	ImFontConfig fontConfig;
	fontConfig.SizePixels = 13 * multiplier;

	ImVec4* colours = ImGui::GetStyle().Colors;
	colours[ImGuiCol_TextDisabled] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
	colours[ImGuiCol_WindowBg] = ImVec4(0.14f, 0.16f, 0.22f, 1.00f);
	colours[ImGuiCol_PopupBg] = ImVec4(0.17f, 0.19f, 0.24f, 1.00f);
	colours[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colours[ImGuiCol_FrameBg] = ImVec4(0.31f, 0.35f, 0.44f, 1.00f);
	colours[ImGuiCol_FrameBgHovered] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
	colours[ImGuiCol_FrameBgActive] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
	colours[ImGuiCol_TitleBg] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
	colours[ImGuiCol_TitleBgActive] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
	colours[ImGuiCol_TitleBgCollapsed] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
	colours[ImGuiCol_MenuBarBg] = ImVec4(0.31f, 0.35f, 0.44f, 1.00f);
	colours[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
	colours[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.35f, 0.43f, 1.00f);
	colours[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
	colours[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
	colours[ImGuiCol_CheckMark] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
	colours[ImGuiCol_SliderGrab] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
	colours[ImGuiCol_SliderGrabActive] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
	colours[ImGuiCol_Button] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
	colours[ImGuiCol_ButtonHovered] = ImVec4(0.83f, 0.26f, 0.34f, 1.00f);
	colours[ImGuiCol_ButtonActive] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
	colours[ImGuiCol_Header] = ImVec4(0.31f, 0.35f, 0.43f, 1.00f);
	colours[ImGuiCol_HeaderHovered] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
	colours[ImGuiCol_HeaderActive] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
	colours[ImGuiCol_Separator] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colours[ImGuiCol_SeparatorHovered] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
	colours[ImGuiCol_SeparatorActive] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
	colours[ImGuiCol_ResizeGrip] = ImVec4(0.31f, 0.35f, 0.44f, 1.00f);
	colours[ImGuiCol_ResizeGripHovered] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
	colours[ImGuiCol_ResizeGripActive] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
	colours[ImGuiCol_Tab] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
	colours[ImGuiCol_TabHovered] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
	colours[ImGuiCol_TabActive] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
	colours[ImGuiCol_TabUnfocusedActive] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
	colours[ImGuiCol_DockingPreview] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
	colours[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.35f);
	colours[ImGuiCol_NavHighlight] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
}

float ConvertBlenderToSource(float x) {
	return (x / 2) * 128;
}

float ConvertSourceToBlender(float y) {
	return (y / 128) * 2;
}

// MAIN

int main()
{

#ifdef CFG_RELEASE
	FreeConsole();
#endif

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE); //TODO

	int winX = 450; // On 1080p
	int winY = 75;

	float multiplier = (float)glfwGetVideoMode(glfwGetPrimaryMonitor())->height / 1080;
	winX *= multiplier;
	winY *= multiplier;

	GLFWwindow* window = glfwCreateWindow(winX, winY, "HLRTools", nullptr, nullptr);

	if (!window)
	{
		// ERROR!
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		// ERROR!
	}

	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
	glfwSetKeyCallback(window, keyCallback);

	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	std::cout << multiplier << std::endl;

	setIMGUIStyle(multiplier);

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");


	float inputValueSource = 0.0f;
	float inputValueBlender = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowCollapsed(false);
		ImGui::SetNextWindowPos(ImVec2(0,0));
		ImGui::SetNextWindowSize(ImVec2(winX, winY));

		ImGuiWindowFlags windowFlags = 0;
		windowFlags |= ImGuiWindowFlags_NoScrollbar;
		windowFlags |= ImGuiWindowFlags_NoResize;
		windowFlags |= ImGuiWindowFlags_NoCollapse;
		windowFlags |= ImGuiWindowFlags_NoSavedSettings;
		windowFlags |= ImGuiWindowFlags_NoMove;

		ImGui::Begin("HLR Unit Converter", NULL, windowFlags);

		float inputValueSourcePreviousFrame = inputValueSource;
		float inputValueBlenderPreviousFrame = inputValueBlender;

		ImGui::SetNextItemWidth(100 * multiplier);
		ImGui::InputFloat("Blender", &inputValueBlender);
		ImGui::SameLine(0, 15 * multiplier);
		ImGui::SetNextItemWidth(20);
		ImGui::Text("<< -- >>");
		ImGui::SameLine(0, 15 * multiplier);
		ImGui::SetNextItemWidth(100 * multiplier);
		ImGui::InputFloat("Source", &inputValueSource);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (inputValueSource != inputValueSourcePreviousFrame)
		{
			inputValueBlender = ConvertSourceToBlender(inputValueSource);
		}

		if (inputValueBlender != inputValueBlenderPreviousFrame)
		{
			inputValueSource = ConvertBlenderToSource(inputValueBlender);
		}

		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();

	glfwTerminate();

}