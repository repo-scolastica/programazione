#include <stdio.h>
#include <windows.h>
#include <iphlpapi.h>

#define MAX 100
#define PATH "C:/Users/SostituireConIlProprioNomeUtente/Desktop/Indirizzi.txt"


int main()
{
    FILE *f = NULL; 
    if((f = fopen(PATH, "w"))) {
        IP_ADAPTER_INFO AdapterInfo[16];
        IP_ADAPTER_INFO *AdapterHandler;

        DWORD dwBufferSize;
        DWORD dwStatus;

        int i, j;

        dwBufferSize = sizeof(AdapterInfo);
        dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufferSize);

        if (dwStatus != NO_ERROR) { return 1; }
        j = 0;
        
        AdapterHandler = AdapterInfo;
        while (AdapterHandler) {
            ++j;
            // MAC
            fprintf(f, "NIC %d, Adress: ", j);
            for (i = 0; i < 6; ++i) { fprintf(f, "%02x:", AdapterHandler->Address[i]); }
            fprintf(f, "\n");
            
            // IP
            fprintf(f, "IP %d, Adress: ", j);
            fprintf(f, "%s:", AdapterHandler->IpAddressList.IpAddress.String);
            fprintf(f, "\n");

            // IP NETMASK
            fprintf(f, "IP NETMASK %d, Adress: ", j);
            fprintf(f, "%s:", AdapterHandler->IpAddressList.IpMask.String);
            fprintf(f, "\n");
            
            // GATEWAY
            fprintf(f, "IP GATEWAY %d, Adress: ", j);
            fprintf(f, "%s:", AdapterHandler->GatewayList.IpAddress.String);
            fprintf(f, "\n");
            
            // GATEWAY NETMASK
            fprintf(f, "GATEWAY NETMASK %d, Adress: ", j);
            fprintf(f, "%s:", AdapterHandler->GatewayList.IpMask.String);
            fprintf(f, "\n");
            
            // DHCP
            fprintf(f, "IP DHCP %d, Adress: ", j);
            fprintf(f, "%s:", AdapterHandler->DhcpServer.IpAddress.String);
            fprintf(f, "\n");
            
            // DHCP NETMASK
            fprintf(f, "DHCP NETMASK %d, Adress: ", j);
            fprintf(f, "%s:", AdapterHandler->DhcpServer.IpMask.String);
            fprintf(f, "\n");
            
            AdapterHandler = AdapterHandler->Next;
            fprintf(f, "\n");
        }
        
        fclose(f);
    }
    
    return 0;
}
