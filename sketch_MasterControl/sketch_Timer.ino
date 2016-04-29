/*
该程序实现从DS1302中读取当前时间
并将时间按格式输出到buf中
*/
/* 日期变量缓存 */
char buf[50];
void t_time()
{
  /* 从 DS1302 获取当前时间 */
  Time t = rtc.time();
  /* 将日期代码格式化凑成buf等待输出 */
  snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",  t.yr, t.mon, t.date, t.hr, t.min, t.sec);
}

