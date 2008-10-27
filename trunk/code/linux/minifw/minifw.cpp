// net_wrapper.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "minifw.h"
#include "iostream"

void MiniFwInit(void)
{
	//WSADATA wsaData;   // if this doesn't work
    //WSAData wsaData; // then try this instead

    //if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
    //    fprintf(stderr, "WSAStartup failed.\n");
    //    exit(1);
    //}

}
