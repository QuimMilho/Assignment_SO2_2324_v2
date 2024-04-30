workspace "Assignment_SO2_2324_v2"
	architecture "x86"
	configurations {
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

-- Incluide dirs relative to root folder
IncludeDir = {}

project "bolsa"
	location "bolsa"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "pch/so2pch.h"
	pchsource "%{prj.name}/src/pch/so2pch.cpp"
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	
	includedirs {
		"%{prj.name}/src",
		"dynamicLib/src"
	}
	
	links {
		"dynamicLib"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		
		defines {
			"SO2_PLATFORM_WINDOWS",
			"UNICODE"
		}
		
	filter "configurations:Debug"
		defines "SO2_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "SO2_RELEASE"
		optimize "On"

project "board"
	location "board"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "pch/so2pch.h"
	pchsource "%{prj.name}/src/pch/so2pch.cpp"
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	
	includedirs {
		"%{prj.name}/src",
		"dynamicLib/src"
	}
	
	links {
		"dynamicLib"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		
		defines {
			"SO2_PLATFORM_WINDOWS",
			"UNICODE"
		}
		
	filter "configurations:Debug"
		defines "SO2_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "SO2_RELEASE"
		optimize "On"
		
project "boardGUI"
	location "boardGUI"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "pch/so2pch.h"
	pchsource "%{prj.name}/src/pch/so2pch.cpp"
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	
	includedirs {
		"%{prj.name}/src",
		"dynamicLib/src"
	}
	
	links {
		"dynamicLib"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		
		defines {
			"SO2_PLATFORM_WINDOWS",
			"UNICODE"
		}
		
	filter "configurations:Debug"
		defines "SO2_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "SO2_RELEASE"
		optimize "On"

project "cliente"
	location "cliente"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "pch/so2pch.h"
	pchsource "%{prj.name}/src/pch/so2pch.cpp"
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	
	includedirs {
		"%{prj.name}/src",
		"dynamicLib/src"
	}
	
	links {
		"dynamicLib"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		
		defines {
			"SO2_PLATFORM_WINDOWS",
			"UNICODE"
		}
		
	filter "configurations:Debug"
		defines "SO2_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "SO2_RELEASE"
		optimize "On"

project "dynamicLib"
	location "dynamicLib"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "pch/so2pch.h"
	pchsource "%{prj.name}/src/pch/so2pch.cpp"
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	
	includedirs {
		"%{prj.name}/src"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		
		defines {
			"SO2_BUILD_DLL",
			"SO2_PLATFORM_WINDOWS",
			"UNICODE"
		}
		
	filter "configurations:Debug"
		defines "SO2_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "SO2_RELEASE"
		optimize "On"