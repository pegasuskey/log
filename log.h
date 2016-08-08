#ifndef __LOG_H__
#define __LOG_H__

/*  output  */
#define STDOUT    1
#define STDERR    2
#define FILEOUT   3

/*   LOG LEVEL   */
#define LEVEL_0   0
#define LEVEL_1   1
#define LEVEL_2   2
#define LEVEL_3   3
#define DEBUG     4

/*  LOG TYPE   */
#define INFO      0
#define ERR       1
#define WARN      2

typedef struct log
{
    int output;
    int level;
    FILE *fp;
}log;

// 以下宏定义 C99
// ## 作用 宏允许不带有__VA_ARG__ 参数
// gcc 下 允许 log_info(_log, _format, arg...) write_log(__FILE__, __LINE__,
// _log, INFO, _format, ##arg)
//
//
#define log_info(_log, _format, ...) \
    write_log(__FILE__, __LINE__, _log, INFO, _format, ##__VA_ARGS__)
#define log_err(_log, _format, ...) \
    write_log(__FILE__, __LINE__, _log, ERR, _format, ##__VA_ARGS__)
#define log_warn(_log, _format, ...) \
    write_log(__FILE__, __LINE__, _log, WARN, _format, ##__VA_ARGS__)

extern log *init_log(int output, int level, char *path);
extern void exit_log(log *lg);
extern void write_log(char *_file, int _line, log *lg, int type, char *format, ...);
#endif



