#include <iostream>
#include <WinSock2.h>
#include <thread>
#include <assert.h>

using namespace std;

void getData(SOCKET sConnect, string name)
{
    WSAData wsaData;
    WORD version = MAKEWORD(2, 2); // 版本
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData); // 成功回傳 0
    if (iResult != 0)
    {
        cout << "Socket open error!!!\n";// 初始化Winsock 失敗
    }

    int r=0;
    char message[200];

    while (1)
    {
        ZeroMemory(message, 200);
        if ((r=recv(sConnect, message, sizeof(message), 0))!=SOCKET_ERROR)
        {
            cout << name << "(receive): "<< message << endl;
            cout << "Please enter a string\n";
        }
        else
        {
            return;
        }
    }
}

void server_socket ()
{
    WSAData wsaData;
    WORD version = MAKEWORD(2, 2); // 版本
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData); // 成功回傳 0
    if (iResult != 0)
    {
        cout << "Socket open error!!!\n";// 初始化Winsock 失敗
    }

    SOCKET server_socket=INVALID_SOCKET;
    SOCKADDR_IN addr_in;
    memset (&addr_in, 0, sizeof (addr_in)) ;

    server_socket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    addr_in.sin_addr.s_addr=inet_addr("127.0.0.1");
    addr_in.sin_family=AF_INET;
    addr_in.sin_port=htons(5555);

    int x=bind(server_socket,(SOCKADDR *)&addr_in,sizeof(addr_in));
    if (x<0)
    {
        cout << "server bind error!!!\n";
    }

    listen(server_socket,SOMAXCONN);

    SOCKET sConnect=INVALID_SOCKET;
    SOCKADDR_IN clientAddr;
    int client_addrlen=sizeof(clientAddr);

    while (true)
    {
        int r=0;
        char message[200];
        cout << "Server waits\n";
        if (sConnect=accept(server_socket,(SOCKADDR*)&clientAddr,&client_addrlen))
        {
            thread (getData, sConnect, "Server").detach();
            cout << "Who is speaking?\n";
            //cout << "Server got connection from: " << inet_ntoa(clientAddr.sin_addr);

            while(1)
            {
                char buffer[200]="";
                char s='0';
                string str="";

                cin.sync();
                if(s=cin.get()=='s')
                {
                    cout << "Please enter a string: \n";
                    cin.getline(buffer,sizeof(buffer));
                    cout << "Server(send):" << buffer << endl;
                    int se=send(sConnect, buffer, sizeof(buffer), 0);
                }
                else
                {
                    cout << "not server\n";
                }
            }

            //getline(cin,str);
            //system("pause");
            //string buf="Need My zip password? Which method will you use to get it?";
            //int s=send(sConnect, buf.c_str(), buf.length(), 0);
            /*while (1){
                if(r = recv(sConnect, message, sizeof(message), 0)>=0){
                    break;
                }
            }
            buf="1. To BOA";
            s=send(sConnect, buf.c_str(), buf.length(), 0);
            while (1){
                if(r = recv(sConnect, message, sizeof(message), 0)>=0){
                    break;
                }
            }
            buf="2. Try to use format string in 'printf' ";
            s=send(sConnect, buf.c_str(), buf.length(), 0);
            while (1){
                if(r = recv(sConnect, message, sizeof(message), 0)>=0){
                    break;
                }
            }
            buf="3. To do some reserve engineering";
            s=send(sConnect, buf.c_str(), buf.length(), 0);
            while (1){
                if(r = recv(sConnect, message, sizeof(message), 0)>=0){
                    break;
                }
            }
            buf="4. I give up, just give me the password";
            s=send(sConnect, buf.c_str(), buf.length(), 0);
            while (1){
                if(r = recv(sConnect, message, sizeof(message), 0)>=0){
                    break;
                }
            }*/
        }
        else
        {
            cout << "Connection error !!!\n";
        }
    }
}

int main()
{
    string s="Need My zip password? Which method will you use to get it?";
    //cout << sizeof (s) << " " << s.length();
    char message[200];
    int r=0;
    int i=0;
    string buf="ack";

    WSAData wsaData;
    WORD version = MAKEWORD(2, 2); // 版本
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData); // 成功回傳 0
    if (iResult != 0)
    {
        cout << "Socket open error!!!\n";// 初始化Winsock 失敗
    }

    SOCKET sConnect=INVALID_SOCKET;
    SOCKADDR_IN clientAddr;
    memset (&clientAddr, 0, sizeof (clientAddr)) ;
    clientAddr.sin_port=htons(5555);
    clientAddr.sin_family=AF_INET;
    clientAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    sConnect=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //thread (server_socket).detach();
    //thread server(server_socket);

    cout << "Do you really want to connect ?\n";
    char conn[5];
    cin .getline(conn,sizeof(conn));

    if (conn[0]=='Y')
    {
        connect(sConnect,(SOCKADDR*)&clientAddr, sizeof(clientAddr));
        thread (getData, sConnect, "Client").detach();

        cout << "Client side\n";
        while (conn[0]=='Y')
        {
            while(1)
            {
                char buffer[200];
                char c='0';
                string str="";
                ZeroMemory(message, 200);
                cin.sync();
                cout << "Please enter a string: \n";
                cin.getline(buffer,sizeof(buffer));
                cout << "Client(send): "<< buffer << endl;
                int se=send(sConnect, buffer, sizeof(buffer), 0);
                /*if (c=cin.get()=='c')
                {
                    //str.assign(client_speak);
                    //cout<<"c: "<<c<<endl;
                    cout << "Please enter a string: \n";
                    cin.getline(buffer,sizeof(buffer));
                    cout << "Client(send): "<< buffer << endl;
                    int se=send(sConnect, buffer, sizeof(buffer), 0);
                }
                else
                {
                    cout << "not client\n";
                }*/
            }
            //cout << "ClientR: " << r;
        }



        system("pause");
        /*r = recv(sConnect, message, sizeof(message), 0);
        cout << "Client: " << message << endl;
        i=send(sConnect, buf.c_str(), buf.length(), 0);
        ZeroMemory(message, 200);
        system("pause");
        r = recv(sConnect, message, sizeof(message), 0);
        cout << "Client: " << message << endl;
        i=send(sConnect, buf.c_str(), buf.length(), 0);
        ZeroMemory(message, 200);
        system("pause");
        r = recv(sConnect, message, sizeof(message), 0);
        cout << "Client: " << message << endl;
        i=send(sConnect, buf.c_str(), buf.length(), 0);
        ZeroMemory(message, 200);
        system("pause");
        r = recv(sConnect, message, sizeof(message), 0);
        cout << "Client: " << message << endl;
        i=send(sConnect, buf.c_str(), buf.length(), 0);
        ZeroMemory(message, 200);
        system("pause");
        r = recv(sConnect, message, sizeof(message), 0);
        cout << "Client: " << message << endl;
        i=send(sConnect, buf.c_str(), buf.length(), 0);
        system("pause");*/

        closesocket(sConnect);
    }
    else
    {
        cout << "Cancel";
        exit(1);
    }

    return 0;
}
