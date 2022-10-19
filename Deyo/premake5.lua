project "Deyo"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

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
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.GLM}"
	}
	
	defines
	{
		"DEYO_ENGINE",
		"GLFW_INCLUDE_NONE",
		"SPDLOG_WCHAR_TO_UTF8_SUPPORT"
	}

	filter "system:windows"
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