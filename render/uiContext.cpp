/** @file      uiContext.cpp
 *  @brief     Source file for the UI Context functions.
 *  @author    arturodlrios
 *  @date      Created on 2024/02/27
 *
 *  This software is the exclusive property of Cortx and is provided
 *  under strict confidentiality. It is intended for use solely by authorized
 *  personnel of Cortx and is protected by intellectual property laws.
 *  Unauthorized use, reproduction, or distribution in whole or in part is
 *  scrictly prohibited.
 *
 *  COPYRIGHT NOTICE: 2025 Cortx, Montreal, QC. All rights reserved.
 */

#include "../pch/pch.h"
#include "uiContext.h"
#include "../backends/imgui.h"
#include "../backends/imgui_impl_glfw.h"
#include "../backends/imgui_impl_opengl3.h"
#include "../backends/implot.h"
#include "../backends/imguiCustomThemes.h"
#include <filesystem>
#include "../ui/IconsFontAwesome5.h"

namespace nrender
{

OrbCode_t UIContext::init(nwindow::IWindow *pWindow)
{
  /* Add font files */
  std::filesystem::path fontsFolder;
  
  // Try multiple possible font locations for both development and installed versions
  std::vector<std::filesystem::path> possibleFontPaths = {
    std::filesystem::current_path() / "fonts/",
    std::filesystem::current_path() / ".." / "fonts/",
    std::filesystem::current_path() / ".." / ".." / "fonts/",
    std::filesystem::current_path() / "bin" / "fonts/",
    std::filesystem::current_path() / "mscope" / "fonts/",
    "/usr/local/bin/mscope/fonts/",
    "/usr/bin/mscope/fonts/"
  };
  
  // Find the first valid fonts directory
  for (const auto& path : possibleFontPaths) {
    if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
      fontsFolder = path;
      std::cout << "Found fonts directory: " << fontsFolder.string() << std::endl;
      break;
    }
  }
  
  if (fontsFolder.empty()) {
    std::cout << "Warning: No fonts directory found, using current path" << std::endl;
    fontsFolder = std::filesystem::current_path() / "fonts/";
  }
  
  std::string strFontPathLight = (fontsFolder / "OpenSans-Light.ttf").string();
  std::string strFontPathRegular
      = (fontsFolder / "OpenSans-Regular.ttf").string();
  std::string strFontPathBold = (fontsFolder / "OpenSans-Bold.ttf").string();
  std::string strFontPathFaSolid
      = (fontsFolder / "fontawesome-webfont.ttf").string();

  RenderContext::init(pWindow);

  /* GL 3.0 + GLSL 130 */
#ifdef PLATFORM_RASPBERRY_PI
  const char *pGlslVersion = "#version 100";  // OpenGL ES 2.0
#else
  const char *pGlslVersion = "#version 410";  // Desktop OpenGL
#endif

  /* Setup Dear ImGui context */
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImPlot::CreateContext();

  ImGuiIO &io = ImGui::GetIO();
  
  // Load the main font (Regular)
  std::cout << "Attempting to load font: " << strFontPathRegular << std::endl;
  ImFont* mainFont = io.Fonts->AddFontFromFileTTF(strFontPathRegular.c_str(), 17);
  if (!mainFont) {
    // Fallback to default font if custom font fails to load
    std::cout << "Warning: Failed to load font: " << strFontPathRegular << std::endl;
    std::cout << "File exists: " << (std::filesystem::exists(strFontPathRegular) ? "Yes" : "No") << std::endl;
    io.Fonts->AddFontDefault();
  } else {
    std::cout << "Successfully loaded font: " << strFontPathRegular << std::endl;
  }

  float baseFontSize = 17.0f; // 13.0f is the size of the default font. Change
                              // to the font size you use.
  float iconFontSize
      = baseFontSize * 2.0f
        / 3.0f; // FontAwesome fonts need to have their sizes reduced
                // by 2.0f/3.0f in order to align correctly

  // Load FontAwesome icons and merge with main font
  std::cout << "Attempting to load FontAwesome font: " << strFontPathFaSolid << std::endl;
  static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_16_FA, 0};
  ImFontConfig icons_config;
  icons_config.MergeMode = true;
  icons_config.PixelSnapH = true;
  icons_config.GlyphMinAdvanceX = iconFontSize;
  ImFont* iconFont = io.Fonts->AddFontFromFileTTF(strFontPathFaSolid.c_str(), iconFontSize,
                               &icons_config, icons_ranges);
  if (!iconFont) {
    std::cout << "Warning: Failed to load FontAwesome font: " << strFontPathFaSolid << std::endl;
    std::cout << "File exists: " << (std::filesystem::exists(strFontPathFaSolid) ? "Yes" : "No") << std::endl;
  } else {
    std::cout << "Successfully loaded FontAwesome font: " << strFontPathFaSolid << std::endl;
  }

  io.Fonts->Build();

  (void)io;
  io.ConfigFlags
      |= ImGuiConfigFlags_NavEnableKeyboard; /* Enable Keyboard Controls */
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; /* Enable Docking */
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  // ImGui::StyleColorsDark();

  ImGuiStyle &style = ImGui::GetStyle();

  SetImGuiStyleMscopeDark(style);

  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  /* Setup Platform/Renderer backends */
  ImGui_ImplGlfw_InitForOpenGL((GLFWwindow *)pWindow_m->pGetNativeWindow(),
                               true);
  ImGui_ImplOpenGL3_Init(pGlslVersion);

  return Success;
}

void UIContext::preRender(void)
{
  /* Start the Dear ImGui frame */
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // Create the docking environment
  ImGuiWindowFlags windowFlags
      = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus
        | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;

  ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);

  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("InvisibleWindow", nullptr, windowFlags);
  ImGui::PopStyleVar(3);

  ImGuiID dockSpaceId = ImGui::GetID("InvisibleWindowDockSpace");

  ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f),
                   ImGuiDockNodeFlags_PassthruCentralNode);
  ImGui::End();
}

void UIContext::postRender(void)
{
  /* Rendering */
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  ImGuiIO &io = ImGui::GetIO();

  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    GLFWwindow *backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
}

void UIContext::end(void)
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  ImPlot::DestroyContext();
}

} // namespace nrender
