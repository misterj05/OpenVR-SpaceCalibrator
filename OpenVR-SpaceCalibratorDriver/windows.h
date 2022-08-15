#pragma once

#define WINAPI
#define ERROR_IO_PENDING 0
#define ERROR_PIPE_CONNECTED 1
#define OPENVRSPACECALIBRATORDRIVER_API
using BOOL = int;
using DWORD = int;
using LPVOID = void*;
using HANDLE = int;
using LPTSTR = char*;
struct OVERLAPPED {
	int hEvent;
};
using LPOVERLAPPED = OVERLAPPED*;
using LPOVERLAPPED_COMPLETION_ROUTINE = void*;
int MH_CreateHook(void*, void*, void**);
int MH_EnableHook(void*);
void MH_RemoveHook(void*);
char* MH_StatusToString(int);
int MH_Initialize();
void MH_Uninitialize();
int SetEvent(int);
void DisconnectNamedPipe(int);
void CloseHandle(int);
int CreateEvent(int, int, int, int);
int GetLastError();
int WaitForSingleObjectEx(int, int, int);
int GetOverlappedResult(int, OVERLAPPED*, int*, int);
char* TEXT(const char*);
int CreateNamedPipe(char*, int, int, int, int, int, int, int);
int ConnectNamedPipe(int, OVERLAPPED*);
int WriteFileEx(int, void*, int, OVERLAPPED*, LPOVERLAPPED_COMPLETION_ROUTINE);
int ReadFileEx(int, void*, int, OVERLAPPED*, LPOVERLAPPED_COMPLETION_ROUTINE);
int localtime_s(tm*, long int*);
extern int TRUE;
extern int FALSE;
extern int MH_OK;
extern int INFINITE;
extern int WAIT_IO_COMPLETION;
extern int PIPE_ACCESS_DUPLEX;
extern int FILE_FLAG_OVERLAPPED;
extern int PIPE_TYPE_MESSAGE;
extern int PIPE_READMODE_MESSAGE;
extern int PIPE_WAIT;
extern int PIPE_UNLIMITED_INSTANCES;
extern int INVALID_HANDLE_VALUE;
extern int ERROR_BROKEN_PIPE;