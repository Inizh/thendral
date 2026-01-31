//
// Created by JCKawin on 30/01/26.
//

#include "application.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <cstdio>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl3.h"
#include "thendral.h"

int main(const int argc, const char* argv[]) {
	// INIT SDL
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
		printf("Error: SDL_Init(): %s\n", SDL_GetError());
		return 1;
	}

	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
						SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	// Create window with graphics context
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
	SDL_WindowFlags window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
								   SDL_WINDOW_HIDDEN |
								   SDL_WINDOW_HIGH_PIXEL_DENSITY;
	SDL_Window* window = SDL_CreateWindow(
		"Dear ImGui SDL3+OpenGL3 example", static_cast<int>(1280 * main_scale),
		static_cast<int>(800 * main_scale), window_flags);
	if (window == nullptr) {
		printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
		return 1;
	}
	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	if (gl_context == nullptr) {
		printf("Error: SDL_GL_CreateContext(): %s\n", SDL_GetError());
		return 1;
	}

	SDL_GL_MakeCurrent(window, gl_context);
	SDL_GL_SetSwapInterval(1);	// Enable vsync
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED,
						  SDL_WINDOWPOS_CENTERED);
	SDL_ShowWindow(window);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |=
		ImGuiConfigFlags_NavEnableKeyboard;	 // Enable Keyboard Controls
	io.ConfigFlags |=
		ImGuiConfigFlags_NavEnableGamepad;	// Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking
	io.ConfigFlags |=
		ImGuiConfigFlags_ViewportsEnable;  // Enable Multi-Viewport / Platform
										   // Windows
	// io.ConfigViewportsNoAutoMerge = true;
	// io.ConfigViewportsNoTaskBarIcon = true;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// ImGui::StyleColorsLight();

	// Setup scaling
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(
		main_scale);  // Bake a fixed style scale. (until we have a solution for
					  // dynamic style scaling, changing this requires resetting
					  // Style + calling this again)
	style.FontScaleDpi =
		main_scale;	 // Set initial font scale. (in docking branch: using
					 // io.ConfigDpiScaleFonts=true automatically overrides this
					 // for every window depending on the current monitor)
	io.ConfigDpiScaleFonts =
		true;  // * Experimental * Automatically overwrite style.FontScaleDpi in
			   // Begin() when Monitor DPI changes. This will scale fonts but
			   // _NOT_ scale sizes/padding for now.
	io.ConfigDpiScaleViewports =
		true;  // * Experimental *  Scale Dear ImGui and Platform Windows when
			   // Monitor DPI changes.

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform
	// windows can look identical to regular ones.
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 10.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplSDL3_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Our state

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Main loop
	bool done = false;
	while (!done) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL3_ProcessEvent(&event);
			if (event.type == SDL_EVENT_QUIT) done = true;
			if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
				event.window.windowID == SDL_GetWindowID(window))
				done = true;
		}

		if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
			SDL_Delay(10);
			continue;
		}

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

		ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(),
									 ImGuiDockNodeFlags_PassthruCentralNode);
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("New")) {
				}
				if (ImGui::MenuItem("Open")) {
				}
				if (ImGui::MenuItem("Save")) {
				}
				if (ImGui::MenuItem("Exit")) {
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit")) {
				if (ImGui::MenuItem("Undo")) {
				}
				if (ImGui::MenuItem("Redo")) {
				}
				if (ImGui::MenuItem("Clear")) {
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View")) {
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Help")) {
			}
			if (ImGui::MenuItem("About")) {
			}
			if (ImGui::MenuItem("Quit")) {
				done = true;
			}

			ImGui::EndMainMenuBar();
		}
		// Rendering
		ImGui::Render();
		glViewport(0, 0, static_cast<int>(io.DisplaySize.x),
				   static_cast<int>(io.DisplaySize.y));
		glClearColor(clear_color.x * clear_color.w,
					 clear_color.y * clear_color.w,
					 clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
			SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
		}

		SDL_GL_SwapWindow(window);
	}

	// Clean up
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DestroyContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
