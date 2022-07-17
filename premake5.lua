workspace "Deyo"
	architecture "x64"
	platforms "Windows"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}_%{cfg.platform}_%{cfg.architecture}"

project "Deyo"
	location "Deyo"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "%{prj.name}/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Playground")
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"DEYO_PLATFORM_WINDOWS",
			"DEYO_ENGINE",
			"_WINDLL"
		}

	filter "configurations:Debug"
		defines "DEYO_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DEYO_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "DEYO_DIST"
		optimize "On"


project "Playground"
	location "Playground"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	links
	{
		"Deyo"
	}

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Deyo/vendor/spdlog/include",
		"Deyo/src"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"DEYO_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DEYO_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DEYO_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "DEYO_DIST"
		optimize "On"