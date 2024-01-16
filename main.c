#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
// Before you start reading the code please keep in minde that EVERY return 0 is for an error and return 1 is for a Success, exept for the newIp and the main function.
// Function that gets the Hexadecimal representation of the ip address
char* toHexa(char ip[]){
    //create a static array so we can return it at the end of the function
    //the fucntion needs to be a pointer to be able to return the static array
    //static means that the variable can live during the entire programme and not be destroyed after the end of the function
    static char hexa[15] = "";
    int part1, part2, part3, part4;
    //we separate the ip address to 4 sections with sscanf (string scan)
    sscanf(ip, "%d.%d.%d.%d", &part1, &part2, &part3, &part4);
    char store[100] = "";
    int parts[] = {part1, part2, part3, part4};
    int i = 0;
    //we convert the decimals to hexadecimales
    //we start from part4 all the way to part1 to avoid reversing the the output
    for (int j = 3; j >= 0; j--){
        int part = parts[j];
        //if the part is a 0 then we just add a 0 to the store table
        if (part == 0){
           store[i] = '0';
           i++; 
        }
        while (part > 0){
            int reste = part % 16;
            //if the rest is less than 10 that means its a number between '0' and '9' 
            if(reste < 10){
                store[i] = '0' + reste;
            }else{
                //if the reset is greater or equal to 10 that means its a char between 'A' and 'F'
                //and with the -10 we get a value from 0 to 5 and when we add the 'A' we get the character between 'A' and 'F'
                //we add the 'A' to get the character
                store[i] = 'A' + (reste - 10);
            }
            part = part / 16;
            i++;
        }
        //add a '.' to separate every two values
        if (j!=0){
            store[i] = '.';
            i++;
        }
    }
    //we read the values we store from the top of the table to the index 0 and we put the values in new table hexa.
    while (i--){
        char stock_hexa[3];
        sprintf(stock_hexa, "%c", store[i]);
        strcat(hexa, stock_hexa);
    }
    return hexa;
}
// Function that gets the binary value of each part of the ip address
//we do the 7 - 1 to fill the last index of the array cuz we start to get the values on the right first
//we add the '0' to convert the 1s and 0s to their values in ASCII so we can store them in char res.
char* numberToBinary(int value){
    static char res[9];
    for (int i = 0; i < 8; i++){
        res[7 - i] = (value % 2) + '0';
        value = value / 2;
    }
    return res;
}
//Function that points to the recurse_bine function
char* toBinary(char ip[]){
    //array to stock the binary values foreach part of the ip
    static char binary[35] = "";
    int part1, part2, part3, part4;
    //we separate the ip address to 4 sections with sscanf (string scan)
    sscanf(ip, "%d.%d.%d.%d", &part1, &part2, &part3, &part4);
    int parts[] = {part1, part2, part3, part4};
    for (int i = 0; i < 4; i++) {
        strcat(binary, numberToBinary(parts[i]));
        //we add a dot only for he first 3 octets so dont have a dot at the end
        if (i != 3)
            strcat(binary, ".");
    }
    return binary;
}
// Function that checks if the ip is valid
int valid_ip(char ip[16]){
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
            if (part1 < 0 || part1 > 255)
                return 0;
            if (part2 < 0 || part2 > 255)
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
// Function that checks if the subnte mask is valid
int valid_subnet(char subnet[16]){
    int length = strlen(subnet);
    int dots = 0;
    //all the octets that can a subnet have for the secend, the third and the last part
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
//function that return 1 if the all the characters are digits and 0 if not
int isNumber(char num[]) {
    for (int i = 0; i < strlen(num); i++) {
        if (num[i] < '0' || num[i] > '9') {
            return 0;
        }
    }
    return 1;
}
//Function that opens the database sqlite so we can do the adds and the upgrades
int databaseOpen(){
    //If the database exist we open it, else we create a new one with the same name.
    //create variables for the databse and fro the statements.
    sqlite3 *db;
    sqlite3_stmt *statement;
    int sqlite_open = sqlite3_open("ip_catalogue.db", &db);
    if (sqlite_open){
        sqlite3_close(db);
        return 0;
    }else{
        //verify if the table ip_addresses exist
        const char table_name[] = "ip_addresses";
        char req[] = "SELECT name FROM sqlite_master WHERE type='table' AND name=?";
        //Prepare the sql statment for execution
        sqlite_open = sqlite3_prepare_v2(db, req, -1, &statement, NULL);
        if(sqlite_open != SQLITE_OK){
            sqlite3_finalize(statement);
            sqlite3_close(db);
            return 0;
        }
        //replace the "?" in the sql query to the actual name 
        sqlite3_bind_text(statement, 1, table_name, -1, SQLITE_STATIC);
        sqlite_open = sqlite3_step(statement);
        if (sqlite_open == SQLITE_ROW){
            sqlite3_finalize(statement);
            sqlite3_close(db);
            return 1;
        }else{
            //when the table ip_addresses does not exist we create a new one
            const char req[] = "CREATE TABLE ip_addresses ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "ip TEXT(15),"
                                "subnet TEXT(15),"
                                "binary TEXT(35),"
                                "hexadecimal TEXT(12)"
                                ");";
            //execute the query above and create a new table
            sqlite_open = sqlite3_exec(db, req, 0, 0, NULL);
            if (sqlite_open != SQLITE_OK) {
                sqlite3_finalize(statement);
                sqlite3_close(db);
                return 0;
            } else {
                sqlite3_finalize(statement);
                sqlite3_close(db);
                return 1;
            }
            
        }        
    }
}
//Function that adds the ip, the subnet , the binary and the hexa values of the ip to the database (sqlite3).
int addToDatabase(char ip_address[16], char subnet[16], char* binary, char* hexa){
    //we call the databaseOpen function to make sure that the database and the table "ip_addresses" exist
    if(databaseOpen() == 0){
        printf("Failed to Open the database.");
        return 0;
    }else{
        sqlite3 *db;
        sqlite3_stmt *statement;
        int sqlite_open = sqlite3_open("ip_catalogue.db", &db);
        char req[] = "INSERT INTO ip_addresses (ip, subnet, binary, hexadecimal) VALUES (?, ?, ?, ?);";
        sqlite_open = sqlite3_prepare_v2(db, req, -1, &statement, 0);
        if(sqlite_open != SQLITE_OK){
            sqlite3_finalize(statement);
            sqlite3_close(db);
            return 0;
        }
        //replace the parameter "?" in the sql query with the actual values
        sqlite3_bind_text(statement, 1, ip_address, -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, subnet, -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 3, binary, -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 4, hexa, -1, SQLITE_STATIC);
        //execute the statement 
        sqlite_open = sqlite3_step(statement);
        if (sqlite_open != SQLITE_DONE){
            sqlite3_finalize(statement);
            sqlite3_close(db);
            return 0;
        }else{
            sqlite3_finalize(statement);
            sqlite3_close(db);
            return 1;
        }
    }
}
//Function that lists all the ip addresses
void ListIps(){
    //we call the databaseOpen function to make sure that the database and the table "ip_addresses" exist
    if(databaseOpen() == 0){
        printf("Failed to Open the database.");
    }else{
        //varaibles for the database
        sqlite3 *db;
        sqlite3_stmt *statement;
        int sqlite_open = sqlite3_open("ip_catalogue.db", &db);
        //the query to select all the ipes form the table
        const char req[] = "SELECT * FROM ip_addresses;";
        sqlite_open = sqlite3_prepare_v2(db, req, -1, &statement, NULL);
        if(sqlite_open != SQLITE_OK){
            printf("Error !!!!\n");
            sqlite3_finalize(statement);
            sqlite3_close(db);
            return;
        }else{
            int empty = 0; 
            while (sqlite3_step(statement) == SQLITE_ROW){
                int count = sqlite3_column_count(statement);
                //For loop to print all the resault for the query
                for (int i = 0; i < count; i++){
                    printf("%s : %s", sqlite3_column_name(statement, i), sqlite3_column_text(statement, i));
                    printf(" | "); 
                }
                empty++;
                printf("\n\n");
            }
            //If the database is empty we print this
            if (empty == 0){
                printf("There is no IP addresses in the database, feel free to add some!!\n\n");
                return;
            }
        }
        sqlite3_finalize(statement);
        sqlite3_close(db);
    }
}
//Search similar ips in the database using the subnet mask
void searchIp(){
    //we call the databaseOpen function to make sure that the database and the table "ip_addresses" exist
    if(databaseOpen() == 0){
        printf("Failed to Open the database.");
    }else{
        char subnet[16];
        while (valid_subnet(subnet) == 0){
            printf("Enter the subnet that you want to filter with(EX : 255.255.255.0) : ");
            scanf("%s", subnet);
        }
        printf("\n");
        //varaibles for the database using sqlite
        sqlite3 *db;
        sqlite3_stmt *statement;
        int sqlite_open = sqlite3_open("ip_catalogue.db", &db);
        //the query to select all the ips where the subnet = the subnet entered by the user
        char req[] = "SELECT * FROM ip_addresses WHERE subnet = ?;";
        sqlite_open = sqlite3_prepare_v2(db, req, -1, &statement, NULL);
        if(sqlite_open != SQLITE_OK){
            printf("Error !!!!\n");
            sqlite3_finalize(statement);
            sqlite3_close(db);
            return;
        }
        //replace the ? with the subnet value
        sqlite3_bind_text(statement, 1, subnet, -1, SQLITE_STATIC);
        //get how many ips with the same subnet exist
        if((sqlite_open = sqlite3_step(statement)) == SQLITE_ROW){
            //this count is set to one cuz we already verified abouve in the if for one time
            int row_count = 1;
            while (sqlite3_step(statement) == SQLITE_ROW){
                row_count++;
            }
            printf("There is %d IP addresses with the subnet %s.\n\n", row_count, subnet);
            //Loop to print all the resault for the query
            while ((sqlite_open = sqlite3_step(statement)) == SQLITE_ROW) {
                int count = sqlite3_column_count(statement);
                for (int i = 0; i < count; i++){
                    printf("%s : %s", sqlite3_column_name(statement, i), sqlite3_column_text(statement, i));
                    printf(" | "); 
                }
                printf("\n\n");
            }
        }else if((sqlite_open = sqlite3_step(statement)) == SQLITE_DONE){
            printf("There is no IPs with this Subnet Mask.\n\n");
        }
        //resete the variable and close the database.
        memset(subnet, 0, 16);
        sqlite3_finalize(statement);
        sqlite3_close(db);
    }
}
//Function thats gonna delete ip from the database by passing the id of the row as a parameter
void deleteIp(){
    //we call the databaseOpen function to make sure that the database and the table "ip_addresses" exist
    if(databaseOpen() == 0){
        printf("Failed to Open the database.");
    }else{
        sqlite3 *db;
        sqlite3_stmt *statement;
        int sqlite_open = sqlite3_open("ip_catalogue.db", &db);
        char req[] = "DELETE FROM ip_addresses WHERE id=?;";
        char id_input[10];
        ListIps();
        //if the user enters anything else but a number we keep asking for a valid integer
        while (1){
            printf("Please enter the ID of the ip you want to delete : ");
            scanf("%s", id_input);
            if (isNumber(id_input) == 1){
               break;
            }
        }
        //whene we get a valide integer we prepare the sql statment for execution
        sqlite_open = sqlite3_prepare_v2(db, req, -1, &statement, NULL);
        if(sqlite_open != SQLITE_OK){
            printf("Failed to Open the database.");
            sqlite3_finalize(statement);
            sqlite3_close(db);
        }else{
            //replace the "?" with the ID
            sqlite3_bind_text(statement, 1, id_input, -1, SQLITE_STATIC);
            sqlite_open = sqlite3_step(statement);
            //if the sqlite_change returns a number greater than 0 that means that the delete has been done, else the delete did not effect any row
            if (sqlite3_changes(db) > 0){
                printf("The ip with the ID %s has been deleted from the database.\n\n", id_input);
                ListIps();
            }else{
                printf("There is no IP addresse with the ID %s .\n\n", id_input);
            }
        }
        sqlite3_finalize(statement);
        sqlite3_close(db);
    }
}
//update an exesting ip address using the id, we use the same thing we used in deleteIp()
void updateIp(){
    //we call the databaseOpen function to make sure that the database and the table "ip_addresses" exist
    if(databaseOpen() == 0){
        printf("Failed to Open the database.");
    }else{
        sqlite3 *db;
        sqlite3_stmt *statement;
        int sqlite_open = sqlite3_open("ip_catalogue.db", &db);
        char req_select[] = "SELECT * FROM ip_addresses WHERE id=?;";
        char id_input[10];
        ListIps();
        //if the user enters anything else but a number we keep asking for a valid integer
        while (1){
            printf("Please enter the ID of the ip you want to Update : ");
            scanf("%s", id_input);
            if (isNumber(id_input) == 1){
               break;
            }
        }
        printf("\n");
        //whene we get a valide integer we prepare the select sql statment
        sqlite_open = sqlite3_prepare_v2(db, req_select, -1, &statement, NULL);
        if(sqlite_open != SQLITE_OK){
            printf("Error !!!!\n");
            sqlite3_finalize(statement);
            sqlite3_close(db);
            return;
        }else{
            int empty = 0;
            sqlite3_bind_text(statement, 1, id_input, -1, SQLITE_STATIC);
            while (sqlite3_step(statement) == SQLITE_ROW){
                int count = sqlite3_column_count(statement);
                //We print the resault for the SELECT with the id
                for (int i = 0; i < count; i++){
                    printf("%s : %s", sqlite3_column_name(statement, i), sqlite3_column_text(statement, i));
                    printf(" | "); 
                }
                empty++;
                printf("\n\n");
            }
            sqlite3_finalize(statement);
            //If the database does not contain a row with the id we print this
            if (empty == 0){
                printf("There is no IP addresse with the ID %s .\n\n", id_input);
            }else{
                //else we ask the user what he want to update
                //if he chose the ip we should update the binary and the hexadecimal parts too
                //if he chose the subnet we update only the subnet part.
                int choice = 0;
                char new_ip_address[16];
                char new_subnet[16];
                char* new_binary;
                char* new_hexa;
                //sql update query for the the ip and the subnet
                char req_update_ip[] = "UPDATE ip_addresses SET ip=?, binary=?, hexadecimal=? WHERE id=?;";
                char req_update_subnet[] = "UPDATE ip_addresses SET subnet=? WHERE id=?;";
                while (1){
                    printf("What do you want to update ? \n");
                    printf("[1] -> Update the IP Address.\n");
                    printf("[2] -> Update the subnet mask .\n");
                    printf("[3] -> Cancel\n");
                    printf("Choose an option : ");
                    scanf("%d", &choice);
                    printf("\n");   
                    // the users choices
                    switch (choice){
                        //if the user chose to update the ip
                        case 1:
                            //if the ip address is not valid we keep asking for a valid one
                            while (valid_ip(new_ip_address) == 0){
                                printf("Enter the new IP Address for Update : ");
                                scanf("%s", new_ip_address);
                            }
                            //convert new ip to binary and hexa using the functions we create.
                            new_binary = toBinary(new_ip_address);
                            new_hexa = toHexa(new_ip_address);
                            sqlite_open = sqlite3_prepare_v2(db, req_update_ip, -1, &statement, NULL);
                            if (sqlite_open != SQLITE_OK) {
                                printf("Error !!!!\n");
                                sqlite3_close(db);
                                return;
                            }
                            //replace the "?" with the id, ip, hexa and the binary
                            sqlite3_bind_text(statement, 1, new_ip_address, -1, SQLITE_STATIC);
                            sqlite3_bind_text(statement, 2, new_binary, -1, SQLITE_STATIC);
                            sqlite3_bind_text(statement, 3, new_hexa, -1, SQLITE_STATIC);
                            sqlite3_bind_text(statement, 4, id_input, -1, SQLITE_STATIC);
                            sqlite_open = sqlite3_step(statement);
                            sqlite3_finalize(statement);
                            if (sqlite3_changes(db) > 0){
                                printf("The row with the ID %s has been updated successfully!\n\n", id_input);
                                ListIps();
                            }else{
                                printf("Error !!!!\n");
                                return;
                            }
                            //reset variables and close database.
                            memset(new_ip_address, 0, 16);
                            memset(new_binary, 0, 35);
                            memset(new_hexa, 0, 12);
                            //close databse
                            sqlite3_close(db);
                            return;
                        case 2:
                            //if the subnet is not valid we keep asking for a valid one
                            while (valid_subnet(new_subnet) == 0){
                                printf("Enter the new subnet for Update : ");
                                scanf("%s", new_subnet);
                            }
                            //prepare the statment
                            sqlite_open = sqlite3_prepare_v2(db, req_update_subnet, -1, &statement, NULL);
                            //replace the "?" with the id, ip, hexa and the binary
                            sqlite3_bind_text(statement, 1, new_subnet, -1, SQLITE_STATIC);
                            sqlite3_bind_text(statement, 2, id_input, -1, SQLITE_STATIC);
                            sqlite_open = sqlite3_step(statement);
                            sqlite3_finalize(statement);
                            if (sqlite3_changes(db) > 0){
                                printf("The row with the ID %s has been updated successfully!\n\n", id_input);
                                ListIps();
                            }else{
                                printf("Error !!!!\n");
                                return;
                            }
                            //reset the subnet variable
                            memset(new_subnet, 0, 16);
                            //close databse
                            sqlite3_close(db);
                            return;
                        case 3:
                            sqlite3_close(db);
                            printf("Canceled !!!!\n\n");
                            return;
                        default:
                            break;
                    }
                }
            }
        }
    }
}
//Function that adds the new ip and its value in binary and hexadecimal to the database
int newIp(){
    char ip_address[16];
    char subnet[16];
    char* binary;
    char* hexa;
    //if the ip address is not valid we keep asking for a valid one
    while (valid_ip(ip_address) == 0){
        printf("Enter the IP Address (EX : 192.168.1.1) : ");
        scanf("%s", ip_address);
    }
    //if the subnet is not valid we keep asking for a valid one
    while (valid_subnet(subnet) == 0){
        printf("Enter the subnet for the IP Address (EX : 255.255.255.0) : ");
        scanf("%s", subnet);
    }
    //after the valadations we convert the ip address into a binray and into a hexadecimal
    binary = toBinary(ip_address);
    hexa = toHexa(ip_address);
    //we add all the values to the database
    if (addToDatabase(ip_address, subnet, binary, hexa) == 1){
        printf("The new IP : %s  has been added.\n", ip_address);
    }else{
        printf("Failed to add the new IP, please try again\n");
    }
    //reset all the varaibles abouve so it does not store the old values
    memset(ip_address, 0, 16);
    memset(subnet, 0, 16);
    memset(binary, 0, 35);
    memset(hexa, 0, 12);
    printf("\n");
    return 0;
}
//The main function
int main(){
    printf("\n");
    printf("\n");
    printf("  #####  #####      #####    ###   ######   ###    #      ######   #####   #    #   #####       \n");
    printf("    #    #   #      #       #   #    ##    #   #   #      #    #  #        #    #   #           \n");
    printf("    #    #####      #       #####    ##    #####   #      #    #  #  ###   #    #   #####       \n");
    printf("    #    #          #       #   #    ##    #   #   #      #    #  #    #   #    #   #           \n");
    printf("  #####  #          #####   #   #    ##    #   #   #####  ######   #####   ######   #####       \n\n");
    printf("           [+]                   Created by : Aliiiiii404                  [+]                  \n");
    printf("           [+]              Select a number in the list below              [+]                  \n\n\n");

    int quit = 0;
    int user_choice = 0;
    while (!quit){
        printf("[1] --> Add a new IP Address.\n");
        printf("[2] --> List IP Addresses.\n");
        printf("[3] --> Search similar by Subnet mask.\n");
        printf("[4] --> Update an existing IP by ID.\n");
        printf("[5] --> Delete an IP Address by ID.\n");
        printf("[6] --> Quit\n\n");
        printf("Choose an option : ");
        scanf("%d", &user_choice);
        printf("\n");   
        // the users choices
        switch (user_choice){
            case 1:
                newIp();
                break;
            case 2:
                ListIps();
                break;
            case 3:
                searchIp();
                break;
            case 4:
                updateIp();
                break;    
            case 5:
                deleteIp();
                break;
            case 6:
                quit = 1;
                printf("Bye Bye !!!!\n");
                break;
            default:
                break;
        }
    }
    return 0;
}
