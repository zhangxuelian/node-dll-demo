/**
* @copyright 2020-2030, �����˿Ƽ����Źɷ����޹�˾ Co.Ltd
* @author luokejun@gosuncn.com
* @version 1.0
* @date 2020-03-01
* @brief �ṩGSAndroidESSDK����ӿ�
* @details
*/

#ifndef _ELECTRONICSS_ADSDK_H_
#define _ELECTRONICSS_ADSDK_H_

#if defined(_WIN32) || defined(_WIN64)

#ifdef GSANDROIDESSDK_EXPORTS

#define ADNDROIDESS_API extern "C" __declspec(dllexport) 
#define ADNDROIDESS_API_CALLBACK __stdcall

#else

#define ADNDROIDESS_API extern "C" __declspec(dllimport)
#define ADNDROIDESS_API_CALLBACK __stdcall

#endif

#else

#define ADNDROIDESS_API extern "C"
#define ADNDROIDESS_API_CALLBACK 

#endif

#define DATA_SIZE_512		512
#define DATA_SIZE_256		256
#define DATA_SIZE_128		128
#define DATA_SIZE_64		64

//ǩ���������
typedef void* ADESSHandle;  

//ǩ��������
typedef enum _E_DevType
{
	E_ANDROID_V1 = 0,
}E_DevType;

typedef enum _E_MsgType
{
	E_None_Type = -1,		//������(����)
	E_Start_Sign = 0,		//��ʼǩ���������ڿ�ʼ¼��	
	E_All_SignOk,			//����ǩ��ȷ��ok
	E_Cancel_Sign,			//ȡ��ǩ��
	E_Sign_Busy,			//����ǩ��
	E_Record_Ok,			//¼���ļ��������
	E_Recvfile_Fail,		//�����ļ�ʧ��
	E_Read_IdCardOk,		//��ȡ���֤�ɹ�
	E_Net_Connect,			//��������(�����ɹ�)
	E_Net_DisConnect,		//�����쳣
	E_Dev_HardwareNormal,	//�豸Ӳ����������
	E_Dev_HardwareFail,		//�豸Ӳ�����в�����
	E_Camera_DisConnect,	//����ͷ����
	E_TimeOut,				//��ʱ
}E_MsgType;

//����ͷ����
typedef enum _E_CameraType
{
	E_Camera_Binocular = 0,	//˫Ŀ����ͷ
}E_CameraType;

//ǩ��������ͷ��ʾ
typedef enum _E_CameraLable
{
	E_Camera_1 = 0,			//������ͷ
	E_Camera_2 = 1,			//������ͷ
}E_CameraLable;

//ǩ������
typedef enum _E_SignType
{
	E_ANY_SIGN = 0,			//����λ��ǩ��
	E_SEPCIFIE_SIGN,		//ָ��λ��ǩ��
	E_ONLY_SIGN,			//��ǩ����ӡ				
}E_SignType;

//ǩ��ʱ���������
typedef struct _StruESSParam
{ 
	E_SignType	eSignType;					//ǩ�����ͣ���ΪE_ONLY_SIGN�������ṹ�������ô���
	char szPdfFilePath[DATA_SIZE_512];		//ȡԭPDF�ļ�·��(·��������http������URL��Ҳ�����Ǳ���·����D:/test.pdf)
	char szOutPdfFilePath[DATA_SIZE_512];	//���ǩ�����pdf·��(������http��ʽ��Ҳ�����Ǳ���·��)
	char szLocation[DATA_SIZE_512];			//ǩ��λ�ã�ָ��λ��ǩ��ʱ��Ч��eSignType = E_SEPCIFIE_SIGN��
	bool bEncryption;					//�Ƿ����ü��ܣ�trueΪ���ã���δ���ţ�
	int nFaceCheck;							//�Ƿ�����������(��δ����)
}StruESSParam,*LPStruESSParam;

// ��Ƶ֡���ݽṹ��
typedef struct _StruStreamFrame
{
	const char* data_y;		//Y��������
	const char* data_u;		//U��������
	const char* data_v;		//V��������
	int stride_y;			//Y��������
	int stride_u;			//U��������
	int stride_v;			//V��������
	int width;				//��Ƶ֡���
	int height;				//��Ƶ֡�߶�
}StruStreamFrame;

