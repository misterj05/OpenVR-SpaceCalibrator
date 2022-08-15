#pragma once

using LPVOID = void*;
int MH_CreateHook(void*, void*, void**);
int MH_EnableHook(void*);
void MH_RemoveHook(void*);
char* MH_StatusToString(int);
int MH_Initialize();
void MH_Uninitialize();
int localtime_s(tm*, long int*);
extern int MH_OK;