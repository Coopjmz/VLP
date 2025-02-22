project "VLP"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir (BinDir)
    objdir (ObjDir)

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

    filter "configurations:Debug"
        runtime "Debug"
        defines "VLP_DEBUG"
        optimize "Off"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        defines "VLP_RELEASE"
        optimize "On"
        symbols "Off"