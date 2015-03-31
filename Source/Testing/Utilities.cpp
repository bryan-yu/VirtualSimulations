#include "Testing.h"
#include <iostream>

#if _WIN32
	#include <windows.h>
#endif

void print_coloured(std::string str, int color)
{
#if _WIN32
	HANDLE hstdin  = GetStdHandle( STD_INPUT_HANDLE  );
	HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
	WORD   index   = 0;

	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo( hstdout, &csbi );

	// Draw pretty colors until the user presses any key
	SetConsoleTextAttribute( hstdout, color );
#endif
	std::cout << str;
#if _WIN32
	FlushConsoleInputBuffer( hstdin );

	// Keep users happy
	SetConsoleTextAttribute( hstdout, csbi.wAttributes );
#endif
}

void print_individual_success(bool success)
{
	std::stringstream ss;
	ss << "\tTest" << (success ? "Passed" : "Failed") << std::endl;
	print_coloured(ss.str(), success ? FGGREEN_BGBLACK : FGRED_BGBLACK);
}

