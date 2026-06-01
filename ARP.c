#include<stdio.h>
#include <winsock2.h>
#include <pcap.h>
#include <stdint.h>

#pragma pack(push, 1)

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
struct arp_packet{
        struct eth_header eth;
        struct arp_header arp;
    };

void mac_address(const char *str, uint8_t* mac_array){
    sscanf(str, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &mac_array[0], &mac_array[1],&mac_array[2],&mac_array[3],&mac_array[4],&mac_array[5]);
    for(int i = 0; i < 6; i++) {
    printf("%02x ", mac_array[i]);
    
}
printf("\n");
}

int main(){

    struct arp_packet packet_to_victim;

    packet_to_victim.eth.dst_mac;
    packet_to_victim.eth.src_mac;
    packet_to_victim.eth.ethertype = htons(0x0806);

    packet_to_victim.arp.hardware_len = 6;
    packet_to_victim.arp.hardware_type = htons(1);
    packet_to_victim.arp.opcode = htons(2);
    packet_to_victim.arp.protocol_len = 4;
    packet_to_victim.arp.protocol_type = htons(0x0800);
    packet_to_victim.arp.sender_ip;
    packet_to_victim.arp.sender_mac;
    packet_to_victim.arp.target_ip;
    packet_to_victim.arp.target_mac;


    struct arp_packet packet_to_router;

    packet_to_router.eth.dst_mac;
    packet_to_router.eth.src_mac;
    packet_to_router.eth.ethertype = htons(0x0806);

    packet_to_router.arp.hardware_len = 6;
    packet_to_router.arp.hardware_type = htons(1);
    packet_to_router.arp.opcode = htons(2);
    packet_to_router.arp.protocol_len = 4;
    packet_to_router.arp.protocol_type = htons(0x0800);
    packet_to_router.arp.sender_ip;
    packet_to_router.arp.sender_mac;
    packet_to_router.arp.target_ip;
    packet_to_router.arp.target_mac;

  
    char my_ip_str[16];
    char victim_ip_str[16];
    char router_ip_str[16];

    uint32_t my_ip;
    uint32_t victim_ip;
    uint32_t router_ip;


    char my_mac_str[18];
    char victim_mac_str[18];
    char router_mac_str[18];

    

    mac_address("00:0c:29:4f:bb:11", packet_to_victim.eth.dst_mac);

    printf("%x\n",packet_to_victim.eth.dst_mac);

//ip_buffer[strcspn(ip_buffer, "\n")] = 0;

//You
    printf("Your profile: \n");
    printf("Enter your IP address: ");
    fgets(my_ip_str, 15,stdin);
    my_ip_str[strcspn(my_ip_str, "\n")] = 0;
    my_ip = inet_addr(my_ip_str);
   


    printf("Enter your MAC address: ");
    fgets(my_mac_str, 17,stdin);
    my_mac_str[strcspn(my_mac_str, "\n")] = 0;

//Victim
    printf("Victim profile: \n");
    printf("Enter victim IP address: ");
    fgets(victim_ip_str, 15,stdin);
    victim_ip_str[strcspn(victim_ip_str, "\n")] = 0;
    victim_ip = inet_addr(victim_ip_str);

    printf("Enter victim MAC address: ");
    fgets(victim_mac_str, 17,stdin);
    victim_mac_str[strcspn(victim_mac_str, "\n")] = 0;

//Router
    printf("Router profile: \n");
    printf("Enter Router IP address: ");
    fgets(router_ip_str, 15,stdin);
    router_ip_str[strcspn(router_ip_str, "\n")] = 0;
    router_ip = inet_addr(router_ip_str);

    printf("Enter router MAC address: ");
    fgets(router_mac_str, 17,stdin);
    router_mac_str[strcspn(router_mac_str, "\n")] = 0;


//Configuration
    //You
    memcpy(packet_to_victim.arp.sender_ip, &router_ip, 4);
    //Victim
    
    //Router







    const char *ip_str = "127.0.0.1";

    uint32_t ip_binary = inet_addr(ip_str);


    if(ip_binary == INADDR_NONE){
        printf("Error");
    }
    else{
        printf("IP in binary: %lu\n", ip_binary );
    }



 //   printf("%zu\n", sizeof(struct eth_header));
 //   printf("%zu\n", sizeof(struct arp_header));

    return 0;
}

#pragma pack(pop)
