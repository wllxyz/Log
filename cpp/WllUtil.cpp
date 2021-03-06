#include <string.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <unistd.h>
using namespace std;
#include "WllUtil.h"
#include "WllConfigure.h"
using namespace Wll::Tool;
//using namespace Wll::Util;

char* Wll::Util::GetDateTimeStr(char* str,size_t size)
{
 static char buf[]="0000/00/00 00:00:00.000";  //for no reenter-process use

 if(str==NULL)
 {
  str=buf;
  size=sizeof(buf);
 }

 if(size<sizeof(buf)) return NULL;

        struct timeval now;
        struct tm now2;

        gettimeofday(&now,NULL);
        localtime_r(&now.tv_sec,&now2);
        snprintf(str,size,"%4.4d/%2.2d/%2.2d %2.2d:%2.2d:%2.2d.%3.3d",now2.tm_year+1900,now2.tm_mon+1,now2.tm_mday,now2.tm_hour,now2.tm_min,now2.tm_sec,int(now.tv_usec/1000));
        return str;
}

char* Wll::Util::GetDateStr(char* str,size_t size)
{
 static char buf[]="00000000";

 if(str==NULL)
 {
  str=buf;
  size=sizeof(buf);
 }

 if(size<sizeof(buf)) return NULL;

        time_t now;
        struct tm now2;
        time(&now);
        localtime_r(&now,&now2);
        snprintf(str,size,"%4.4d%2.2d%2.2d",now2.tm_year+1900, now2.tm_mon+1, now2.tm_mday);
        return str;
}

char* Wll::Util::GetProcessName(char* str, size_t size)
{
        static char buf[MAX_TEMP_BUF_LENGTH]="";

        if(str==NULL)
        {
                str=buf;
                size=sizeof(buf);
        }

 	if(size<=0) return NULL;

 	char process_cmdline_filename[MAX_TEMP_BUF_LENGTH]="";
 	char process_filepath[MAX_TEMP_BUF_LENGTH]="";
        snprintf(process_cmdline_filename,sizeof(process_cmdline_filename),"/proc/%d/exe",getpid());

        readlink(process_cmdline_filename,process_filepath,sizeof(process_filepath));

        char* p=strrchr(process_filepath,'/');

        p=(p==NULL?process_filepath:p+1);
 	strncpy(str,p,size-1);
 	str[size-1]=0;
 	return str;
}

char* Wll::Util::GetProcessDir(char* str, size_t size)
{
        static char buf[MAX_TEMP_BUF_LENGTH]="";

        if(str==NULL)
        {
                str=buf;
                size=sizeof(buf);
        }

 	if(size<=0) return NULL;

 	char process_cmdline_filename[MAX_TEMP_BUF_LENGTH]="";
 	char process_filepath[MAX_TEMP_BUF_LENGTH]="";
    snprintf(process_cmdline_filename,sizeof(process_cmdline_filename),"/proc/%d/exe",getpid());

    readlink(process_cmdline_filename,process_filepath,sizeof(process_filepath));

        char* p=strrchr(process_filepath,'/');

        if(p!=NULL) *p = 0;

 	strncpy(str,process_filepath,size-1);
 	str[size-1]=0;
 	return str;
}

long Wll::Util::GetFileLength(FILE* file)
{
        assert(file != NULL);

        long current_pos = ftell(file);
        int ret = fseek(file,0,SEEK_END);
        long length = ftell(file);
        //restore file position pointer
        fseek(file,current_pos,SEEK_SET);

        return (ret==0 ? length : -1);
}

char* Wll::Util::GetLogHome(char* buf, size_t size)
{
 static char tmp_buf[MAX_TEMP_BUF_LENGTH]="";
 
 if(buf==NULL)
 {
  buf=tmp_buf;
  size=sizeof(tmp_buf);
 }

 if(size<=0) return NULL;

 Configure config;
 config.Load();
 if(!config.Get("SYSTEM_ENVIRON","LOG_HOME",buf,size))
 {
  strncpy(buf,".",size);
  buf[size-1]=0;
 }
 return buf;
}

char* Wll::Util::GetLogConfigFile(char* buf,size_t size)
{
 static char tmp_buf[MAX_TEMP_BUF_LENGTH]="";

        if(buf==NULL)
        {
                buf=tmp_buf;
                size=sizeof(tmp_buf);
        }

 if(size<=0) return NULL;

 char log_home[MAX_TEMP_BUF_LENGTH]="";
 GetLogHome(log_home,sizeof(log_home));
 snprintf(buf,size,"%s/conf/log.cfg",log_home);

 return buf;
}

char* Wll::Util::GetLogPath(char* buf,size_t size)
{
        static char tmp_buf[MAX_TEMP_BUF_LENGTH]="";

        if(buf==NULL)
        {
                buf=tmp_buf;
                size=sizeof(tmp_buf);
        }

        if(size<=0) return NULL;

        char log_home[MAX_TEMP_BUF_LENGTH]="";
        GetLogHome(log_home,sizeof(log_home));
        snprintf(buf,size,"%s/logs",log_home);

 return buf;
 
}

