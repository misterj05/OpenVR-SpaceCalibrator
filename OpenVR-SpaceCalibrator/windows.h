#pragma once

// TODO remove
#define _In_
#define _In_opt_
using DWORD = int;
using BYTE = int;
using LSTATUS = int;
using HKEY = int;
using LPSTR = char*;
using LPTSTR = char*;
using BOOL = int;
using LPWSTR = wchar_t*;
using HINSTANCE = int;
int HKEY_CURRENT_USER_LOCAL_SETTINGS;
int RRF_RT_REG_SZ;
int REG_SZ;
int ERROR_SUCCESS;
int KEY_ALL_ACCESS;
int REG_NONE;
int FORMAT_MESSAGE_FROM_SYSTEM;
int FORMAT_MESSAGE_ALLOCATE_BUFFER;
int LANG_USER_DEFAULT;
int GENERIC_READ;
int GENERIC_WRITE;
int OPEN_EXISTING;
int INVALID_HANDLE_VALUE;
int PIPE_READMODE_MESSAGE;
int FORMAT_MESSAGE_IGNORE_INSERTS;
int LANG_NEUTRAL;
int SUBLANG_DEFAULT;
int ERROR_MORE_DATA;
constexpr int MAX_PATH = 1024;
int FormatMessageA(int, const char*, int, int, char*, int, char*);
void RegCloseKey(int);
int RegCreateKeyExA(int, const char*, int, int, int, int, int, int*, int);
int RegGetValueA(int, const char*, const char*, int, int, const char*, int*);
int RegSetValueExA(int, const char*, int, int, const int*, int);
void LocalFree(char*);
void CloseHandle(int);
void WaitNamedPipe(const char*, int);
int CreateFile(const char*, int, int, int, int, int, int);
int SetNamedPipeHandleState(int, int*, int, int);
char* TEXT(const char*);
int ReadFile(int, void*, int, int*, int);
int GetLastError();
int WriteFile(int, const void*, int, int*, int);
int MAKELANGID(int, int);
void AllocConsole();
void freopen_s(FILE**, const char*, const char*, FILE*);
void MessageBox(int*, const wchar_t*, const wchar_t*, int);
int lstrcmp(const wchar_t*, const wchar_t*);
void _getcwd(char*, int);