#include "Lexer.h"

ILexer::ILexer() :
	m_File(INVALID_HANDLE_VALUE),
	m_dwFileSize(0),
	m_NowProgress(0),
	m_Pointer(0),
	m_NowLoaded(0),
	m_dwBufferSize(0),
	m_pBuffer(NULL)
{
}

ILexer::~ILexer()
{
	Close();
}

char ILexer::GetNextChar()
{
	// ------------------------------------------------------------
	// CASE) Buffer�� ���� �پ����� �ٽ� File�� ���� Buffer��ŭ�� �о� ���δ�.
	// ------------------------------------------------------------
	if (m_Pointer == m_NowLoaded)
	{
		// Declare) 
		BOOL	result;

		// 1) Read�Ѵ�.
		result = ReadFile(m_File, m_pBuffer, m_dwBufferSize, &m_NowLoaded, NULL);

		// Check) 
		RETURN_IF(result == FALSE, 0);

		// Check) 
		RETURN_IF(m_NowLoaded == 0, 0);

		// 2) Reset�Ѵ�.
		m_Pointer = 0;
	}


	// ------------------------------------------------------------
	// Buffer�� ���� �ʾ��� ��� �׳� ���� ���ڸ� ����������.
	// ------------------------------------------------------------
	// ����...���...
	++m_NowProgress;


	// Return) ���� ���ڸ� �����ش�.
	return	m_pBuffer[m_Pointer++];
}

BOOL ILexer::Open(LPCSTR p_FileName, DWORD p_dwBufferSize)
{
	// ------------------------------------------------------------
	// Check) 
	// ------------------------------------------------------------
	// 1) FileName String�� NULL�̸� �׳� ����������.
	RETURN_IF(p_FileName == NULL, FALSE);

	// 2) Buffer�� Size�� 0�� ����������.
	RETURN_IF(p_dwBufferSize == 0, FALSE);


	// ------------------------------------------------------------
	// Declare) 
	// ------------------------------------------------------------
	// 1) Buffer
	HANDLE	hFile = INVALID_HANDLE_VALUE;
	void*	pBuffer = NULL;
	DWORD	dwFileSize;

	try
	{
		// ------------------------------------------------------------
		// 1. File Open�ϱ�.
		// ------------------------------------------------------------
		// 1) File�� Open�Ѵ�.
		hFile = CreateFile(p_FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		// Check) ������ ���� ���ߴ�.
		RETURN_IF(hFile == INVALID_HANDLE_VALUE, FALSE);

		// 2) �⺻���� �������� �����Ѵ�.
		dwFileSize = GetFileSize(m_File, NULL);


		// ------------------------------------------------------------
		// 2. �ʱ�ȭ �� �غ�
		// ------------------------------------------------------------
		// 1) Buffer Size ����.
		pBuffer = (char*)malloc(p_dwBufferSize);


		// ------------------------------------------------------------
		// 2. �ʱ�ȭ �� �غ�
		// ------------------------------------------------------------
		// 1) File ������  �����Ѵ�.
		m_File = hFile;
		m_dwFileSize = dwFileSize;

		// 2) Buffer������ �����Ѵ�.
		m_pBuffer = (char*)pBuffer;
		m_dwBufferSize = p_dwBufferSize;

		// 3) �ʱ�ȭ
		Reset();
	}

	// ------------------------------------------------------------
	// Exception)
	// ------------------------------------------------------------
	catch (...)
	{
		// 1) File�ݱ�.
		SAFE_CLOSEHANDLE(hFile);

		// 2) Buffer �����.
		SAFE_FREE(pBuffer);

		// Return) ����....
		return	FALSE;
	}


	// Return) ����!!!
	return	TRUE;
}

void ILexer::Close()
{
	// ------------------------------------------------------------
	// Check) 
	// ------------------------------------------------------------
	// 1) ������ ���� ���������� �˻��Ͽ� �������°� �ƴ϶�� �׳� ����������.
	RETURN_IF(m_File == INVALID_HANDLE_VALUE, );

	// ------------------------------------------------------------
	// 1. ��� �ݴ´�.
	// ------------------------------------------------------------
	// 1) Buffer�� ����������.
	SAFE_FREE(m_pBuffer);
	m_dwBufferSize = 0;

	// 2) File�� �ݴ´�.
	SAFE_CLOSEHANDLE(m_File);
}

BOOL ILexer::Reset()
{
	// ------------------------------------------------------------
	// Check) 
	// ------------------------------------------------------------
	// 1) ������ ���� ���������� �˻��Ѵ�.
	RETURN_IF(m_File == INVALID_HANDLE_VALUE, FALSE);


	// ------------------------------------------------------------
	// 1. ������ �ʱ���·� ������.
	// ------------------------------------------------------------
	// 1) �⺻ ������ Reset�Ѵ�.
	m_NowProgress = 0;
	m_Pointer = 0;
	m_NowLoaded = 0;


	// ------------------------------------------------------------
	// 2. ������ �ʱ���·� ������.
	// ------------------------------------------------------------
	// Declare) 
	DWORD	dwResult;

	// 1) File�� Pointer�� ���� ó������ �ǵ�����.
	dwResult = SetFilePointer(m_File, 0, 0, FILE_BEGIN);

	// Check) �б⿡ ���������� FALSE�� Return�Ѵ�.
	RETURN_IF(dwResult == INVALID_SET_FILE_POINTER, FALSE);


	// Return) ����!!
	return	TRUE;
}