// ��Ƶ�������ݽṹ��
typedef struct _StruStreamAudio
{
	const void *data;		//��Ƶ����
	int length;				//��Ƶ���ݳ���
	int bits;				//������
	int sample;				//������
	int channels;			//ͨ����
}StruStreamAudio;

/** 
* @brief	SDK��ʼ��������һ�Σ�  
* @param	[in]szCameraSdkPath		rtc�豸sdk·�����������ڲ�����Ĭ��sdk·����
* @return	�ɹ�����0,ʧ�ܷ���>0.
*/
ADNDROIDESS_API int ADESS_SDK_Init(char* szCameraSdkPath = "");

/** 
* @brief	SDK����ʼ��������һ�Σ�   
* @return	�ɹ�����0,ʧ�ܷ���>0.
*/
ADNDROIDESS_API int ADESS_SDK_UnInit();

/**
* @brief	�����豸��Handle������һ�Σ� 
* @param	[out]pHandle				�豸���ָ��
* @param	[in]eDevType				ǩ�ְ����ͣ���ϸ���ṹ����E_DevType��
* @param	[in]szDevIp					�豸��ӦIP
* @param	[in]nDevPort				�豸��Ӧ�˿ں�
* @return	�ɹ�����0,ʧ�ܷ���>0.
*/
ADNDROIDESS_API int ADESS_SDK_CreateDevice(ADESSHandle *pHandle, E_DevType eDevType, char* szDevIp, int nDevPort);

/**
* @brief	�����豸������һ�Σ� 
* @param	[in]pHandle				�豸���ָ��	
* @return	�ɹ�����0,ʧ�ܷ���>0.
*/
ADNDROIDESS_API int ADESS_SDK_DestoryDevice(ADESSHandle handle);

/**
* @brief	ǩ���ص�����
* @param	[out]handle					�豸����ص�
* @param	[out]eMsgType				����E_MsgType���ͣ�Ȼ���ȡszSignData��Ӧ����
* @param	[out]szSignData				E_MsgTypeΪE_All_SignOkʱ��ǩ����ӡͼƬ·��Json���ݣ�,E_MsgTypeΪ��������ʱ��Ϊ""
* @param	[out]szPdfBase64Data		E_MsgTypeΪE_All_SignOkʱ,�ϳɵ�pdfbase64���ݣ���CA��֤���ݣ�,E_MsgTypeΪ��������ʱ��Ϊ""
* @param	[out]pUser					�û��Զ�������
*/
typedef void(ADNDROIDESS_API_CALLBACK* ClickSignCallBack)(ADESSHandle handle, E_MsgType eMsgType, char* szSignJsonData, char* szPdfBase64Data, void* pUser);

/**
* @brief	������Ϣ�ص�����������һ�Σ�
* @param	[in]pSignCallBack				ǩ���ص�������ṹ���壩
* @param	[in]pUser						�û��Զ�������
* @return	�ɹ�����0,ʧ�ܷ���>0.
*/
ADNDROIDESS_API int ADESS_SDK_SetMsgCallBack(ClickSignCallBack pSignCallBack, void* pUser);

/**
* @brief	�ֶ�Уʱ
* @param	[in]Handle				�豸���ָ��
* @param	[in]lCurrentTime		��ǰУʱʱ�䣨���룩�����������ֵ��SDK�ڲ����ȡ���ص�ǰʱ�䣩
* @return	�ɹ�����0,ʧ�ܷ���>0.
*/
ADNDROIDESS_API int ADESS_SDK_SetTime(ADESSHandle handle, unsigned __int64 lCurrentTime = 0);

/**
* @brief	��ȡ�豸���к�
* @param	[in]Handle				�豸���ָ��	
* @param	[in]szSN				�����Ĵ洢�ռ䣬�������ַ����飨�磺char szSN[256]��			
* @param	[in]nLen				����ĳ���,��szSN��Ӧ(256)
* @return	�ɹ�����0,ʧ�ܷ���>0.
*/
ADNDROIDESS_API int ADESS_SDK_GetSN(ADESSHandle handle, char* szSN, int nLen);

/**
* @brief	��ȡ�豸��Ϣ
* @param	[in]Handle				�豸���ָ��	
* @param	[in]szDevJsonInfo		�����Ĵ洢�ռ䣬�������ַ����飨�磺char szDevJsonInfo[512]��			
* @param	[in]nLen				����ĳ���,��szSN��Ӧ(512)
* @return	�ɹ�����0,ʧ�ܷ���>0.
*/
ADNDROIDESS_API int ADESS_SDK_GetDevInfo(ADESSHandle handle, char* szDevJsonInfo, int nLen);

