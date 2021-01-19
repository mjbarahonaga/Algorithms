workspace "Algorithms"
    architecture "x86_64"
    startproject "Demo"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

project "Demo"
    location "Demo"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"
    systemversion "latest"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("build/" .. outputdir .. "/%{prj.name}")

    warnings "Extra"

    files
    {
        "algorithms.h",
        "%{prj.name}/Tests/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/Tests",
        "../Algorithms"
    }

    filter "configurations:Debug"
        -- defines
        -- {
        --     "PE_DEBUG"
        -- }
        runtime "Debug"
        symbols "On"
        buildoptions "/MTd"

    filter "configurations:Release"
        -- defines "PE_RELEASE"
        runtime "Release"
        optimize "Speed"
        buildoptions "/MT"
