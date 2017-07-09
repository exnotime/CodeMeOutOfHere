solution "CodeMeOut"
    configurations { "Debug", "Release" }
        flags{ "Unicode", "NoPCH" }
        libdirs { "lib", "lib/sfml" }
        includedirs { "inc"}
        platforms{"x64" }

        local location_path = "solution"
        if _ACTION then
	        defines { "_CRT_SECURE_NO_WARNINGS", "NOMINMAX"  }
            location_path = location_path .. "/" .. _ACTION
            location ( location_path )
            location_path = location_path .. "/projects"
        end

    configuration { "Debug" }
        defines { "DEBUG" }
        flags { "Symbols" }
        targetdir ( "bin/" .. "/debug" )

    configuration { "Release" }
        defines { "NDEBUG", "RELEASE" }
        flags { "Optimize", "FloatFast", "Symbols" }
        targetdir ( "bin/" .. "/release" )


	project "Main"
        targetname "CodeMeOut"
		debugdir ""
        defines { "AS_USE_NAMESPACE" }
		location ( location_path )
		language "C++"
		kind "ConsoleApp"
		files { "src/**"}
		includedirs { "include", "src" }
        configuration { "Debug" }
                links { "angelscript64d", "sfml-audio-d","sfml-graphics-d","sfml-main-d","sfml-system-d","sfml-window-d" }
        configuration { "Release" }
                links { "angelscript64", "sfml-audio","sfml-graphics","sfml-main","sfml-system","sfml-window" }
        
