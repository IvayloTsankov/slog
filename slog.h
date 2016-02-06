#ifndef SLOG_H_
#define SLOG_H_

// Installing:
//      When compile add -DSLOGGING or/and -DLOGGING_DEBUG
// Usage:
//      Same usage as printf
//      SLOG(<format_string>, param1, param2, ...);
//      SLOG_DEBUG(<format_string>, param1, param2, ...);
//
// Change outputfile:
//      SLOG_set_output(FILE* output);

// Simple logging mechanism
#if defined (SLOGGING)
#   include <string>
#   include <chrono>
#   include <cstdint>
#   include <cstdio>

#if defined (WIN_32)
#   include "WinBase.h"
#   define DWORD pid_t;
#else
#   include <unistd.h>
#endif // (WIN_32)

    static pid_t SLOG_getpid()
    {
#if defined (_WIN32)
        return GetProcessId();
#else
        return getpid();
#endif // (_WIN32)
    }

    static long long int SLOG_get_utc_millisec()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>
               (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    }

	static FILE* log_output = stdout;
	#define SLOG(a, ...) fprintf(log_output, "(ts: %lld)(pid: %d) " a "\n", \
                                 SLOG_get_utc_millisec(), \
                                 SLOG_getpid(), ##__VA_ARGS__);

    static void SLOG_set_output(FILE* output)
    {
         log_output = output;
    }
#else
    #define SLOG(a, ...)
#endif // (SLOGGING)

#if defined (SLOGGING_DEBUG)
    #define SLOG_DEBUG SLOG
#else
    #define SLOG_DEBUG(a, ...)
#endif // (SLOGGING_DEBUG)

#endif // SLOG_H_
