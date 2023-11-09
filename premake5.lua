workspace "TestGame"
    configurations { "Debug", "Release" }
    architecture "x64"
    location "E:/Dev/CloneEngine"
    startproject "Runtime"

include "E:/Dev/CloneEngine/Engine/BuildEngine.lua"
include "E:/Dev/CloneEngine/Runtime/BuildRuntime.lua"
include "E:/Dev/CloneEngine/TestGame/BuildTestGame.lua"
