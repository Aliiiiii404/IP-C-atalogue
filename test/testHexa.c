#include <stdio.h>
#include <string.h>

char* toHexa(char* ip){
    //variables
    static char hexa[15] = "";
    int part1, part2, part3, part4;
    sscanf(ip, "%d.%d.%d.%d", &part1, &part2, &part3, &part4);
    char store[100];
    int parts[] = {part1, part2, part3, part4};
    int i = 0;
    //we convert the decimals to hexadecimales
    //we start from part4 all the way to part1 to avoid reversing the the output
    for (int j = 3; j >= 0; j--){
        int part = parts[j];
        if (part == 0){
           store[i] = '0';
           printf("%c\n HERE", store[i]);
           i++; 
        }
        while (part > 0){
            int remain = part % 16;
            if(remain < 10){
                store[i] = '0' + remain;
                printf("Here1 :%d\n", remain);
            }else{
                store[i] = 'A' + (remain - 10);
                printf("Here2  :%c\n", 'A' + (remain - 10));
            }
            part = part / 16;
            i++;
        }
        if (j!=0){
            store[i] = '.';
            i++;
        }
    }
    //we read the values we store from the top or the table to the index 0 and we put the values in new table hexa.
    while (i--){
        char stock_hexa[3];
        sprintf(stock_hexa, "%c", store[i]);
        strcat(hexa, stock_hexa);
    }
    return hexa;
}

//      while (part4 > 0){
//        int remain = part4 % 16;
//        if(remain < 10){
//            store[i] = '0' + remain;
//        }else{
//            store[i] = 'A' + (remain - 10);
//        }
//       part4 = part4 / 16;
//        i++;
//   }
//    store[i] = '.';
//    i++;
//    while (part3 > 0){
//       int remain = part3 % 16;
//        if(remain < 10){
//           store[i] = '0' + remain;
//        }else{
//            store[i] = 'A' + (remain - 10);
//        }
//        part3 = part3 / 16;
//        i++;
//    }
//    store[i] = '.';
//    i++;
//    while (part2 > 0){
//        int remain = part2 % 16;
//        if(remain < 10){
//           store[i] = '0' + remain;
//        }else{
//            store[i] = 'A' + (remain - 10);
//        }
//        part2 = part2 / 16;
//        i++;
//    }
//    store[i] = '.';
//    i++;
//    while (part1 > 0){
//        int remain = part1 % 16;
//        if(remain < 10){
//            store[i] = '0' + remain;
//        }else{
//            store[i] = 'A' + (remain - 10);
//        }
//        part1 = part1 / 16;
//        i++;
//    }


int main() {
    char ip[] = "192.168.1.1";
    char ip2[] = "10.20.30.40";
    char ip3[] = "172.16.254.30";
    char ip4[] = "127.0.0.1";
    char ip5[] = "255.255.255.255";
    char ip6[] = "127.0.0.1";
    char ip7[] = "1.1.1.0";
    char *hexa = toHexa(ip);
    printf("the binary of the ip is : %s\n", hexa);
    return 0;
}
