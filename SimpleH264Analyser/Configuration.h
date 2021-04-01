#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <fstream>
//定义宏，是否显示数据，是否向日志文件中输入数据
#define TRACE_CONFIG_CONSOLE 1
#define TRACE_CONFIG_LOGOUT 1
//为了能够全局使用，定义一个全局变量
extern std::ofstream g_traceFile;
#endif // !_CONFIGURATION_H_



