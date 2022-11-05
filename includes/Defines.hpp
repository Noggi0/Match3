/**
 * Match 3 game, by Vincent Son
 */

#ifndef __DEFINES_HPP__
#define __DEFINES_HPP__

#include <string>

/* Paths */
#ifdef _WIN32
	const std::string ASSETS_PATH = "../../../../assets/";
#else
	const std::string ASSETS_PATH = "../../../../assets/";
#endif

/* Window Size */
#ifdef __APPLE__
    constexpr int WIDTH = 800 * 2;
    constexpr int HEIGHT = 600 * 2;
#elif _WIN32
    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 600;
#endif


#endif /* __DEFINES_HPP__ */