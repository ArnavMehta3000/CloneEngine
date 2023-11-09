
project "CloneEngineRuntime"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++latest"

    targetdir "%{wks.location}/build/bin/%{cfg.architecture}-%{cfg.buildcfg}"
    objdir "%{wks.location}/build/int/%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"

    location "%{wks.location}/Runtime/"
    links { "CloneEngineCore" , "%USER_PROJECT_NAME%"}

    includedirs 
    {
        "%{wks.location}/Engine/include/",
        "%{wks.location}/%USER_PROJECT_NAME%/src/",
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
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"