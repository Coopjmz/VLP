workspace "VLP"
    architecture "x64"
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

BuildDir = "%{wks.location}/build"
OutDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
BinDir = "%{BuildDir}/bin/%{OutDir}"
ObjDir = "%{BuildDir}/obj/%{OutDir}"

include "VLP"
include "Example"