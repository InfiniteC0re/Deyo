#pragma once

// Functionality
#include <iostream>
#include <utility>
#include <memory>
#include <algorithm>
#include <functional>
#include <type_traits>

// Types
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
// these two are some parts of <functional> or it's dependencies
// #include <cstdint>
// #include <string>

// Libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Deyo headers
#include <Deyo/Core/Core.h>
#include <Deyo/Core/Log.h>

// Platform specific headers
#ifdef DEYO_PLATFORM_WINDOWS
	#include <Windows.h>
#endif