#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int valid_ip(char* ip){
    int length = strlen(ip);
    int dots = 0;
    //the parts of the ip address
    int part1, part2, part3, part4;
    // an ip address is minmum 7 characters or maximum 15.
    if (length >= 7 && length <= 15){
        //for loop to get how many dots are in the ip 
        for (int i = 0; i <= length; i++){
            if (ip[i] == '.'){
                dots++;
            }
        }
        //if the dots are different than 3 we return 0
        if (dots != 3){
            return 0;
        }else{
            //we separate the ip address to 4 sections with sscanf (string scan)
            int res = sscanf(ip, "%d.%d.%d.%d", &part1, &part2, &part3, &part4);
            printf("%d.%d.%d.%d", part1, part2, part3, part4);
            if (part1 < 0 || part1 > 255)
                return 0;
            if (part1 < 0 || part2 > 255)
                return 0;
            if (part3 < 0 || part3 > 255)
                return 0;
            if (part4 < 0 || part4 > 255)
                return 0;
        return 1;        
            
        }
    }else{
        return 0;
    }
}

int main(){
    char ip[] = "255.255.255.255";
    char ip1[] = "128.0.0.1";
    char ip2[] = "300.192.1.2";
    char ip3[] = "-12.23.12.23";
    char ip4[] = "172.45.223..1";
    char ip5[] = "afs.213.sf.23ew";


    if (valid_ip(ip5) == 1){
        printf("valid\n");
    }else{
        printf(" Not Valid\n");
    }
    return 0;
}



