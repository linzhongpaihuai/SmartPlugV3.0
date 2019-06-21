#include "../include/user_common.h"

#define LOG_PREFIX_BUF_SIZE 	(100)
#define LOG_BUF_SIZE 			(300)


//日志默认INFO级别
static uint8_t uiLogLevel = INFO;
static char *g_pcLogBuf = NULL;

void LOG_LogInit( void )
{
	//printf("LOG_LogInit start.\r\n");

 	g_pcLogBuf = (CHAR*)malloc( LOG_PREFIX_BUF_SIZE + LOG_BUF_SIZE + 5 );
	if ( NULL == g_pcLogBuf )
	{
		printf("[ERROR][%s:%d][%s]# malloc failed",	__FILE__, __LINE__, __func__);
		while(1);
	}
	//printf("LOG_LogInit over.\r\n");
}

void LOG_SetLogLevel( uint8_t ucLevel )
{
	if( ucLevel >= DEBUG && ucLevel <= NONE )
	{
		uiLogLevel = ucLevel;
	}
	else
	{
		printf("LOG_SetLogLevel failed, uiLevel: %d.\r\n", ucLevel);
	}
}


void LOG_Logout(uint8_t ucLevel, const char *pcFileName, int iLine, const char *pcfunc, char *pcFamt, ...)
{
	va_list Arg;
	char *pcPos = NULL;
	char *pcBuf = NULL;

	pcPos = pcBuf = g_pcLogBuf;

	if ( NULL == pcFamt)
	{
		return;
	}

	if ( ucLevel < uiLogLevel )
	{
		return;
	}

	switch ( ucLevel )
	{
	    case ERROR :
			pcPos += snprintf(pcBuf, LOG_PREFIX_BUF_SIZE, "[ERROR][%s:%d][%s]# ", pcFileName, iLine, pcfunc );
			break;
	    case WARN :
			pcPos += snprintf(pcBuf, LOG_PREFIX_BUF_SIZE, "[WARN][%s:%d][%s]# ", pcFileName, iLine, pcfunc );
			break;
	    case INFO :
			pcPos += snprintf(pcBuf, LOG_PREFIX_BUF_SIZE, "[INFO][%s:%d][%s]# ", pcFileName, iLine, pcfunc );
	        break;
	    case DEBUG :
			pcPos += snprintf(pcBuf, LOG_PREFIX_BUF_SIZE, "[DEBUG][%s:%d][%s]# ", pcFileName, iLine, pcfunc );
	        break;
	    default:
	        return;
	}

	va_start(Arg, pcFamt);
	pcPos += vsnprintf(pcPos, LOG_BUF_SIZE, pcFamt, Arg);
	va_end(Arg);


	pcPos += sprintf(pcPos,"\r\n");
	printf(pcBuf);

	//判断输出日志是否过大截断
	if ( (pcPos - pcBuf) > (LOG_BUF_SIZE + LOG_PREFIX_BUF_SIZE))
	{
		printf("[ERROR][%s:%d][%s]# Log too large has been cut off.\r\n", __FILE__, __LINE__, __func__);
	}
	return;
}

