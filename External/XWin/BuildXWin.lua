
project "XWin"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"

    targetdir "%{wks.location}/build/bin/%{cfg.architecture}-%{cfg.buildcfg}"
    objdir "%{wks.location}/build/int/%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"

    location "%{wks.location}/External/Xwin/"

    includedirs 
    {
        "%{prj.location}/include/XWin/",
        "%{prj.location}/src/"
    }

    files
    {
        "%{prj.location}/**.h",
        "%{prj.location}/**.hpp",
        "%{prj.location}/**.cpp",
        "%{prj.location}/**.ixx",
    }

    flags
    {
        "MultiProcessorCompile"
    }

    filter "configurations:Debug"
        defines { "DEBUG", "_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG", "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"
        
    filter "configurations:Shipping"
        defines { "NDEBUG", "SHIPPING" }
        runtime "Release"
        optimize "On"
        symbols "Off"