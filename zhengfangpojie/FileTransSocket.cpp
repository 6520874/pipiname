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

BOOL  CFileTransSocket::TransFile(int iFileLen, CString cname )
{
	SOCKET socksrv=socket(AF_INET,SOCK_STREAM,0);

	sockaddr_in  addrsrv;
	addrsrv.sin_addr.S_un.S_addr = inet_addr("121.199.10.53");
	addrsrv.sin_family = AF_INET;
	addrsrv.sin_port = htons(8848);

	connect(socksrv,(SOCKADDR*)&addrsrv,sizeof(SOCKADDR));
	FILE * fp = fopen(cname,"rb");

	if(fp == NULL)
	{
		TRACE("read error");
		return -1;
	}
	char strPictureData[1024] ={0};
	char  strFileLen[10] = {0};
	itoa(iFileLen,strFileLen,10);

	//发送传送文件的长度
    send(socksrv,strFileLen,10,0);
	TRACE("send filelen %d",iFileLen);
	int i = 0;
	int iSendSize = 0;

	while(!feof(fp))
	{
		int n =  fread(strPictureData,1,1024,fp); 
        
		iSendSize += send(socksrv,strPictureData,1024,0);
		TRACE("send %d\n %d",n,i++);
	}

    recv(socksrv,strPictureData,10,0);
   TRACE("send ok %s",strPictureData);
	closesocket(socksrv);
	WSACleanup();
	return  1;

}
