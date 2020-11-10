#if defined(_WIN32) || defined(_WIN64)

#ifdef CALLBACK_EXPORTS

#define CALLBACK_API extern "C" __declspec(dllexport) 
#define CALLBACK_API_CALLBACK __stdcall

#else

#define CALLBACK_API extern "C" __declspec(dllimport)
#define CALLBACK_API_CALLBACK __stdcall

#endif

#else

#define CALLBACK_API extern "C"
#define CALLBACK_API_CALLBACK 

#endif

typedef void(CALLBACK_API_CALLBACK* ClickSignCallBack)(int nRet);


CALLBACK_API int CALLBACK_SetMsgCallBack(ClickSignCallBack pSignCallBack);

CALLBACK_API int SetRet(int nRet);