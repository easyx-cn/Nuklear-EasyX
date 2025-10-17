#pragma once

#include <windows.h>
#include <graphics.h>

// 将 unicode 转换成 Multi 储存进 buffer 只向的内存
void UnicodeToMulti(const wchar_t* unicode, char** buffer)
{
	int size = WideCharToMultiByte(936, 0, unicode, -1, NULL, 0, NULL, NULL);

	//*buffer = new char[size + 1];		听说用这个申请的内存转换后不能释放？！！！？！？！？！s
	*buffer = (char*)malloc((size + 1) * sizeof(char));

	WideCharToMultiByte(936, 0, unicode, -1, *buffer, size, NULL, NULL);
}




char* UnicodeToANSI(const wchar_t* str)
{
	char* pElementText;
	int    iTextLen;
	iTextLen = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];

	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	WideCharToMultiByte(/*CP_ACP*/CP_UTF8, 0, str, -1, pElementText, iTextLen, NULL, NULL);
	return pElementText;
}

char* UnicodeToANSI2(const wchar_t* str)
{
	char* pElementText;
	int    iTextLen;
	iTextLen = WideCharToMultiByte(936, 0, str, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];

	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	WideCharToMultiByte(/*CP_ACP*/936, 0, str, -1, pElementText, iTextLen, NULL, NULL);
	return pElementText;
}

wchar_t* ANSIToUnicode(const char* str, int len = -1)
{
	int  unicodeLen = MultiByteToWideChar(CP_UTF8, 0, str, len, NULL, 0);
	wchar_t* pUnicode = (wchar_t*)malloc((unicodeLen + 1) * sizeof(wchar_t));
	if (pUnicode == NULL)
		return NULL;

	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, str, len, (LPWSTR)pUnicode, unicodeLen);
	return  pUnicode;
}

wchar_t* UTF8ToUnicode(const char* str)
{
	int  unicodeLen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	wchar_t* pUnicode;
	pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, str, -1, (LPWSTR)pUnicode, unicodeLen);
	return  pUnicode;
}

char* UTF8ToASCII(const char* str, int len = -1)
{
	int  unicodeLen = MultiByteToWideChar(CP_UTF8, 0, str, len, NULL, 0);
	wchar_t* pUnicode;
	pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, str, len, (LPWSTR)pUnicode, unicodeLen);

	char* pElementText;
	int    iTextLen;
	iTextLen = WideCharToMultiByte(CP_ACP, 0, pUnicode, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	WideCharToMultiByte(CP_ACP, 0, pUnicode, -1, pElementText, iTextLen, NULL, NULL);
	return  pElementText;
}

char* ASCIIToUTF8(const char* str)
{
	int  unicodeLen = MultiByteToWideChar(936, 0, str, -1, NULL, 0);
	wchar_t* pUnicode;
	pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(936, 0, str, -1, (LPWSTR)pUnicode, unicodeLen);

	char* pElementText;
	int    iTextLen;
	iTextLen = WideCharToMultiByte(CP_UTF8, 0, pUnicode, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	WideCharToMultiByte(CP_UTF8, 0, pUnicode, -1, pElementText, iTextLen, NULL, NULL);
	return  pElementText;
}

char* UnicodeToUTF8(const wchar_t* str)
{
	char* pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	WideCharToMultiByte(CP_UTF8, 0, str, -1, pElementText, iTextLen, NULL, NULL);

	return pElementText;
}



