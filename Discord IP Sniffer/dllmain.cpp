#include <windows.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")

void InitializeNetwork() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
}

void CloseNetwork() {
    WSACleanup();
}

std::string SnoopIP() {
    int octet1 = rand() % 256;
    int octet2 = rand() % 256;
    int octet3 = rand() % 256;
    int octet4 = rand() % 256;
    char ip[16];
    sprintf_s(ip, "%d.%d.%d.%d", octet1, octet2, octet3, octet4);
    return std::string(ip);
}

void CapturePackets() {
    Sleep(2000);
}

void SniffIP() {
    for (int i = 0; i < 3; ++i) {
        std::string randomIP = SnoopIP();
        MessageBoxA(NULL, randomIP.c_str(), "Sniffed IP Address", MB_OK);
        Sleep(1000);
    }
}

void StartFakeSniffer() {
    InitializeNetwork();
    CapturePackets();
    SniffIP();
    CloseNetwork();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C" __declspec(dllexport) void StartDiscordIPSniffer() {
    srand(time(NULL));
    StartFakeSniffer();
}
