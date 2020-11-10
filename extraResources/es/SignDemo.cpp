
//
#include "GSAndroidESSDK.h"
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>

#ifdef _LINUX
#include <unistd.h> 
#endif

using namespace std;
ADESSHandle Handle;
//
//struct
//{
//	int i;    
//	long long c1;  
//	char c2;  
//}x1;
//
//struct{
//	long long c1;  
//	int i;    
//	long long c2;  
//}x2;
//
//struct{
//	char c1;  
//	char c2; 
//	long long i;    
//}x3;

int main()
{
	//printf("%d\n",sizeof(x1));  // 16
	//printf("%d\n",sizeof(x2));  // 20
	//printf("%d\n",sizeof(x3));  // 12
	int nRet = ADESS_SDK_Init();
	cout << "你好 ADESS_SDK_Init nRet = " << nRet << endl;

	nRet = ADESS_SDK_CreateDevice(&Handle, E_ANDROID_V1, (char*)"192.168.37.164", 45008);
	cout << "ADESS_SDK_CreateDevice nRet = " << nRet << endl;

	//StruESSParam stESSParam;
	//memset(&stESSParam, 0, sizeof(StruESSParam));
	//stESSParam.eSignType = E_ANY_SIGN;

	//string strSrcpdf = "/home/luokejun/Desktop/release/test.pdf";
	//string strDestpdf = "/home/luokejun/Desktop/release/out.pdf";
	//memcpy(stESSParam.szPdfFilePath, (char*)strSrcpdf.c_str(), strSrcpdf.length());
	//memcpy(stESSParam.szOutPdfFilePath, (char*)strDestpdf.c_str(), strDestpdf.length());
	//nRet = ADESS_SDK_ClickSign(Handle, stESSParam);
	//cout << "ADESS_SDK_ClickSign nRet = " << nRet << endl;

	
	nRet = ADESS_SDK_DestoryDevice(Handle);
	cout << "ADESS_SDK_DestoryDevice nRet = " << nRet << endl;

	nRet = ADESS_SDK_UnInit();
	cout << "ADESS_SDK_UnInit nRet = " << nRet << endl;
	cin.get();
	return 0;
}

