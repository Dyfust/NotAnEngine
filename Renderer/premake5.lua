workspace "NotAnEngine"
    architecture "x64"

    configurations {"Debug", "Release"}

project "NotAnEngine"
    location "NotAnEngine"
    language "C++"
    kind "ConsoleApp"

    outputformat = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    targetdir ("bin/" .. outputformat .. "/%{prj.name}")
    objdir ("bin-int/" .. outputformat .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "$(ProjectDir)vendor/stb_image",
        "$(ProjectDir)vendor/glcore",
        "$(ProjectDir)vendor/glfw/GLFW",
        "$(ProjectDir)vendor/glm",
        "$(ProjectDir)vendor/obj_loader",
    }

    libdirs
    {
        "$(ProjectDir)vendor/glfw"
    }
    
    links 
    {
        "glfw3.lib",
    }

    filter {"configurations:Debug"}
        defines {"DEBUG"}
        symbols "On"

    filter {"configurations:Release"}
        defines {"NDEBUG"}
        optimize "On"

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest" 