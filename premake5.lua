project "fracky"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/"
    objdir "bin-int/"

    files {"src/**.cpp","%{prj.location}/include/**.h"}
    includedirs {"%{prj.location}/include/"}

    filter "configurations:Debug"
        symbols "On"
    filter "configurations:Release"
        optimize "On"
    filter "configurations:Dist"
        optimize "On"