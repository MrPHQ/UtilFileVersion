#include "stdafx.h"
#include "FileVersion.h"

/*
BOOL WINAPI VerQueryValue(
__in   LPCVOID pBlock, //由函数GetFileVersionInfo得到的版本信息源
__in   LPCTSTR lpSubBlock, //“/”表示该函数获取VS_FIXEDFILEINFO结构信息
	//为“/VarFileInfo/Translation”表示该函数获取文件的翻译表
	//为“/StringFileInfo/lang-codepage/string-name”表示该函数获取文件的字符串信息
__out  LPVOID *lplpBuffer, //返回指向pBlock指向的地址，当pBlock被释放时，该参数也被释放
__out  PUINT puLen //lplpBuffer指向的数据的字节大小
);

*/
CFileVersion::CFileVersion()
{
	m_lpVersionData = NULL;
	m_dwLangCharset = 0;
}


CFileVersion::~CFileVersion()
{
	Close();
}

void CFileVersion::Close()
{
	if (m_lpVersionData != NULL){
		delete[] m_lpVersionData;
		m_lpVersionData = NULL;
		m_dwLangCharset = 0;
	}
}
BOOL CFileVersion::Open(const char* lpszModuleName)
{
	assert(_tcslen(lpszModuleName) > 0);
	assert(m_lpVersionData == NULL);
	// Get the version information size for allocate the buffer  
	DWORD dwHandle;
	DWORD dwDataSize = ::GetFileVersionInfoSize((LPTSTR)lpszModuleName, &dwHandle);
	if (dwDataSize == 0)
		return FALSE;
	// Allocate buffer and retrieve version information  
	m_lpVersionData = new BYTE[dwDataSize];
	if (!::GetFileVersionInfo((LPTSTR)lpszModuleName, dwHandle, dwDataSize,(void*)m_lpVersionData))
	{
		LPVOID
		Close();
		return FALSE;
	}
	// Retrieve the first language and character-set identifier  
	UINT nQuerySize =0;
	DWORD* pTransTable = nullptr;
	if (!::VerQueryValue(m_lpVersionData, "\\VarFileInfo\\Translation",(void **)&pTransTable, &nQuerySize))
	{
		Close();
		return FALSE;
	}
	if (nullptr == pTransTable){
		return FALSE;
	}
	// Swap the words to have lang-charset in the correct format  
	m_dwLangCharset = MAKELONG(HIWORD(pTransTable[0]), LOWORD(pTransTable[0]));
	return TRUE;
}
int CFileVersion::QueryValue(const char* lpszValueName, char* buff, int len, DWORD dwLangCharset /* = 0*/)
{
	// Must call Open() first  
	assert(m_lpVersionData != NULL);

	// If no lang-charset specified use default  
	if (dwLangCharset == 0)
		dwLangCharset = m_dwLangCharset;
	// Query version information value  
	UINT nQuerySize;
	LPVOID lpData;
	char szStr[128];
	_snprintf_s(szStr, _TRUNCATE, "\\StringFileInfo\\%08lx\\%s",dwLangCharset, lpszValueName);
	if (::VerQueryValue((void **)m_lpVersionData, szStr, &lpData, &nQuerySize)){
		if (lpData != nullptr){
			memcpy(buff, lpData, min(nQuerySize, len - 1));
		}
	}
	return 0;
}
int CFileVersion::GetFixedInfo(VS_FIXEDFILEINFO& vsffi)
{
	// Must call Open() first  
	assert(m_lpVersionData != NULL);
	if (m_lpVersionData == NULL)
		return -1;
	UINT nQuerySize;
	VS_FIXEDFILEINFO* pVsffi = nullptr;
	if (::VerQueryValue((void **)m_lpVersionData, _T("\\"),
		(void**)&pVsffi, &nQuerySize))
	{
		if (pVsffi != nullptr){
			vsffi = *pVsffi;
		}
		return 0;
	}
	return -2;
}
int CFileVersion::GetFixedFileVersion(char* buff, int len)
{
	char szVersion[64];
	VS_FIXEDFILEINFO vsffi;

	szVersion[0] = '\0';
	if (GetFixedInfo(vsffi))
	{
		_snprintf_s(szVersion, _TRUNCATE, "%u,%u,%u,%u", HIWORD(vsffi.dwFileVersionMS),
			LOWORD(vsffi.dwFileVersionMS),
			HIWORD(vsffi.dwFileVersionLS),
			LOWORD(vsffi.dwFileVersionLS));
	}
	if (buff == nullptr){
		return -1;
	}
	strncpy_s(buff, len, szVersion, min(len - 1, strlen(szVersion)));
	return 0;
}
int CFileVersion::GetFixedProductVersion(char* buff, int len)
{
	char szVersion[64];
	VS_FIXEDFILEINFO vsffi;

	szVersion[0] = '\0';
	if (GetFixedInfo(vsffi))
	{
		_snprintf_s(szVersion, _TRUNCATE, "%u,%u,%u,%u", HIWORD(vsffi.dwProductVersionMS),
			LOWORD(vsffi.dwProductVersionMS),
			HIWORD(vsffi.dwProductVersionLS),
			LOWORD(vsffi.dwProductVersionLS));
	}
	strncpy_s(buff, len, szVersion, min(len - 1, strlen(szVersion)));
	return 0;
}