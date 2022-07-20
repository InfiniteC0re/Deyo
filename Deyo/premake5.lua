project "Deyo"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "src/pch.cpp"
	
	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"vendor/GLFW/include",
		"vendor/GLAD/include",
		"vendor/ImGui",
	}
	
	defines
	{
		"DEYO_ENGINE",
		"GLFW_INCLUDE_NONE"
	}

	filter "system:windows"
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"DEYO_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DEYO_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "DEYO_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "DEYO_DIST"
		runtime "Release"
		optimize "On"