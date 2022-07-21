project "Playground"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	links
	{
		"Deyo"
	}

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Deyo/vendor/spdlog/include",
		"%{wks.location}/Deyo/src"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"DEYO_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		defines "DEYO_DEBUG"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		defines "DEYO_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		runtime "Release"
		defines "DEYO_DIST"
		optimize "On"