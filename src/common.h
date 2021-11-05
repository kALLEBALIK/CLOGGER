#ifndef CLOGGER_COMMON_H
#define CLOGGER_COMMON_H

#include <Windows.h>

#define CHARSZ sizeof(CHAR)

#define STATE_NONE 0
#define STATE_SHIFT 1
#define STATE_CONTROL 2
#define STATE_ALT 4
#define STATE_CAPS 32

inline unsigned __fastcall GetLen(CHAR* str) {
    return (UINT)(strlen(str) * sizeof(CHAR));
}

#endif

