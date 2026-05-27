#include<stdio.h>
#include<stdlib.h>
#include <winsock2.h>
#include <pcap.h>

int main(){


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

    pcap_freealldevs(alldevs);
    return 0;


}