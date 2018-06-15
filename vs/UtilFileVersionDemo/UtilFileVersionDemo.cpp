// UtilFileVersionDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FileVersion.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::cin.ignore();
	{
		CFileVersion cFileVer;
		cFileVer.Open("utils.dll");
		char szTmp[128];
		szTmp[0] = '\0';
		cFileVer.GetFileDescription(szTmp, 128);
		std::cout << "FileDescription" <<"\t"<< szTmp << std::endl;
		szTmp[0] = '\0';
		cFileVer.GetFileVersion(szTmp, 128);
		std::cout << "FileVersion" << "\t" << szTmp << std::endl;
		szTmp[0] = '\0';
		cFileVer.GetInternalName(szTmp, 128);
		std::cout << "InternalName" << "\t" << szTmp << std::endl;
		szTmp[0] = '\0';
		cFileVer.GetCompanyName(szTmp, 128);
		std::cout << "CompanyName" << "\t" << szTmp << std::endl;
		szTmp[0] = '\0';
		cFileVer.GetLegalCopyright(szTmp, 128);
		std::cout << "LegalCopyright" << "\t" << szTmp << std::endl;
		szTmp[0] = '\0';
		cFileVer.GetOriginalFilename(szTmp, 128);
		std::cout << "OriginalFilename" << "\t" << szTmp << std::endl;
		szTmp[0] = '\0';
		cFileVer.GetProductName(szTmp, 128);
		std::cout << "ProductName" << "\t" << szTmp << std::endl;
		szTmp[0] = '\0';
		cFileVer.GetProductVersion(szTmp, 128);
		std::cout << "ProductVersion" << "\t" << szTmp << std::endl;
	}
	std::cin.ignore();
	return 0;
}

