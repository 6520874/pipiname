#include "StdAfx.h"
#include "FileTransSocket.h"
#include <Winsock2.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")


CFileTransSocket::CFileTransSocket(void)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 1, 1 );

	err = WSAStartup( wVersionRequested, &wsaData);
	if (err)
	{
		return ;
	}

	if ( LOBYTE( wsaData.wVersion ) != 1 ||
		HIBYTE( wsaData.wVersion ) != 1 )
	{
		WSACleanup( );
		return ;
	}

}

CFileTransSocket::~CFileTransSocket(void)
{
	
}

BOOL  CFileTransSocket::Tran( CString cname )
{
	SOCKET socksrv=socket(AF_INET,SOCK_STREAM,0);

	sockaddr_in  addrsrv;
	addrsrv.sin_addr.S_un.S_addr = inet_addr("121.199.10.53");
	addrsrv.sin_family = AF_INET;
	addrsrv.sin_port = htons(8848);

	connect(socksrv,(SOCKADDR*)&addrsrv,sizeof(SOCKADDR));
	FILE * fp = fopen("c://wow.jpg","rb");

	if(fp == NULL)
	{
		TRACE("read error");
		return -1;
	}
	char strPictureData[1024];

	while(!feof(fp))
	{
		int n =  fread(strPictureData,1,1024,fp); 
           
		TRACE("send %d\n",n);
		//cout<<"send "<<n<<endl;
		send(socksrv,strPictureData,n,0);

	}

	closesocket(socksrv);
	WSACleanup();

	return  1;

}
