workspace "Lilith"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Lilith/vendor/GLFW/include"
IncludeDir["Glad"] = "Lilith/vendor/Glad/include"
IncludeDir["ImGui"] = "Lilith/vendor/ImGui"
IncludeDir["glm"] = "Lilith/vendor/glm"
IncludeDir["stb_image"] = "Lilith/vendor/stb_image"

group "Dependencies"
	include "Lilith/vendor/GLFW"
	include "Lilith/vendor/Glad"
	include "Lilith/vendor/ImGui"

group ""

project "Lilith"
	location "Lilith"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "lipch.h"
	pchsource "Lilith/src/lipch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"LI_PLATFORM_WINDOWS",
			"LI_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "LI_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LI_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LI_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Lilith/vendor/spdlog/include",
		"Lilith/src",
		"Lilith/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Lilith"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"LI_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
