#include<stdio.h>
#include <winsock2.h>
#include <pcap.h>


int main(){

    const char *ip_str = "127.0.0.1";

    unsigned long ip_binary = inet_addr(ip_str);


    if(ip_binary == INADDR_NONE){
        printf("Error");
    }
    else{
        printf("IP in binary: %lu\n", ip_binary );
    }


#pragma pack(push, 1)

#pragma pack(pop)

    return 0;
}


