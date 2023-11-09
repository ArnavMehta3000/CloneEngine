workspace "{0}"
    configurations {{ "Debug", "Release" }}
    architecture "x64"
    location "{1}"
    startproject "Runtime"

include "{1}/Engine/BuildEngine.lua"
include "{1}/Runtime/BuildRuntime.lua"
include "{1}/{0}/Build{0}.lua"
