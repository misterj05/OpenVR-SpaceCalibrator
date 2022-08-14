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
extern int HKEY_CURRENT_USER_LOCAL_SETTINGS;
extern int RRF_RT_REG_SZ;
extern int REG_SZ;
extern int ERROR_SUCCESS;
extern int KEY_ALL_ACCESS;
extern int REG_NONE;
extern int FORMAT_MESSAGE_FROM_SYSTEM;
extern int FORMAT_MESSAGE_ALLOCATE_BUFFER;
extern int LANG_USER_DEFAULT;
extern int GENERIC_READ;
extern int GENERIC_WRITE;
extern int OPEN_EXISTING;
extern int INVALID_HANDLE_VALUE;
extern int PIPE_READMODE_MESSAGE;
extern int FORMAT_MESSAGE_IGNORE_INSERTS;
extern int LANG_NEUTRAL;
extern int SUBLANG_DEFAULT;
extern int ERROR_MORE_DATA;
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