#ifndef  __TDEFINE_H__
#define  __TDEFINE_H__

/***************************************|确认平台**********************************************/
#define		TWIN		0																	////
#define		TUNIX		1																	////
#define		TOSX		2																	////
#define		TANDROID	3																	////
																							////
#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )							////
#  define TPLATFORM			TWIN															////
#  define TPLATFORM_NAME	"win"															////
#elif defined( __APPLE_CC__ )																////
#  define TPLATFORM			TOSX															////
#  define TPLATFORM_NAME	"osx"															////
#elif defined( __ANDROID__ )																////
#  define TPLATFORM			TANDROID														////
#  define TPLATFORM_NAME	"android"														////
#else																						////
#  define TPLATFORM			TUNIX															////
#  define TPLATFORM_NAME	"unix"															////
#endif																						////
/***********************************************************************************************/

/**************************************|Include*************************************************/
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <string.h>
#include <map>
#include <vector>
#include <queue>
#include <assert.h>
#include <fstream>
#if TPLATFORM == TWIN																		////
#pragma warning(disable:4996)																////
#pragma warning(disable:4819)																////
#pragma warning(disable:4005)																////
#define WIN32_LEAN_AND_MEAN																	////																
#include <winsock2.h>
#include <windows.h> 
#include <process.h>
#include <mutex>																			////
#elif 	TPLATFORM == TUNIX																	////
#include <pthread.h> 																		////
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdarg.h>
#include <iconv.h>
#endif	

/***********************************************************************************************/
/**************************************Ttype****************************************************/
#if TPLATFORM == TWIN
typedef unsigned short				TUSHORT;
typedef signed __int64				TINT64;
typedef signed __int32				TINT32;
typedef signed __int16				TINT16;
typedef signed __int8				TINT8;
typedef unsigned __int64			TUINT64;
typedef unsigned __int32			TUINT32;
typedef unsigned __int16			TUINT16;
typedef unsigned __int8				TUINT8;
#else
typedef int64_t						TINT64;
typedef int32_t						TINT32;
typedef int16_t						TINT16;
typedef int8_t						TINT8;
typedef uint64_t					TUINT64;
typedef uint32_t					TUINT32;
typedef uint16_t					TUINT16;
typedef uint8_t						TUINT8;
#endif

#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )//Win
#ifdef __TEXPORTS__
#define TEXPORTS __declspec(dllexport)
#else
#define TEXPORTS __declspec(dllimport)
#endif
#else//Linux
#define  TEXPORTS
#endif
/**************************************|线程相关************************************************/
//#define  TThread_MutexAutoLock(x)			std::mutex x;std::lock_guard<std::mutex> instcance(x);
#if TPLATFORM == TWIN																		////
#define  TThread_Mutex						CRITICAL_SECTION								////
#define  TThread_IniMutex(x)				InitializeCriticalSection(&x);					////
#define  TThread_FiniMutex(x)				DeleteCriticalSection(&x);						////
#define  TThread_MutexLock(x)				EnterCriticalSection(&x);						////
#define  TThread_MutexunLock(x)				LeaveCriticalSection(&x);						////	
																							////
#else																						////
#define TThread_Mutex						pthread_mutex_t									////
#define TThread_IniMutex(x)					pthread_mutex_init (&x, NULL)					////
#define TThread_FiniMutex(x)				pthread_mutex_destroy(&x)						////
#define TThread_MutexLock(x)				pthread_mutex_lock(&x)							////
#define TThread_MutexunLock(x)				pthread_mutex_unlock(&x)						////
#endif																						////
/***********************************************************************************************/

#define STATIC_TCHECK(expr) { char strBuf[(expr) ? 1 : 0]; strBuf[0] = 0; };
#endif