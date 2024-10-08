project "VLP"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir (BinDir)
    objdir (IntDir)

	pchheader "vlppch.h"
	pchsource "src/vlppch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src"
    }

    filter "system:windows"
        systemversion "latest"
        defines "VLP_PLATFORM_WINDOWS"

    filter "configurations:Debug"
        runtime "Debug"
        defines "VLP_DEBUG"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        defines "VLP_RELEASE"
        optimize "on"