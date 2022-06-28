#include <iostream>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include "fileoperations.h"

int client, server;
int portNum = 1500;
bool isExit = false;
const int bufsize = 1024;
char buffer[bufsize];
int userinput;
bool fileselected = false;

static std::string targetlocation = "/home/kapil/foperation";

void processor(int input);

using namespace std;

int main()
{ 

    struct sockaddr_in server_addr;
    socklen_t size;

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/
    /* --------------- socket() function ------------------*/

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0) 
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }

    cout << "\n=> Socket server has been created..." << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    /* ---------- BINDING THE SOCKET ---------- */
    /* ---------------- bind() ---------------- */


    if ((bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0) 
    {
        cout << "=> Error binding connection, the socket has already been established..." << endl;
        return -1;
    }

    size = sizeof(server_addr);
    cout << "=> Looking for clients..." << endl;

    /* ------------- LISTENING CALL ------------- */
    /* ---------------- listen() ---------------- */

    listen(client, 1);

    /* ------------- ACCEPTING CLIENTS  ------------- */
    /* ----------------- listen() ------------------- */

    int clientCount = 1;
    server = accept(client,(struct sockaddr *)&server_addr,&size);

    // first check if it is valid or not
    if (server < 0) 
        cout << "=> Error on accepting..." << endl;

    while (server > 0) 
    {
        strcpy(buffer, "=> Server connected...\n");
        send(server, buffer, bufsize, 0);
        cout << "=> Connected with the client #" << clientCount << ", you are good to go..." << endl;
        cout << "\n=> Enter 0 to end the connection\n" << endl;
        do{
        recv(server, buffer, bufsize, 0);
        int a = stoi(buffer);
        if(a == 0){
            isExit = true;
        }else{
            processor(a);
        }
        }while (!isExit);

        /* ---------------- CLOSE CALL ------------- */
        /* ----------------- close() --------------- */

        // inet_ntoa converts packet data to IP, which was taken from client
        cout << "\n\n=> Connection terminated with IP " << inet_ntoa(server_addr.sin_addr);
        close(server);
        cout << "\nGoodbye..." << endl;
        isExit = false;
        exit(1);
    }

    close(client);
    return 0;
}

void processor(int input){
    std::string filename;    
        
        switch(input){
            case 1 :
            strcpy(buffer, "please enter a target location:\n");
            send(server, buffer, bufsize, 0);
            recv(server, buffer, bufsize, 0);
            targetlocation = buffer;
            strcpy(buffer, "Target location set successfully!\n");
            send(server, buffer, bufsize, 0);
            break;

            case 2 :
            strcpy(buffer, "Listing files in the target location :\n");
            send(server, buffer, bufsize, 0);
            strcpy(buffer, listfilesinpwd(targetlocation).c_str());
            send(server, buffer, bufsize, 0);
            break;

            case 3 :{
            std::string userinput;
            bool found;
            strcpy(buffer, "Please enter the filename you want to select: \n");
            send(server, buffer, bufsize, 0);
            recv(server, buffer, bufsize, 0);
            userinput = buffer;
            found = searchingfile(targetlocation, userinput);
            if(found == true){
                filename = userinput;
                fileselected = true;
                strcpy(buffer, "1");
                send(server, buffer, bufsize, 0);
            }else{
                strcpy(buffer, "2");
                send(server, buffer, bufsize, 0);
            }
            }
            break;

            case 4 :
            if(fileselected == true){
                std::string path;
                strcpy(buffer, "Please enter the path file has to be copied from including file in it :\n");
                send(server, buffer, bufsize, 0);
                recv(server, buffer, bufsize, 0);
                path = buffer;
                copytolocation(path , targetlocation);
                strcpy(buffer, "file copied to target location successfully! \n");
                send(server, buffer, bufsize, 0);
            }else{
                strcpy(buffer, "Please select a file first using command 3.\n");
                send(server, buffer, bufsize, 0);
            }
            break;

            case 5 :
            deletefile(targetlocation);
            strcpy(buffer, "Target location deleted!\n");
            send(server, buffer, bufsize, 0);
            break;

            default :
            strcpy(buffer, "Invalid input, Please enter a valid input given in menu.\n");
            send(server, buffer, bufsize, 0);
            break;
        
    }
}