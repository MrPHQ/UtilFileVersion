#pragma once

#define FILE_VERSION_FIELD_DESCRI "FileDescription"
#define FILE_VERSION_FIELD_FVERSION "FileVersion"
#define FILE_VERSION_FIELD_INTERNAL_NAME "InternalName"
#define FILE_VERSION_FIELD_COMPANYNAME "CompanyName"
#define FILE_VERSION_FIELD_COPY_RIGHT "LegalCopyright"
#define FILE_VERSION_FIELD_ORIGINAL_NAME "OriginalFilename"
#define FILE_VERSION_FIELD_PRODUCT_NAME "ProductName"
#define FILE_VERSION_FIELD_PVERSION "ProductVersion"


class CFileVersion
{
public:
	CFileVersion();
	~CFileVersion();

public:
	BOOL Open(const char* file);
	void Close();
	int QueryValue(const char* lpszValueName, char* buff, int len, DWORD dwLangCharset = 0);
	int GetFileDescription(char* buff, int len){ return QueryValue("FileDescription", buff, len); };
	int GetFileVersion(char* buff, int len) { return QueryValue("FileVersion", buff, len); };
	int GetInternalName(char* buff, int len) { return QueryValue("InternalName", buff, len); };
	int GetCompanyName(char* buff, int len) { return QueryValue("CompanyName", buff, len); };
	int GetLegalCopyright(char* buff, int len) { return QueryValue("LegalCopyright", buff, len); };
	int GetOriginalFilename(char* buff, int len) { return QueryValue("OriginalFilename", buff, len); };
	int GetProductName(char* buff, int len) { return QueryValue("ProductName", buff, len); };
	int GetProductVersion(char* buff, int len) { return QueryValue("ProductVersion", buff, len); };
	int GetFixedInfo(VS_FIXEDFILEINFO& vsffi);
	int GetFixedFileVersion(char* buff, int len);
	int GetFixedProductVersion(char* buff, int len);
	// Attributes  
protected:
	BYTE*  m_lpVersionData;
	DWORD m_dwLangCharset;
};

