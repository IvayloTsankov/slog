#ifndef SLOG_H_
#define SLOG_H_

#include <chrono>

// Installing:
//      When compile add -DSLOGGING or/and -DLOGGING_DEBUG
// Usage:
//      Same usage as printf
//      SLOG(<format_string>, param1, param2, ...);
//      SLOG_DEBUG(<format_string>, param1, param2, ...);
//
// Change outputfile:
//      SLOG_set_output(FILE* output);

#include <string>

static int64_t GetUTCInMilliseconds()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
           (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

// Simple logging mechanism
#if defined (SLOGGING)
	static FILE* log_output = stdout;
	#define SLOG(a, ...) fprintf(log_output, "(ts: %lld)(pid: %d) " a "\n", (long long int)GetUTCInMilliseconds(), ws_getpid(), ##__VA_ARGS__);
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
