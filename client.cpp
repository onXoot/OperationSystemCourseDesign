#include <iostream>
#include <arpa/inet.h> // socket 相关 ...
#include <unistd.h>    // close()
#include <thread> 
#include <string>
#include <cstring>
using namespace std;
int sockfd;
struct sockaddr_in serv_addr;

void SendMsg(const string &msg) {
	if(-1 == send(sockfd, msg.c_str(), msg.size(), 0))
		cout<<"Failed to send"<<endl;
}

void recv_msg(){
	int len;
	char recv_buf[101];
	while (1) {
		memset(recv_buf, 0, sizeof(recv_buf));
        len = recv(sockfd, recv_buf, sizeof(recv_buf), 0);
		if (-1 == len) {
			cout<<"receive fail"<<endl;
		}
		if(0 == len){
            close(sockfd);
			cout<<"disconnected with server!"<<endl;
			close(sockfd);
			cout<<" close client!"<<endl;
			exit(0);
			break;
		}
		cout<<"result is: "<<recv_buf<<endl;
	}
}

int main()
{
	string ip = "127.0.0.1";
	int port;
	cout<<"please input server port:";
	cin>>port;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd) {
		cout<<"Failed to sockfd"<<endl;
		return -1;
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(ip.c_str());

	int stat = connect(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr));
	if (-1 == stat) {
		cout<<"Failed to connect"<<endl;
		return -1;
	}
    std::thread(recv_msg).detach();
    string send_msg;
		
	getline(cin,send_msg);
	while(1)
	{		
		getline(cin,send_msg);
		if (send_msg == "q")		
		{
			cout<<"client is close！"<<endl;
			break;
		}
		else{
			if(send_msg[send_msg.size()-1] != '=')
				send_msg.append("=");
			SendMsg(send_msg);
		}
	}
	close(sockfd);
	return 0;
}






