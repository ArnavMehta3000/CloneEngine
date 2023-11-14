
project "{0}"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"

    targetdir "%{{wks.location}}/build/bin/%{{cfg.architecture}}-%{{cfg.buildcfg}}"
    objdir "%{{wks.location}}/build/int/%{{cfg.architecture}}-%{{cfg.buildcfg}}/%{{prj.name}}"

    location "%{{wks.location}}/{0}/"
    links {{ "CloneEngineCore" }}

    includedirs 
    {{
        "%{{wks.location}}/Engine/include/",
        "%{{prj.location}}/src/"
    }}

    files
    {{
        "%{{prj.location}}/**.h",
        "%{{prj.location}}/**.hpp",
        "%{{prj.location}}/**.cpp",
        "%{{prj.location}}/**.ixx",
    }}

    flags
    {{
        "MultiProcessorCompile"
    }}

    filter "configurations:Debug"
        defines {{ "DEBUG", "_DEBUG", "GAME" }}
        symbols "On"

    filter "configurations:Release"
        defines {{ "NDEBUG", "GAME" }}
        optimize "On"
        symbols "Off"
        
