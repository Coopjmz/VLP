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
        defines "PLATFORM_WINDOWS"

    filter "configurations:Debug"
        runtime "Debug"
        defines "DEBUG"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        defines "RELEASE"
        optimize "on"