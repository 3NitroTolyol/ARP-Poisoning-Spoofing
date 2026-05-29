#include<stdio.h>
#include<stdlib.h>
#include <winsock2.h>
#include <pcap.h>

int main(){

    int choice;
    pcap_if_t *alldevs;
    pcap_if_t *d;
    int i = 0;
    

    char errbuf[PCAP_ERRBUF_SIZE];

    if(pcap_findalldevs(&alldevs, errbuf) == -1){
        fprintf(stderr, "%s\n", errbuf);
        exit(1);
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
        return 0;
    }
//doing choice 
    
    printf("Enter number to choice adapter you need: ");
    scanf("%d", &choice);

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
        }
//open_live
    pcap_t *handle;
    
    handle = pcap_open_live(d->name, BUFSIZ, 1 , 1000, errbuf);
    if(handle == NULL){
        fprintf(stderr, "Couldn't open device %s: %s\n", d, errbuf);
        return(2);
    }
    
/*Если ваша программа не поддерживает заголовки
канального уровня предоставляемые устройством, 
то она должна будет прекратить работу, с помощью подобного кода*/

    if (pcap_datalink(handle) != DLT_EN10MB) 
    {
    fprintf(stderr, "Device %s doesn't provide Ethernet headers -not  supported\n", d);
    return(2);
    }





    pcap_freealldevs(alldevs);

    
    return 0;


}