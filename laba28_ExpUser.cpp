#define _WIN32_WINNT 0x0500
#define UNICODE
#ifdef UNICODE
#define _UNICODE
#endif
#include <windows.h>
#include <stdio.h>
#include <sddl.h>
void main(void) {
	wchar_t UserName[256];
	DWORD MaxUserNameLength = 256; // int -> DWORD
	SID Sid[1024];
	PSID pSid;
	LPTSTR StringSid;
	DWORD SidSize = 1024;
	SID_NAME_USE SidType;
	LPTSTR DomainName = NULL;
	DWORD DomainNameSize = 16; // длина имени домена
	HANDLE hHeap;
	hHeap = GetProcessHeap();
	pSid = &Sid[0];
	GetUserName(UserName, &MaxUserNameLength); // получаем имя пользователя
	DomainName = (LPTSTR)HeapAlloc(hHeap, 0, DomainNameSize * sizeof(TCHAR));
	LookupAccountName(
		NULL, // локальный компьютер
		UserName, pSid, &SidSize, DomainName, &DomainNameSize, &SidType);
	if (!ConvertSidToStringSid(pSid, &StringSid)) /* память для строки выделяет сама функция */
		printf("Convert SID to string SID failed.");
	wprintf(L"StringSid %s\n", StringSid);
	LocalFree(StringSid);
	HeapFree(hHeap, 0, DomainName);
}