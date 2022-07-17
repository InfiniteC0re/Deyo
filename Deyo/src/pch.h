#pragma once

// Functionality
#include <iostream>
#include <utility>
#include <memory>
#include <algorithm>
#include <functional>

// Types
#include <vector>
#include <unordered_set>
#include <unordered_map>
// these two are some parts of <functional> or it's dependencies
// #include <cstdint>
// #include <string>

// Deyo headers
#include <Deyo/Log.h>

// Platform specific headers
#ifdef DEYO_PLATFORM_WINDOWS
	#include <Windows.h>
#endif