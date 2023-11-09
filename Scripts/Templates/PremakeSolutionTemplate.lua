workspace "{0}"
    configurations {{ "Debug", "Release" }}
    startproject "CloneEngineRuntime"
    architecture "x64"
    location "{1}"

include "{1}/Runtime/BuildRuntime.lua"
include "{1}/Engine/BuildEngine.lua"
include "{1}/{0}/Build{0}.lua"
