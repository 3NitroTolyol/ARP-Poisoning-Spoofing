#include<stdio.h>
#include <winsock2.h>
#include <pcap.h>
#include <stdint.h>

#pragma pack(push, 1)
int main(){


struct eth_header{
    uint8_t dst_mac[6];
    uint8_t src_mac[6];
    uint16_t ethertype;
};

struct arp_header{
    uint16_t hardware_type;    
    uint16_t protocol_type;    
    uint8_t  hardware_len;     
    uint8_t  protocol_len;     
    uint16_t opcode;           
    uint8_t  sender_mac[6];    
    uint8_t  sender_ip[4];     
    uint8_t  target_mac[6];    
    uint8_t  target_ip[4];
};

    printf("%zu\n", sizeof(struct eth_header));
    printf("%zu\n", sizeof(struct arp_header));

  

    const char *ip_str = "127.0.0.1";

    unsigned long ip_binary = inet_addr(ip_str);


    if(ip_binary == INADDR_NONE){
        printf("Error");
    }
    else{
        printf("IP in binary: %lu\n", ip_binary );
    }


#pragma pack(pop)


    return 0;
}


