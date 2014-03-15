#pragma once

class CFileTransSocket
{
public:
	CFileTransSocket(void);
	~CFileTransSocket(void);


	BOOL  TransFile(int iFileLen ,CString cname);
};
