#ifndef __TDBTOOLS_H__
#define __TDBTOOLS_H__
#include "tdefine.h"
static bool _bfirst_ = true;
inline void print2windows(const char *pfile, const char *pfunname, int line, const char *args, ...)
{
	int	second = 0;
	time_t timep;
	struct tm *st;
#if TPLATFORM == TWIN
	timep = clock();
	second = (timep % 1000) * 1000;
	time(&timep);
#elif __MACH__ // OS X does not have clock_gettime, use clock_get_time
	struct timespec ts;
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts.tv_sec = mts.tv_sec;
	ts.tv_nsec = mts.tv_nsec;
	second = mts.tv_sec;
#else
	timeval tv;
	gettimeofday(&tv, NULL);
	timep = tv.tv_sec;
	second = (int)tv.tv_usec;
#endif
	st = localtime(&timep);	/* 获取本地时间 */
	/*(1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday,
		p->tm_hour, p->tm_min, p->tm_sec, second)*/
	if (_bfirst_)
	{
		_bfirst_ = false;
		printf("==========================================================\n");
		printf("==                     %02d-%02d-%02d                       ==\n", 1900 + st->tm_year, 1 + st->tm_mon, st->tm_mday);
		printf("==========================================================\n");
	}
	char message[1024];
	memset(message, 0, 1024);
	va_list ap;
	va_start(ap, args);
	vsnprintf(message, 1024, args, ap);
	va_end(ap);

	char file[256] = { 0 };
	strcpy(file, strrchr(pfile, '\\') == 0 ? pfile : strrchr(pfile, '\\') + 1);
	printf("[%02d:%02d:%02d:%03d] [%s] [Line in %d] [%s] : %s\n", st->tm_hour, st->tm_min, st->tm_sec, second, file, line, pfunname, message);
}
static char *LoadFile(const char* filename, TUINT32 &size)
{
	if (!filename)return NULL;
	std::fstream in(filename, std::ios::in | std::ios::binary);
	if (!in.is_open())
	{
		std::cerr << "LoadFile " << filename << " failed!" << std::endl;
		return NULL;
	}
	//文件大小
	in.seekg(0, std::ios::end);
	size = in.tellg();
	in.seekg(0, std::ios::beg);
	if (size <= 0)
	{
		return NULL;
	}
	char *data = new char[size];
	int readed = 0;
	while (!in.eof())
	{
		in.read((char*)data + readed, size - readed);
		if (in.gcount() > 0)
			readed += in.gcount();
		else
			break;
	}
	in.close();
	//LX_TYPE_BLOB;
	return data;
}
static bool SaveFile(const char * filename, const char *data, TUINT32 size)
{
	if (!data || size <= 0)
		return false;
	std::fstream out(filename, std::ios::out | std::ios::binary);
	if (!out.is_open())
	{
		std::cout << "SaveFile failed!open failed!" << filename << std::endl;
		return false;
	}
	out.write(data, size);
	out.close();
	return true;
}
#if TPLATFORM != TWIN
static size_t Convert(char *from_cha, char *to_cha, char *in, size_t inlen, char *out, size_t outlen)
{
	//转换上下文
	iconv_t cd;
	cd = iconv_open(to_cha, from_cha);
	if (cd == 0)
		return -1;
	memset(out, 0, outlen);
	char **pin = &in;
	char **pout = &out;
	//返回转换字节数的数量，但是转GBK时经常不正确 >=0就成功
	size_t re = iconv(cd, pin, &inlen, pout, &outlen);
	iconv_close(cd);
	return re;
}
#endif
static std::string UTF8ToGBK(const char *data)
{
	std::string re = "";
	//1 UFT8 转为unicode win utf16
#ifdef _WIN32
	//1.1 统计转换后字节数
	int len = MultiByteToWideChar(CP_UTF8,	//转换的格式
		0,			//默认的转换方式
		data,		//输入的字节
		-1,			//输入的字符串大小 -1 找\0
		0,//输出
		0//输出的空间大小
	);
	if (len <= 0)
		return re;
	std::wstring udata;
	udata.resize(len);
	MultiByteToWideChar(CP_UTF8, 0, data, -1, (wchar_t*)udata.data(), len);

	//2 unicode 转GBK
	len = WideCharToMultiByte(CP_ACP, 0, (wchar_t*)udata.data(), -1, 0, 0,
		0,	//失败默认替代字符
		0	//是否使用默认替代 
	);
	if (len <= 0)
		return re;
	re.resize(len);
	WideCharToMultiByte(CP_ACP, 0, (wchar_t*)udata.data(), -1, (char*)re.data(), len, 0, 0);
#else
	re.resize(1024);
	int inlen = strlen(data);
	Convert((char*)"utf-8", (char*)"gbk", (char*)data, inlen, (char*)re.data(), re.size());
	int outlen = strlen(re.data());
	re.resize(outlen);
#endif
	return re;
}
static std::string GBKToUTF8(const char *data)
{
	std::string re = "";
#ifdef _WIN32	
	//GBK转unicode
	//1.1 统计转换后字节数
	int len = MultiByteToWideChar(CP_ACP,	//转换的格式
		0,			//默认的转换方式
		data,		//输入的字节
		-1,			//输入的字符串大小 -1 找\0
		0,//输出
		0//输出的空间大小
	);
	if (len <= 0)
		return re;
	std::wstring udata;
	udata.resize(len);
	MultiByteToWideChar(CP_ACP, 0, data, -1, (wchar_t*)udata.data(), len);

	//2 unicode 转utf-8
	len = WideCharToMultiByte(CP_UTF8, 0, (wchar_t*)udata.data(), -1, 0, 0,
		0,	//失败默认替代字符
		0	//是否使用默认替代 
	);
	if (len <= 0)
		return re;
	re.resize(len);
	WideCharToMultiByte(CP_UTF8, 0, (wchar_t*)udata.data(), -1, (char*)re.data(), len, 0, 0);
#else
	re.resize(1024);
	int inlen = strlen(data);
	Convert((char*)"gbk", (char*)"utf-8", (char*)data, inlen, (char*)re.data(), re.size());
	int outlen = strlen(re.data());
	re.resize(outlen);
#endif
	return re;
}



#define Tprint(...) print2windows(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__);
#define CHECKHANDLE(x)     if(x == NULL){return DB_INVALID_PARAM;}


#endif

