#include <stdio.h>
#include <unistd.h>
#include "log.h"

log *lg = NULL;


int main(int argc, char *argv[])
{
    int i = 0;
    lg = init_log(3, 1, "./");    
    
    //write_log(__FILE__, __LINE__, lg, INFO, "hello world! %s", "buff");
    log_info(lg, "hello world! %d %s", 123, "buff");
    log_info(lg, "aaaasssdd");
    while(1)
    {
        log_err(lg, "nihao %d", i++);
        sleep(1);
        if(i == 20)
        {
            break;
        }
    }
    
    log_err(lg, "hello nihao!");

    exit_log(lg);
    return 0;
}


