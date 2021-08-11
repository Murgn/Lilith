workspace "Lilith"
	architecture "x64"

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
include "Lilith/vendor/GLFW"
include "Lilith/vendor/Glad"
include "Lilith/vendor/ImGui"

project "Lilith"
	location "Lilith"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "lipch.h"
	pchsource "Lilith/src/lipch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"LI_PLATFORM_WINDOWS",
			"LI_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations.Debug"
		defines "LI_DEBUG"
		symbols "On"

	filter "configurations.Release"
		defines "LI_RELEASE"
		optimize "On"

	filter "configurations.Dist"
		defines "LI_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Lilith/src"
	}

	links
	{
		"Lilith"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"LI_PLATFORM_WINDOWS"
		}

	filter "configurations.Debug"
		defines "LI_DEBUG"
		symbols "On"

	filter "configurations.Release"
		defines "LI_RELEASE"
		optimize "On"

	filter "configurations.Dist"
		defines "LI_DIST"
		optimize "On"