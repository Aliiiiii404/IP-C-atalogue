#include <stdio.h>
#include <string.h>


char* numberToBinary(int value) {
    static char res[9];
    for (int i = 0; i < 8; i++) {
        //we do the 7 - 1 to fill the last index of the array cuz we start to get the values on the right first
        //we add the '0' to convert the 1s and 0s to their values in ASCII so we can store them in char res.
        res[7 - i] = (value % 2) + '0';
        printf("%c\n", res[7 - i]);
        value = value / 2;
    }
    return res;
}


char* toBinary(char* ip){
  //array to stock the binary values foreach part of the ip.
    static char binary[35] = "";
    int part1, part2, part3, part4;
    sscanf(ip, "%d.%d.%d.%d", &part1, &part2, &part3, &part4);
    int parts[] = {part1, part2, part3, part4};
    for (int i = 0; i < 4; i++){
      strcat(binary, numberToBinary(parts[i]));
      strcat(binary, ".");
    }
    return binary;
}

int main() {
    char ip[] = "192.168.0.0";
    char ip1[] = "127.0.0.1";
    char *binary = toBinary(ip1);

    printf("the binary of the ip is : %s\n", binary);
    return 0;
}





