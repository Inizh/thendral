#include <stdio.h>
#include <stdlib.h>

void OpenURLInBrowser(const char* url) {
#ifdef _WIN32
	// Windows
	ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWDEFAULT);
#elif __APPLE__
	// macOS
	const char* open_executable = "open";
	char command[256];
	snprintf(command, 256, "%s \"%s\"", open_executable, url);
	system(command);
#else
	// Linux/Unix (xdg-open is common)
	const char* open_executable = "xdg-open";
	char command[256];
	snprintf(command, 256, "%s \"%s\"", open_executable, url);
	system(command);
#endif
}
