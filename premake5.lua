workspace "VLP"
    architecture "x86_64"
    startproject "Example"

    configurations
    {
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    filter "system:windows"
        buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

BuildDir = "%{wks.location}/build"
OutDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
BinDir = "%{BuildDir}/bin/%{OutDir}"
ObjDir = "%{BuildDir}/obj/%{OutDir}"

include "VLP"
include "Example"