project "Example"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir (BinDir)
    objdir (ObjDir)

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
        "../VLP/src"
    }

    links
    {
        "VLP"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        defines "DEBUG"
        optimize "Off"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        defines "RELEASE"
        optimize "On"
        symbols "Off"