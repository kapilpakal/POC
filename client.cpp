#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

void processor(int input);

using namespace std;

int client;
int portNum = 1500; // NOTE that the port number is same for both client and server
bool isExit = false;
const int bufsize = 1024;
char buffer[bufsize];
char* ip = "127.0.0.1";
int userinput;
bool fileselected = false;

int main(){  

    struct sockaddr_in server_addr;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0) 
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }

    cout << "\n=> Socket client has been created..." << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);

    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
        cout << "=> Connection to the server port number: " << portNum << endl;

    cout << "=> Awaiting confirmation from the server..." << endl; //line 40
    recv(client, buffer, bufsize, 0);
    cout << "=> Connection confirmed, you are good to go...";

    cout << " Welcome to file manager.\nPlease enter the numbers based on the menu: \n ";

    cout << " 1 - set target location \n 2 - list files in pwd \n 3 - select a file \n 4- copy file to target location \n 5 - delete file \n 0 - exit \n ";

    cout << "\n\n=> Enter 0 to end the connection\n" << endl;

    // write code here.
    do{
        cin >> buffer;
        send(client, buffer, bufsize, 0);
        int a = stoi(buffer);
        if(a == 0){
            isExit = true;
        }else{
            processor(a);
        }
        }while (!isExit);

    cout << "\n=> Connection terminated.\nGoodbye...\n";

    close(client);
    return 0;
}

void processor(int input){
    string b;
    switch(input){
        case 1 :
        recv(client, buffer, bufsize, 0);
        cout << buffer;
        cin >> buffer;
        send(client, buffer, bufsize, 0);
        recv(client, buffer, bufsize, 0);
        cout << buffer;
        break;

        case 2 :
        recv(client, buffer, bufsize, 0);
        cout << buffer;
        recv(client, buffer, bufsize, 0);
        cout << buffer;
        break;

        case 3 :
        recv(client, buffer, bufsize, 0);
        cout << buffer;
        cin >> buffer;
        send(client, buffer, bufsize, 0);
        recv(client, buffer, bufsize, 0);
        b = buffer;
        if(b == "1"){
            fileselected = true;
            std::cout << "File found and selected successfully!";
        }
        else{
            std::cout << "File not found please enter a valid filename including its extension.\n!";
        }
        break;

        case 4 :
        if(fileselected == true){
        recv(client, buffer, bufsize, 0);
        cout << buffer;
        cin >> buffer;
        send(client, buffer, bufsize, 0);

        recv(client, buffer, bufsize, 0);
        cout << buffer;

        }else{
        recv(client, buffer, bufsize, 0);
        cout << buffer;
        }
        break;

        case 5 :
        recv(client, buffer, bufsize, 0);
        cout << buffer;
        break;

        default :
        recv(client, buffer, bufsize, 0);
        cout << buffer;
        break;
    }
}