/**
* @brief	ǩ���ӿ�
* @param	[in]handle						�豸���ָ��	
* @param	[in]stESSParam				�豸����������ṹ����StruESSParam�����ṹ����szOutPdfFilePath���ڻص��ɹ��󣬵�ָ��·����ȡ
* @return	�ɹ�����0,ʧ�ܷ���>0.
*/
ADNDROIDESS_API int ADESS_SDK_ClickSign(ADESSHandle handle, StruESSParam stESSParam);

/**
* @brief	PS����Ƶ����ʽΪYUV420P����Ƶ����ʽΪ��ƵPCM
* @param	[out]hWnd					��Ӧ��Ƶ���ھ��
* @param	[out]pStreamFrame			��Ƶ֡��Ϣ������Ϊnullptr��
* @param	[out]pAudio					��Ƶ���ݣ�����Ϊnullptr��
* @param	[out]pUser					�û����������ָ��
*/
typedef void(ADNDROIDESS_API_CALLBACK *StreamCallBack)(void* hWnd, const StruStreamFrame *pStreamFrame, const StruStreamAudio *pAudio, void *pUser);

/**
* @brief	������Ƶ
* @param	[in]handle					�豸���ָ��
* @param	[in]hWnd					���ھ��
* @param	[in]eCameraType				����ͷ����
* @param	[in]eLable					����ͷ��ǩ
* @param	[in]pStreamCallBack			�����ݻص�(Ĭ��Ϊ0��Ϊ0ʱ����Ⱦ�ɱ�SDK�ڲ���Ⱦ�������ϲ����и��ݻص�����������Ⱦ)
* @param	[in]pUser					�û��Զ���ָ��(Ĭ��Ϊ0)
��ע�������SDK�ڲ�������Ⱦ���ϲ���ô˽ӿ�ʱ�����ô�����pStreamCallBack��pUser;
* @return	�ɹ�����0,ʧ�ܷ���>0.
*/
ADNDROIDESS_API int ADESS_SDK_StartPlayVideo(ADESSHandle handle, void* hWnd, E_CameraType eCameraType, E_CameraLable eLable, StreamCallBack pStreamCallBack = 0, void* pUser = 0);

/**
* @brief	ֹͣ������Ƶ
* @param	[in]handle				�豸���ָ��
* @return	�ɹ�����0,ʧ�ܷ���>0.
*/
ADNDROIDESS_API int ADESS_SDK_StopPlayVideo(ADESSHandle handle);

/**
* @brief	¼����Ƶ
* @param	[in]handle					�豸���ָ��
* @param	[in]hWnd					���ھ��
* @param	[in]szVideoFilePath			¼�񱣴�·��(��ע�������Ǳ���·��"D:\\test.mp4"��Ҳ������httpURL"http://....")
* @param	[in]eCameraType				����ͷ����
* @param	[in]bRemote					�Ƿ�����ǩ�����¼��//true��ʾǩ����¼��¼����ǩ�����¼����ɺ󣬻ش������ˣ�
* @return	�ɹ�����0,ʧ�ܷ���>0.
*/
ADNDROIDESS_API int ADESS_SDK_StartRecord(ADESSHandle handle, void* hWnd, const char* szVideoFilePath, E_CameraType eCameraType, bool bRemote);

/**
* @brief	ֹͣ¼����Ƶ����ֹͣ��������¼�Ƶ���Ƶ��
* @param	[in]handle				�豸���ָ��
* @return	�ɹ�����0,ʧ�ܷ���>0.
*/
ADNDROIDESS_API int ADESS_SDK_StopRecord(ADESSHandle handle);

/**
* @brief	Զ��ȡ��ǩ��
* @param	[in]handle				�豸���ָ��
* @return	�ɹ�����0,ʧ�ܷ���>0.
*/
ADNDROIDESS_API int ADESS_SDK_CancelSign(ADESSHandle handle);

/**
* @brief	����ǩ��app
* @param	[in]handle				�豸���ָ��
* @return	�ɹ�����0,ʧ�ܷ���>0.
*/
ADNDROIDESS_API int ADESS_SDK_ReStartApp(ADESSHandle handle);

#endif