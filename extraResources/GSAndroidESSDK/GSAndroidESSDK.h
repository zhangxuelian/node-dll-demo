/**
* @copyright 2020-2030, 高新兴科技集团股份有限公司 Co.Ltd
* @author luokejun@gosuncn.com
* @version 1.0
* @date 2020-03-01
* @brief 提供GSAndroidESSDK对外接口
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

//签名板对象句柄
typedef void* ADESSHandle;  

//签名板类型
typedef enum _E_DevType
{
	E_ANDROID_V1 = 0,
}E_DevType;

typedef enum _E_MsgType
{
	E_None_Type = -1,		//无类型(错误)
	E_Start_Sign = 0,		//开始签名（可用于开始录像）	
	E_All_SignOk,			//所有签名确认ok
	E_Cancel_Sign,			//取消签名
	E_Sign_Busy,			//正在签名
	E_Record_Ok,			//录像文件接收完成
	E_Recvfile_Fail,		//接收文件失败
	E_Read_IdCardOk,		//读取身份证成功
	E_Net_Connect,			//网络正常(重连成功)
	E_Net_DisConnect,		//网络异常
	E_Dev_HardwareNormal,	//设备硬件运行正常
	E_Dev_HardwareFail,		//设备硬件运行不正常
	E_Camera_DisConnect,	//摄像头掉线
	E_TimeOut,				//超时
}E_MsgType;

//摄像头类型
typedef enum _E_CameraType
{
	E_Camera_Binocular = 0,	//双目摄像头
}E_CameraType;

//签名板摄像头标示
typedef enum _E_CameraLable
{
	E_Camera_1 = 0,			//上摄像头
	E_Camera_2 = 1,			//下摄像头
}E_CameraLable;

//签名类型
typedef enum _E_SignType
{
	E_ANY_SIGN = 0,			//任意位置签名
	E_SEPCIFIE_SIGN,		//指定位置签名
	E_ONLY_SIGN,			//仅签名捺印				
}E_SignType;

//签名时所传入参数
typedef struct _StruESSParam
{ 
	E_SignType	eSignType;					//签名类型（当为E_ONLY_SIGN，其他结构参数不用传）
	char szPdfFilePath[DATA_SIZE_512];		//取原PDF文件路径(路径可以是http可下载URL，也可以是本地路径：D:/test.pdf)
	char szOutPdfFilePath[DATA_SIZE_512];	//输出签名后的pdf路径(可以是http形式，也可以是本地路径)
	char szLocation[DATA_SIZE_512];			//签名位置：指定位置签名时有效（eSignType = E_SEPCIFIE_SIGN）
	bool bEncryption;					//是否启用加密（true为启用，暂未开放）
	int nFaceCheck;							//是否进行人脸检测(暂未开放)
}StruESSParam,*LPStruESSParam;

// 视频帧数据结构体
typedef struct _StruStreamFrame
{
	const char* data_y;		//Y分量数据
	const char* data_u;		//U分量数据
	const char* data_v;		//V分量数据
	int stride_y;			//Y分量步长
	int stride_u;			//U分量步长
	int stride_v;			//V分量步长
	int width;				//视频帧宽带
	int height;				//视频帧高度
}StruStreamFrame;

// 音频数据数据结构体
typedef struct _StruStreamAudio
{
	const void *data;		//音频数据
	int length;				//音频数据长度
	int bits;				//比特率
	int sample;				//采样率
	int channels;			//通道数
}StruStreamAudio;

/** 
* @brief	SDK初始化（调用一次）  
* @param	[in]szCameraSdkPath		rtc设备sdk路径（不传则内部加载默认sdk路径）
* @return	成功返回0,失败返回>0.
*/
ADNDROIDESS_API int ADESS_SDK_Init(char* szCameraSdkPath = "");

/** 
* @brief	SDK反初始化（调用一次）   
* @return	成功返回0,失败返回>0.
*/
ADNDROIDESS_API int ADESS_SDK_UnInit();

/**
* @brief	创建设备的Handle（调用一次） 
* @param	[out]pHandle				设备句柄指针
* @param	[in]eDevType				签字板类型（详细见结构定义E_DevType）
* @param	[in]szDevIp					设备对应IP
* @param	[in]nDevPort				设备对应端口号
* @return	成功返回0,失败返回>0.
*/
ADNDROIDESS_API int ADESS_SDK_CreateDevice(ADESSHandle *pHandle, E_DevType eDevType, char* szDevIp, int nDevPort);

/**
* @brief	销毁设备（调用一次） 
* @param	[in]pHandle				设备句柄指针	
* @return	成功返回0,失败返回>0.
*/
ADNDROIDESS_API int ADESS_SDK_DestoryDevice(ADESSHandle handle);

/**
* @brief	签名回调函数
* @param	[out]handle					设备句柄回调
* @param	[out]eMsgType				参照E_MsgType类型，然后获取szSignData对应数据
* @param	[out]szSignData				E_MsgType为E_All_SignOk时（签名捺印图片路径Json数据）,E_MsgType为其他类型时，为""
* @param	[out]szPdfBase64Data		E_MsgType为E_All_SignOk时,合成的pdfbase64数据（非CA认证数据）,E_MsgType为其他类型时，为""
* @param	[out]pUser					用户自定义数据
*/
typedef void(ADNDROIDESS_API_CALLBACK* ClickSignCallBack)(ADESSHandle handle, E_MsgType eMsgType, char* szSignJsonData, char* szPdfBase64Data, void* pUser);

