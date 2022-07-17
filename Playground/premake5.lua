project "Playground"
	kind "ConsoleApp"
	language "C++"

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
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"DEYO_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		buildoptions "/MDd"
		defines "DEYO_DEBUG"
		symbols "On"

	filter "configurations:Release"
		buildoptions "/MD"
		defines "DEYO_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		buildoptions "/MD"
		defines "DEYO_DIST"
		optimize "On"