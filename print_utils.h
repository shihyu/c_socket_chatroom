#ifndef __PRINT_UTILS_H__
#define __PRINT_UTILS_H__

/// 错误信息打印, 自动换行
void err_print(const char * str);

/// 标准的打印信息, 自动换行
void std_print(const char * str);

/// 打印信息, 自动换行
void trace(const char * format, ...);

#endif // __PRINT_UTILS_H__