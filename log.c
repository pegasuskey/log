#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>  // va_list  ***
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "log.h"

log *init_log(int output, int level, char *path)
{
    FILE *fp = NULL;

    log *wlog = (log *)malloc(sizeof(log));
    if(!wlog)
    {
        printf("\nfatal error:malloc fail\n");
        return NULL;
    }

    if(output == FILEOUT)
    {
        fp = fopen("msg.log", "w");
        if(!fp)
        {
            printf("\nfatal error:create log file fail\n");
            free(wlog);
            return NULL;
        }
        wlog->fp = fp;
        setvbuf(wlog->fp, (char *)NULL, _IOLBF, BUFSIZ);
    }
    else
    {
        wlog->fp = NULL;
        setvbuf(stdout, (char *)NULL, _IONBF, BUFSIZ);
        setvbuf(stderr, (char *)NULL, _IONBF, BUFSIZ);
    }
    wlog->output = output;
    wlog->level = level;

    return wlog;
}

void exit_log(log *lg)
{
    if(lg->output == FILEOUT)
    {
        fclose(lg->fp);
    }
    free(lg);
}


/*
 *  level ???
 *
 *
 *
 */
void write_log(char *_file, int _line, log *lg, int type, char *format, ...)
{
    va_list va_value;
    struct tm *tm;
    struct timeval tv;
    char type_buf[256];
    //time_t now;

    /* 获取当前时间  */
    //time(&now);
    gettimeofday(&tv, NULL);
    tm = localtime(&tv.tv_sec);

    if(!format)
    {
        printf("\n[FATAL ERROR: No set format]\n");
        return;
    }
    
    if(type == INFO)
    {
        sprintf(type_buf, "-INFO ");
    }
    else if(type == ERR)
    {
        sprintf(type_buf, "(%s:%d)-ERR ", _file, _line);
    }
    else if(type == WARN)
    {
        sprintf(type_buf, "(%s:%d)-WARN ", _file, _line);
    }
    else
    {
        sprintf(type_buf, "(%s:%d)-DEBUG ", _file, _line);
    }

    va_start(va_value, format);
    if(lg->output == STDOUT)
    {
        fprintf(stdout, "[%04d-%02d-%02d %02d:%02d:%02d.%03d]%s", tm->tm_year+1900, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, tv.tv_usec/1000, type_buf);  
        vfprintf(stdout, format, va_value);
        fprintf(stdout, "\n");
    }
    else if(lg->output == STDERR)
    {
        fprintf(stderr, "[%02d-%02d-%02d %02d:%02d:%02d.%03d]%s", tm->tm_year+1900, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, tv.tv_usec/1000, type_buf);  
        vfprintf(stderr, format, va_value);
        fprintf(stderr, "\n");
    
    }
    else if(lg->output == FILEOUT)
    {
        fprintf(lg->fp, "[%02d-%02d-%02d %02d:%02d:%02d.%03d]%s", tm->tm_year+1900, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, tv.tv_usec/1000, type_buf);  
        vfprintf(lg->fp, format, va_value);
        fprintf(lg->fp, "\n");
    }

    va_end(va_value);

    return;
}


