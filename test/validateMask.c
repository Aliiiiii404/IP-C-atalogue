#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int valid_subnet(char* subnet){
    int length = strlen(subnet);
    int dots = 0;
    //all the octets that can a subnet have for the secend and the third part and th last part
    int validateSecendThirdOctets[] = {0, 128, 192, 224, 240, 248, 252, 254, 255};
    int validateLastOctets[] = {0, 128, 192, 224, 240, 248, 252};
    //the parts of the subnet
    int part1, part2, part3, part4;
    //variable that gonna decide if we found the right octets in the tables abouve and its set to 0 or false by default (false)
    int found = 0;
    // a subnet is minmum 9 (255.0.0.0) characters or maximum 15 (255.255.255.255).
    if (length >= 9 && length <= 15){
        //for loop to get how many dots are in the subnet
        for (int i = 0; i <= length; i++){
            if (subnet[i] == '.'){
                dots++;
            }
        }
        //if the dots are different than 3 we return 0
        if (dots != 3){
            return 0;
        }else{
            //we scan the subnet and make it parts with string scan
            int res = sscanf(subnet, "%d.%d.%d.%d", &part1, &part2, &part3, &part4);
            //verify if the parts we scand are integers
            if(res != 4){
                return 0;
            }
            //verify if the first octet is 255
            if (part1 != 255){
                return 0;
            }
            //validate the secend octets
            for (int i = 0; i < 9; i++){
                //verify if the part is a digit and
                if (part2 == validateSecendThirdOctets[i]){
                    found = 1;
                    break;
                }
            }
            if (found == 0){
                return 0;
            }
            found = 0;
            //validate the third octets
            for (int i = 0; i < 9; i++){
                if (part3 == validateSecendThirdOctets[i]){
                    found = 1;
                    break;
                }
            }
            if (found == 0){
                return 0;
            }
            found = 0;
            //validate the third octets
            for (int i = 0; i < 7; i++){
                if (part4 == validateLastOctets[i]){
                    found = 1;
                    break;
                }
            }
            if (found == 0){
                return 0;
            }
            return 1;
        }
    }else{
        return 0;
    }
}

int main(){
    char subnet[] = "255.255.255.0";
    char subnet2[] = "255.0.0.0";
    char subnet3[] = "255.16.100.1";
    char subnet4[] = "125.512.100.1";
    char subnet5[] = "hfghgfhf3hfg.hfghgf";
    char subnet6[] = "afs.213.sf.23ew";
    char subnet7[] = "255.255.20.20";
    char subnet8[] = "255.255.y.1";



    if (valid_subnet(subnet8) == 1){
        printf("valid\n");
    }else{
        printf(" Not Valid\n");
    }
    return 0;
}