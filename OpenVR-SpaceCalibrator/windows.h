#pragma once

// TODO remove
#define _In_
#define _In_opt_
using LPWSTR = wchar_t*;
using HINSTANCE = int;
constexpr int MAX_PATH = 1024;
void AllocConsole();
void freopen_s(FILE**, const char*, const char*, FILE*);
void MessageBox(int*, const wchar_t*, const wchar_t*, int);
int lstrcmp(const wchar_t*, const wchar_t*);
void _getcwd(char*, int);