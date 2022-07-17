workspace "Deyo"
	architecture "x64"
	platforms "Windows"

	configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}_%{cfg.platform}_%{cfg.architecture}"

-- the engine
include "Deyo"

-- engine dependencies
include "Deyo/vendor/GLFW"
include "Deyo/vendor/GLAD"

-- client applications
include "Playground"