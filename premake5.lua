--main
workspace "VoxelRender"
	architecture "x64"
	startproject "VoxelRender"

configurations
{
	"Debug",
	"Release"
}

flags
{
	"MultiProcessorCompile"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/VoxelRender/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/VoxelRender/vendor/Glad/include"
IncludeDir["glm"] = "%{wks.location}/VoxelRender/vendor/glm/"

group "Deps"
	include "VoxelRender/vendor/GLFW"
	include "VoxelRender/vendor/Glad"
group ""

include "VoxelRender"
