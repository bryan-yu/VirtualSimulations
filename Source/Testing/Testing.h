#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "OgreRenderWindow.h"

#if _WIN32
	#define FG_BLUE		 0x01
	#define FG_GREEN	 0x02
	#define FG_RED		 0x04
	#define FG_INTENSITY 0x08
	#define BG_BLUE		 0x10
	#define BG_GREEN	 0x20
	#define BG_RED		 0x40
	#define BG_INTENSITY 0x80

	#define FGRED_BGBLACK	(FG_RED   | FG_INTENSITY)
	#define FGGREEN_BGBLACK	(FG_GREEN | FG_INTENSITY)
#endif

void print_coloured(std::string str, int color);
void print_individual_success(bool success);

namespace Vector3Test { bool dotest(); }
namespace Point3Test { bool dotest(); }
namespace InputTest { bool dotest(); }
namespace GameObjectTest { bool doTest(); }
