workspace "VLP"
    architecture "x64"
    startproject "Test"

    configurations
    {
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }

OutDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
BinDir = "%{wks.location}/bin/%{OutDir}/%{prj.name}"
IntDir = "%{wks.location}/bin-int/%{OutDir}/%{prj.name}"

include "VLP"
include "Test"