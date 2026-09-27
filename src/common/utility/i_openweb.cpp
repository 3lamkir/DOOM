// Opens a URL in the system's default web browser.
// Used by the "Web" option added to the pause/options menu.

#include "c_cvars.h"
#include "c_dispatch.h"

#if defined(_WIN32)
#include <windows.h>
#include <shellapi.h>
#elif defined(__APPLE__)
#include <cstdlib>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif

static void OpenURLInBrowser(const char *url)
{
#if defined(_WIN32)
	ShellExecuteA(nullptr, "open", url, nullptr, nullptr, SW_SHOWNORMAL);
#elif defined(__APPLE__)
	FString cmd;
	cmd.Format("open \"%s\"", url);
	system(cmd.GetChars());
#else
	pid_t pid = fork();
	if (pid == 0)
	{
		execlp("xdg-open", "xdg-open", url, (char *)nullptr);
		_exit(1);
	}
#endif
}

CVAR(String, web_url, "https://example.com", CVAR_ARCHIVE)

CCMD(openweb)
{
	OpenURLInBrowser(web_url);
}