/**
* @brief	设置消息回调函数（调用一次）
* @param	[in]pSignCallBack				签名回调（详见结构定义）
* @param	[in]pUser						用户自定义数据
* @return	成功返回0,失败返回>0.
*/
ADNDROIDESS_API int ADESS_SDK_SetMsgCallBack(ClickSignCallBack pSignCallBack, void* pUser);

/**
* @brief	手动校时
* @param	[in]Handle				设备句柄指针
* @param	[in]lCurrentTime		当前校时时间（毫秒）（如果不传此值，SDK内部会获取本地当前时间）
* @return	成功返回0,失败返回>0.
*/
ADNDROIDESS_API int ADESS_SDK_SetTime(ADESSHandle handle, unsigned __int64 lCurrentTime = 0);

/**
* @brief	获取设备序列号
* @param	[in]Handle				设备句柄指针	
* @param	[in]szSN				需分配的存储空间，可以是字符数组（如：char szSN[256]）			
* @param	[in]nLen				分配的长度,与szSN对应(256)
* @return	成功返回0,失败返回>0.
*/
ADNDROIDESS_API int ADESS_SDK_GetSN(ADESSHandle handle, char* szSN, int nLen);

/**
* @brief	获取设备信息
* @param	[in]Handle				设备句柄指针	
* @param	[in]szDevJsonInfo		需分配的存储空间，可以是字符数组（如：char szDevJsonInfo[512]）			
* @param	[in]nLen				分配的长度,与szSN对应(512)
* @return	成功返回0,失败返回>0.
*/
ADNDROIDESS_API int ADESS_SDK_GetDevInfo(ADESSHandle handle, char* szDevJsonInfo, int nLen);

/**
* @brief	签名接口
* @param	[in]handle						设备句柄指针	
* @param	[in]stESSParam				设备参数（详见结构定义StruESSParam），结构体中szOutPdfFilePath，在回调成功后，到指定路径获取
* @return	成功返回0,失败返回>0.
*/
ADNDROIDESS_API int ADESS_SDK_ClickSign(ADESSHandle handle, StruESSParam stESSParam);

/**
* @brief	PS：视频流格式为YUV420P，音频流格式为变频PCM
* @param	[out]hWnd					对应视频窗口句柄
* @param	[out]pStreamFrame			视频帧信息（可能为nullptr）
* @param	[out]pAudio					音频数据（可能为nullptr）
* @param	[out]pUser					用户定义的数据指针
*/
typedef void(ADNDROIDESS_API_CALLBACK *StreamCallBack)(void* hWnd, const StruStreamFrame *pStreamFrame, const StruStreamAudio *pAudio, void *pUser);

/**
* @brief	播放视频
* @param	[in]handle					设备句柄指针
* @param	[in]hWnd					窗口句柄
* @param	[in]eCameraType				摄像头类型
* @param	[in]eLable					摄像头标签
* @param	[in]pStreamCallBack			流数据回调(默认为0，为0时，渲染由本SDK内部渲染，否则上层自行根据回调参数数据渲染)
* @param	[in]pUser					用户自定义指针(默认为0)
备注：如果由SDK内部进行渲染，上层调用此接口时，不用传参数pStreamCallBack和pUser;
* @return	成功返回0,失败返回>0.
*/
ADNDROIDESS_API int ADESS_SDK_StartPlayVideo(ADESSHandle handle, void* hWnd, E_CameraType eCameraType, E_CameraLable eLable, StreamCallBack pStreamCallBack = 0, void* pUser = 0);

/**
* @brief	停止播放视频
* @param	[in]handle				设备句柄指针
* @return	成功返回0,失败返回>0.
*/
ADNDROIDESS_API int ADESS_SDK_StopPlayVideo(ADESSHandle handle);

/**
* @brief	录制视频
* @param	[in]handle					设备句柄指针
* @param	[in]hWnd					窗口句柄
* @param	[in]szVideoFilePath			录像保存路径(备注：可以是本地路径"D:\\test.mp4"，也可以是httpURL"http://....")
* @param	[in]eCameraType				摄像头类型
* @param	[in]bRemote					是否启用签名板端录像//true标示签名板录像（录像由签名板端录制完成后，回传给本端）
* @return	成功返回0,失败返回>0.
*/
ADNDROIDESS_API int ADESS_SDK_StartRecord(ADESSHandle handle, void* hWnd, const char* szVideoFilePath, E_CameraType eCameraType, bool bRemote);

/**
* @brief	停止录制视频（会停止所有正在录制的视频）
* @param	[in]handle				设备句柄指针
* @return	成功返回0,失败返回>0.
*/
ADNDROIDESS_API int ADESS_SDK_StopRecord(ADESSHandle handle);

/**
* @brief	远程取消签名
* @param	[in]handle				设备句柄指针
* @return	成功返回0,失败返回>0.
*/
ADNDROIDESS_API int ADESS_SDK_CancelSign(ADESSHandle handle);

/**
* @brief	重启签名app
* @param	[in]handle				设备句柄指针
* @return	成功返回0,失败返回>0.
*/
ADNDROIDESS_API int ADESS_SDK_ReStartApp(ADESSHandle handle);

#endif