#include <iostream>
#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 30

using namespace std;

int main(int argc, char* argv[])
{
    fd_set reads, temps;
    int result, str_len;
    char buf[BUF_SIZE];
    timeval timeout;
    FD_ZERO(&reads);
    FD_SET(0, &reads);

    /**
	timeout.tv_sec = 5;
    timeout.tv_usec = 5000;
	**/

    while (1) {
        temps = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        result = select(1, &temps, 0, 0, &timeout);
        if (result < 0) {
            puts("select error");
            break;
        } else if (result == 0) {
            puts("Time out");
			break;
        } else { 
			if (FD_ISSET(0, &temps)){
				str_len = read(0, buf, BUF_SIZE);
				buf[str_len] = 0;
				cout << "message from console : " << buf << endl;
				cout << "select fd number : " << result << endl;
			}
        }
    }
	return 0;
}
