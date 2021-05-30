#include <stdio.h>
#include <time.h>
 int main()
 {
    time_t begin,end;
    long i;
    begin= time(NULL);
    for(i = 0; i < 150000000; i++);
    end = time(NULL);
    printf("for loop used %f seconds to complete the " \
           "execution\n", difftime(end, begin));
    return 0;
}