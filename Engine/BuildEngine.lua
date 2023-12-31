
project "CloneEngineCore"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    nuget { "directxtk_desktop_win10:2023.10.31.1" }

    targetdir "%{wks.location}/build/bin/%{cfg.architecture}-%{cfg.buildcfg}"
    objdir "%{wks.location}/build/int/%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"

    location "%{wks.location}/Engine/"
    -- links { "" }

    includedirs 
    {
        "%{prj.location}/"
    }

    files
    {
        "%{prj.location}/**.h",
        "%{prj.location}/**.hpp",
        "%{prj.location}/**.cpp",
        "%{prj.location}/**.ixx",
        "%{prj.location}/**.inl",
        "%{prj.location}/**.hint",
        "%{prj.location}/**.natvis",
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