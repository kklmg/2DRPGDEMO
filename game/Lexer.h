#pragma once
#include<Windows.h>
//-----------------------------------------------------------------------------
//  Common Lexer
//  
//  1) Common Lexer��...
//     - �⺻���� File�� Open/Clse/Reset��ɰ� ���� Characater�� ���� �� �ִ�
//       ��ɸ� �����ϴ� Class��.
//     - Buffering�� �����ϹǷ� �Ϲ� fgetc()�� ���� �ͺ��� ���� �ӵ��� ������.
//     - ������ p_TokenString���� �׿� �ش��ϴ� String�� �����ش�.
//
//  2) GetToken()�Լ�.
//     - ���� �ٽ��Լ��� �� Lexer�� ��ӹ޾� �ݵ�� ������ ���־���Ѵ�.
//     - Return value�� Token�� ������ �ش��ϴ� ���ڸ� �����ָ�..
//     - p_TokenString���� �ش� Token�� ���ڿ��� �����ؼ� �־��ִ� ����� �ϵ���
//       �����ؾ��Ѵ�.
//  
//-----------------------------------------------------------------------------
// Include) 
#include "CGDefinitions.h"
#include "TokenDefine.h"

class ILexer
{
	// ****************************************************************************
	// Constructor/Destructor)
	// ----------------------------------------------------------------------------
public:
	ILexer();
	virtual ~ILexer();


	// ****************************************************************************
	// Public)
	// ----------------------------------------------------------------------------
public:
	// 1) File Open/Close/Reset�Լ�.
	BOOL				Open(LPCSTR p_strFileName, DWORD p_dwBufferSize = MAX_SIZE_OF_BUFFER);	// ������ ����.
	void				Close();			// �ݾƹ�����.
	BOOL				Reset();			// ó������ �ٽ� �����Ѵ�.

											// 2) Token�� ��� �Լ�.(�ݵ�� ������ ����� �Ѵ�.)
	virtual	int					GetToken(LPSTR p_TokenString) = 0;


	// ****************************************************************************
	// Implementation)
	// ----------------------------------------------------------------------------
private:
	// 1) ������ �о �۾��ϱ� ���� ������
	HANDLE				m_File;				// ������ �ڵ�

											// 2) Buffer Infos~~
	DWORD				m_Pointer;			// ���� Buffer�� �а� �ִ� ���ڿ��� Pointer
	DWORD				m_NowLoaded;		// ���� �о� �鿩���� ũ��

	DWORD				m_dwBufferSize;		// Buffer�� ũ��
	char*				m_pBuffer;			// ������ ������ �о� ���� Buffer

	DWORD				m_dwFileSize;		// ������ ��ü ũ��
	DWORD				m_NowProgress;		// ���� ����.

protected:
	// 1) ���� Character�� ������ �Լ�.(Lexer ���������θ� ����.)
	char				GetNextChar();
};
