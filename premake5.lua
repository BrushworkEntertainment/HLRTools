workspace "HLRTools"
-- Put that SDK in huge quotations 
	architecture "x86_64"
	cppdialect "C++17"

	configurations 
	{ 
		"Debug",
		"PreRelease",
		"Release" 
	}

	flags { "MultiProcessorCompile" }

	startproject "UnitUtil"

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

---------------------------------------------------

project "UnitUtil"
	filename "Unit"
	location "UnitUtil"

	kind "ConsoleApp"
	language "C++"

	targetdir ("%{wks.location}/out/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/out/obj/" .. outputdir .. "/%{prj.name}")
	debugdir ("%{wks.location}/out/bin/" .. outputdir .. "/%{prj.name}")

	defines { "_CRT_SECURE_NO_WARNINGS" }

	files 
	{
		"UnitUtil/src/**.cpp",
		"UnitUtil/src/**.hpp",
		"UnitUtil/src/**.h",
		"UnitUtil/dependencies/**.c",
		"UnitUtil/dependencies/**.h",
		"UnitUtil/dependencies/**.cpp",
		"UnitUtil/dependencies/**.hpp",
		"UnitUtil/dependencies/**.inl"
	}

	includedirs
	{
		"UnitUtil/src",
		"%{wks.location}/dependencies/include",
		"%{wks.location}/dependencies/include/imgui"
	}

	libdirs
	{
		"%{wks.location}/dependencies/lib"
	}

	links
	{
		"opengl32",
		"glfw3.lib"
	}

	filter "configurations:Debug"
		defines { "CFG_DEBUG" }
		symbols "On"
		optimize "Off"
	
	filter "configurations:PreRelease"
		defines { "CFG_PRERELEASE" }
		symbols "On"
		optimize "On"
		
	filter "configurations:Release"
		defines { "CFG_RELEASE" }
		symbols "Off"
		optimize "On"

---------------------------------------------------
