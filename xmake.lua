-- Match 3 game --
-- Made by Vincent Son --

set_project("Match3")
set_languages("cxx17")

if is_mode("release") then
    set_optimize("fastest")
elseif is_mode("debug") then
    set_warnings("allextra")
    set_optimize("none")
    set_symbols("debug")
end

add_requires("sfml")

target("match3")
    set_kind("binary")
    add_files("./main.cpp")
    add_files("src/*.cpp")
    add_packages("sfml")