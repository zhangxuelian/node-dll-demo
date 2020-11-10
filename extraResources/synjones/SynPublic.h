#pragma once
#pragma pack(1)
typedef struct tagIDCardData {
	char Name[32];		//����       
	char Sex[6];		//�Ա�
	char Nation[64];	//����
	char Born[18];		//��������
	char Address[72];	//סַ
	char IDCardNo[38];	//����֤��
	char GrantDept[32]; //��֤����
	char UserLifeBegin[18];	// ��Ч��ʼ����
	char UserLifeEnd[18];	// ��Ч��ֹ����
	char PassID[20];		// ͨ��֤����
	char IssuesTimes[6];	//ǩ������
	char reserved[12];		// ����
	char PhotoFileName[255];// ��Ƭ·��

	char CardType[4];    //֤������
	char EngName[122];   //Ӣ����
	char CertVol[6];     //֤���汾��

}IDCardData;
#pragma pack()

typedef int(*ProgressCallback)(int progress);
extern "C" {
	//////////////////////////////////////////////////////////////////////////
	//				SAM�˿ں���
	//
	//////////////////////////////////////////////////////////////////////////
	int _stdcall Syn_GetCOMBaud(int iPort, unsigned int *  puiBaudRate);
	int _stdcall Syn_SetCOMBaud(int iPort, unsigned int uiCurrBaud, unsigned int uiSetBaud);
	int _stdcall Syn_OpenPort(int iPort);
	int _stdcall Syn_ClosePort(int iPort);
	//////////////////////////////////////////////////////////////////////////
	//				SAM�ຯ��
	//
	//////////////////////////////////////////////////////////////////////////
	int _stdcall Syn_SetMaxRFByte(int	iPort, unsigned char ucByte, int	bIfOpen);
	int _stdcall Syn_ResetSAM(int  iPort, int	iIfOpen);
	int _stdcall Syn_GetSAMStatus(int iPort, int iIfOpen);
	int _stdcall Syn_GetSAMID(int iPort, unsigned char *	pucSAMID, int iIfOpen);
	int _stdcall Syn_GetSAMIDToStr(int iPort, char *	pcSAMID, int iIfOpen);
	//////////////////////////////////////////////////////////////////////////
	//				����֤���ຯ��
	//
	//////////////////////////////////////////////////////////////////////////
	int _stdcall Syn_StartFindIDCard(int iPort, unsigned char *	pucIIN, int	iIfOpen);
	int _stdcall Syn_SelectIDCard(int iPort, unsigned char * pucSN, int iIfOpen);
	int _stdcall Syn_ReadBaseMsg(
		int				iPort,
		unsigned char * pucCHMsg,
		unsigned int  * puiCHMsgLen,
		unsigned char * pucPHMsg,
		unsigned int  *	puiPHMsgLen,
		int				iIfOpen);
	int _stdcall Syn_ReadBaseMsgToFile(
		int 			iPort,
		char * 			pcCHMsgFileName,
		unsigned int *	puiCHMsgFileLen,
		char * 			pcPHMsgFileName,
		unsigned int  *	puiPHMsgFileLen,
		int				iIfOpen
		);
	int	_stdcall Syn_ReadBaseFPMsg(
		int				iPort,
		unsigned char *	pucCHMsg,
		unsigned int  *	puiCHMsgLen,
		unsigned char *	pucPHMsg,
		unsigned int  *	puiPHMsgLen,
		unsigned char *	pucFPMsg,
		unsigned int  *	puiFPMsgLen,
		int				iIfOpen
		);
	int	_stdcall Syn_ReadBaseFPMsgToFile(
		int				iPort,
		char *			pcCHMsgFileName,
		unsigned int *	puiCHMsgFileLen,
		char *			pcPHMsgFileName,
		unsigned int *	puiPHMsgFileLen,
		char *			pcFPMsgFileName,
		unsigned int *	puiFPMsgFileLen,
		int				iIfOpen
		);
	int _stdcall Syn_ReadNewAppMsg(int iPort, unsigned char * pucAppMsg, unsigned int * puiAppMsgLen, int iIfOpen);
	int _stdcall Syn_GetBmp(int iPort, char * Wlt_File);

	int _stdcall Syn_ReadMsg(int iPort, int iIfOpen, IDCardData *pIDCardData);
	int _stdcall Syn_ReadFPMsg(int iPort, int iIfOpen, IDCardData *pIDCardData, char * cFPhotoname);

	int _stdcall Syn_FindReader();
	int _stdcall Syn_FindUSBReader();

	int _stdcall Syn_BmpToJpeg(char * cBmpName, char * cJpegName);
	int _stdcall Syn_PhotoToStrBase64(char * cBase64, int * iLen, char *cPhotoName);
	int _stdcall Syn_StrBase64ToPhoto(char * cBase64, int iLen, char *cPhotoName);
	//////////////////////////////////////////////////////////////////////////
	//				���ø��ӹ��ܺ���
	//
	//////////////////////////////////////////////////////////////////////////
	int _stdcall Syn_SetPhotoPath(int iOption, char * cPhotoPath);
	int _stdcall Syn_SetPhotoType(int iType);
	int _stdcall Syn_SetPhotoName(int iType);
	int _stdcall Syn_SetPhotoNameEx(int iType, char * cPhotoname);
	int _stdcall Syn_SetSexType(int iType);
	int _stdcall Syn_SetNationType(int iType);
	int _stdcall Syn_SetBornType(int iType);
	int _stdcall Syn_SetUserLifeBType(int iType);
	int _stdcall Syn_SetUserLifeEType(int iType, int iOption);

	//////////////////////////////////////////////////////////////////////////
	//				USBHID����
	//
	//////////////////////////////////////////////////////////////////////////

	int _stdcall Syn_USBHIDM1Reset(int iPort, DWORD * pdwCardSN, unsigned char * pbSize);
	int _stdcall Syn_USBHIDM1AuthenKey(int iPort, unsigned char KeyType, unsigned char BlockNo, unsigned char * pKey);
	int _stdcall Syn_USBHIDM1ReadBlock(int iPort, unsigned char BlockNo, unsigned char * pBlock);
	int _stdcall Syn_USBHIDM1WriteBlock(int iPort, unsigned char BlockNo, unsigned char * pBlock);
	int _stdcall Syn_USBHIDM1Halt(int iPort);
	int _stdcall Syn_USBHIDReadFactoryInfo(
		int iPort,
		unsigned char * pFactory,
		unsigned char * pVol,
		unsigned char * pSerialNo,
		unsigned char * pReserved);
	int _stdcall Syn_USBHIDWriteFactoryInfo(
		int iPort,
		unsigned char * pFactory,
		unsigned char * pVol,
		unsigned char * pSerialNo,
		unsigned char * pReserved);
	int _stdcall Syn_USBHIDReadUserInfo(int iPort, unsigned char *pInfo);
	int _stdcall Syn_USBHIDWriteUserInfo(int iPort, unsigned char *pInfo);
	int _stdcall Syn_USBHIDGetMaxByte(int iPort, unsigned char *pSAMMaxByte, unsigned char *pARMVol);
	int _stdcall Syn_USBHIDSendSound(int iPort, unsigned char ucSound);
	int _stdcall Syn_USBHIDControlLED(int iPort, unsigned char ucLed);
	int _stdcall Syn_USBHIDControlBeep(int iPort, unsigned char ucType, unsigned short usTime);
	int _stdcall Syn_USBHIDGetSecCardID(int iPort, unsigned char * pdwCardSN);

	int _stdcall Syn_USBHIDSIMpowerOn(int iPort, unsigned char * ucATR, unsigned char * ucLen);
	int _stdcall Syn_USBHIDSIMpowerOff(int iPort);
	int _stdcall Syn_USBHIDSIMAPDU(int iPort, int slen, unsigned char *datasend, int* rlen, unsigned char* datareceive);
	int _stdcall Syn_USBHIDReadUserMac(int iPort, unsigned char *pMac);
	int _stdcall Syn_USBHIDWriteUserMac(int iPort, unsigned char *pMac);
	//add new interface
	//int _stdcall Syn_USBHIDSetTransportType(int iPort,int type);
	int _stdcall Syn_USBHIDSetUserIDCode(int iPort, unsigned char *code, int len);
	int _stdcall Syn_USBHIDIsEncryptMode(int iPort);
	int _stdcall Syn_USBHIDdoUpdate(int iPort, unsigned char *updateBuffer, long bufferLen, ProgressCallback progressCallback);
	//////////////////////////////////////////////////////////////////////////
	//				USBReade.dll USBHID����
	//
	//////////////////////////////////////////////////////////////////////////
	int _stdcall Syn_USBOpenPort(int iPort);
	int _stdcall Syn_USBClosePort(int iPort);
	int _stdcall Syn_USBSetMaxRFByte(int	iPort, unsigned char ucByte, int	bIfOpen);
	int _stdcall Syn_USBStartFindIDCard(int iPort, unsigned char *	pucIIN, int	iIfOpen);
	int _stdcall Syn_USBSelectIDCard(int iPort, unsigned char * pucSN, int iIfOpen);
	int _stdcall Syn_USBReadBaseMsg(
		int				iPort,
		unsigned char * pucCHMsg,
		unsigned int  * puiCHMsgLen,
		unsigned char * pucPHMsg,
		unsigned int  *	puiPHMsgLen,
		int				iIfOpen);
	int	_stdcall Syn_USBReadBaseFPMsg(
		int				iPort,
		unsigned char *	pucCHMsg,
		unsigned int  *	puiCHMsgLen,
		unsigned char *	pucPHMsg,
		unsigned int  *	puiPHMsgLen,
		unsigned char *	pucFPMsg,
		unsigned int  *	puiFPMsgLen,
		int				iIfOpen
		);
	int _stdcall Syn_USBReadNewAppMsg(int iPort, unsigned char * pucAppMsg, unsigned int * puiAppMsgLen, int iIfOpen);

	int _stdcall Syn_USBGetSAMID(int iPort, unsigned char *	pucSAMID, int iIfOpen);
	int _stdcall Syn_USBGetSAMIDToStr(int iPort, char *	pcSAMID, int iIfOpen);

	int _stdcall Syn_USBM1Reset(int iPort, DWORD * pdwCardSN, unsigned char * pbSize);
	int _stdcall Syn_USBM1AuthenKey(int iPort, unsigned char KeyType, unsigned char BlockNo, unsigned char * pKey);
	int _stdcall Syn_USBM1ReadBlock(int iPort, unsigned char BlockNo, unsigned char * pBlock);
	int _stdcall Syn_USBM1WriteBlock(int iPort, unsigned char BlockNo, unsigned char * pBlock);
	int _stdcall Syn_USBM1Halt(int iPort);
	int _stdcall Syn_USBReadFactoryInfo(
		int iPort,
		unsigned char * pFactory,
		unsigned char * pVol,
		unsigned char * pSerialNo,
		unsigned char * pReserved);
	int _stdcall Syn_USBWriteFactoryInfo(
		int iPort,
		unsigned char * pFactory,
		unsigned char * pVol,
		unsigned char * pSerialNo,
		unsigned char * pReserved);
	int _stdcall Syn_USBReadUserInfo(int iPort, unsigned char *pInfo);
	int _stdcall Syn_USBWriteUserInfo(int iPort, unsigned char *pInfo);
	int _stdcall Syn_USBGetMaxByte(int iPort, unsigned char *pSAMMaxByte, unsigned char *pARMVol);
	int _stdcall Syn_USBSendSound(int iPort, unsigned char ucSound);
	int _stdcall Syn_USBControlLED(int iPort, unsigned char ucLed);
	int _stdcall Syn_USBControlBeep(int iPort, unsigned char ucType, unsigned short usTime);

	int _stdcall Syn_USBGetSecCardID(int iPort, unsigned char * pdwCardSN);

	int _stdcall Syn_USBSIMpowerOn(int iPort, unsigned char * ucATR, unsigned char * ucLen);
	int _stdcall Syn_USBSIMpowerOff(int iPort);
	int _stdcall Syn_USBSIMAPDU(int iPort, int slen, unsigned char *datasend, int* rlen, unsigned char* datareceive);
	int _stdcall Syn_USBReadUserMac(int iPort, unsigned char *pMac);
	int _stdcall Syn_USBWriteUserMac(int iPort, unsigned char *pMac);
	int _stdcall Syn_USBPSAMpowerOn( int iPort, int slot, unsigned char * ucATR, unsigned char * ucLen);
	int _stdcall Syn_USBPSAMpowerOff( int iPort, int slot);
	int _stdcall Syn_USBPSAMAPDU(int iPort, int slot,int slen,unsigned char *datasend,int* rlen,unsigned char* datareceive);
	int _stdcall Syn_USBControlFingerLed( int iPort,unsigned char ucType,unsigned short usTime);
	int _stdcall Syn_PSAMpowerOn( int iPort, int slot, unsigned char * ucATR, unsigned char * ucLen);
	int _stdcall Syn_PSAMpowerOff( int iPort, int slot);
	int _stdcall Syn_PSAMAPDU(int iPort, int slot,int slen,unsigned char *datasend,int* rlen,unsigned char* datareceive);
	int _stdcall Syn_ControlFingerLed( int iPort,unsigned char ucType,unsigned short usTime);
	//add new interface
	//int _stdcall Syn_USBSetTransportType(int iPort,int type);
	int _stdcall Syn_USBSetUserIDCode(int iPort, unsigned char *code, int len);
	int _stdcall Syn_USBIsEncryptMode(int iPort);
	int _stdcall Syn_USBdoUpdate(int iPort, unsigned char *updateBuffer, long bufferLen, ProgressCallback progressCallback);


	//////////////////////////////////////////////////////////////////////////
	//				���ڲ���M1������
	//
	//////////////////////////////////////////////////////////////////////////

	int _stdcall Syn_SerialFindReader(int iPort, unsigned int* badurate);
	int _stdcall Syn_SerialOpen(int iPort, int badurate);
	int _stdcall Syn_SerialClose(int iPort);
	int _stdcall Syn_SerialM1Reset(int iPort, DWORD * pdwCardSN, unsigned char * pbSize);
	int _stdcall Syn_SerialM1AuthenKey(int iPort, unsigned char KeyType, unsigned char BlockNo, unsigned char * pKey);
	int _stdcall Syn_SerialM1ReadBlock(int iPort, unsigned char BlockNo, unsigned char * pBlock);
	int _stdcall Syn_SerialM1WriteBlock(int iPort, unsigned char BlockNo, unsigned char * pBlock);
	int _stdcall Syn_SerialM1Halt(int iPort);
	int _stdcall Syn_SerialStartFindCPUCard ( int iPort , unsigned char *	ATS,  int *rlen);
	int _stdcall Syn_SerialStartRemoveCPUCard ( int iPort , unsigned char * ATS);
	int _stdcall Syn_SerialPCTOCPUCard(int iPort,int slen,unsigned char *datasend,int* rlen,unsigned char* datareceive);
	int _stdcall Syn_SerialSIMpowerOn( int iPort,  unsigned char * ucATR , unsigned char * ucLen);
	int _stdcall Syn_SerialSIMpowerOff( int iPort);
	int _stdcall Syn_SerialSIMAPDU(int iPort,int slen,unsigned char *datasend,int* rlen,unsigned char* datareceive);
	int _stdcall Syn_SerialControlBeep( int iPort,unsigned char ucType,unsigned short usTime);
	int _stdcall Syn_SerialGetSecCardID( int iPort,  unsigned char * pdwCardSN);

	int _stdcall Syn_SerialPSAMpowerOn( int iPort, int slot, unsigned char * ucATR, unsigned char * ucLen);
	int _stdcall Syn_SerialPSAMpowerOff( int iPort, int slot);
	int _stdcall Syn_SerialPSAMAPDU(int iPort, int slot,int slen,unsigned char *datasend,int* rlen,unsigned char* datareceive);
	int _stdcall Syn_SerialControlFingerLed( int iPort,unsigned char ucType,unsigned short usTime);

	int _stdcall Syn_SerialReadUserInfo( int iPort,unsigned char *pInfo);
	int _stdcall Syn_SerialWriteUserInfo( int iPort,unsigned char *pInfo);

	int _stdcall Syn_USBStartFindCPUCard(int iPort, unsigned char *	ATS, int *rlen);
	int _stdcall Syn_StartFindCPUCard(int iPort, unsigned char * ATS, int *rlen);

	int _stdcall Syn_USBStartRemoveCPUCard(int iPort, unsigned char *	ATS);
	int _stdcall Syn_StartRemoveCPUCard(int iPort, unsigned char * ATS);

	int _stdcall Syn_USBPCTOCPUCard(int iPort, int slen, unsigned char *datasend, int* rlen, unsigned char* datareceive);
	int _stdcall Syn_PCTOCPUCard(int iPort, int slen, unsigned char *datasend, int* rlen, unsigned char* datareceive);

}