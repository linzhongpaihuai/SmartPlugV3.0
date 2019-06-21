#ifndef __USER_LOG_H__
#define __USER_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif





#define LOG_OUT_ENABLE 	(1)

#define NONE       5
#define ERROR      4
#define WARN       3
#define INFO       2
#define DEBUG      1



#if LOG_OUT_ENABLE

	#define GET_FILE_NAME(str) 	((strrchr(str,'/')) ? (strrchr(str,'/')+1) : str)

	#define LOG_OUT(Level, Fmt, Args...) LOG_Logout((uint8_t)Level, GET_FILE_NAME(__FILE__), __LINE__, __func__, Fmt, ##Args)
#else
	#define LOG_OUT(Level, Fmt, Args...) 
#endif

void LOG_LogInit( void );
void LOG_SetLogLevel( uint8_t ucLevel );
void LOG_Logout(uint8_t ucLevel, const char *pcFileName, int iLine, const char *pcfunc, char *pcFamt, ...);

#ifdef __cplusplus
}
#endif

#endif

