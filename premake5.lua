workspace "Deyo"
	architecture "x64"
	platforms "Windows"

	configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}_%{cfg.platform}_%{cfg.architecture}"

-- the engine
group "Core"
	include "Deyo"

-- client applications
group "Deyo Clients"
	include "Playground"

-- engine dependencies
group "ThirdParty"
	include "Deyo/vendor/GLFW"
	include "Deyo/vendor/GLAD"
	include "Deyo/vendor/ImGui"