
#include "DialogLexer.h"


DIALOG::CLexer::CLexer(LPCSTR p_FileName, DWORD p_SizeOfBuffer)
{
	// 1) Open�Ѵ�.
	if (p_FileName != NULL)
	{
		Open(p_FileName, p_SizeOfBuffer);
	}
}

DIALOG::CLexer::~CLexer()
{
}

//Lexical Analysis
int DIALOG::CLexer::GetToken(LPSTR p_TokenString)
{
	// ------------------------------------------------------------
	// 1. ���� �������� ����ã��
	// ------------------------------------------------------------
	// - ���ʿ� �����̳� Tab�̳� �����̳� ĳ�������� ���� ���ڿ��� ������ �����Ѵ�.
	CHAR	Char = GetNextChar();
	while (Char == ' ' || Char == '\t' || Char == '\r' || Char == '\n')
	{
		Char = GetNextChar();

		// Check) �������� Ȯ���Ѵ�.
		RETURN_IF(!Char, TOKEND_END);
	}


	// ------------------------------------------------------------
	// 2. BLOCK Ȯ��.
	// ------------------------------------------------------------
	// 1) '{'�ΰ��� Ȯ���Ѵ�.
	if (Char == '{')
	{
		p_TokenString[0] = '{';
		p_TokenString[1] = NULL;

		return	TOKEND_BLOCK_START;
	}

	// 2) '}'�ΰ��� Ȯ���Ѵ�.
	else if (Char == '}')
	{
		p_TokenString[0] = '}';
		p_TokenString[1] = NULL;

		return	TOKEND_BLOCK_END;
	}


	// ------------------------------------------------------------
	// 3. Reserved Word
	// ------------------------------------------------------------
	// - '*'�ΰ��� Ȯ���Ѵ�.
	//   ���� '*'�� �����ϴ� ���� Reserved word�̹Ƿ� �˻��Ѵ�!
	else if (Char == '*')
	{
		int		p_StringPoint = 0;
		while (Char != ' ' && Char != '\t' && Char != '\r' && Char != '\n' && Char != '"' && Char != '{' && Char != '}')
		{
			p_TokenString[p_StringPoint] = Char;

			Char = GetNextChar();

			// Check) �������� Ȯ���Ѵ�.
			RETURN_IF(!Char, TOKEND_END);

			++p_StringPoint;
		}
		p_TokenString[p_StringPoint] = NULL;

		for (int i = 0; i<eDigToken_MAX; ++i)
		{
			if (!strcmp(p_TokenString, DigToken[i]))
			{
				// �´� Token�� ã�Ҵ�! �� ��ȣ�� return�����ش�.
				return	i;
			}
		}

		// �´� ���� ���� ã�� ���ߴ�. ���ǵ��� ���� TOKEN�̶�� �����ش�.
		return	TOKEND_NOTDEFINED;
	}


	// ------------------------------------------------------------
	// 4. ���������� Ȯ���Ѵ�.
	// ------------------------------------------------------------
	// - ���࿡ '0'���� '9'�����̰ų� '-'���ϰ� �پ� ������ ���ڶ�� �Ǵ��� �Ѵ�.
	else if (Char >= '0' && Char <= '9' || Char == '-')
	{
		int		p_StringPoint = 0;
		while ((Char >= '0' && Char <= '9') || Char == '-' || Char == '.')
		{
			p_TokenString[p_StringPoint] = Char;

			Char = GetNextChar();

			// Check) �������� Ȯ���Ѵ�.
			RETURN_IF(!Char, TOKEND_END);

			++p_StringPoint;
		}
		p_TokenString[p_StringPoint] = NULL;


		return	TOKEND_NUMBER;
	}


	// ------------------------------------------------------------
	// 5. String������ �˻��Ѵ�.
	// ------------------------------------------------------------
	// - '"' ����ǥ�� �����ϸ� �̰��� String�δ�!
	else if (Char == '"')
	{
		Char = GetNextChar();

		// Check) �������� Ȯ���Ѵ�.
		RETURN_IF(!Char, TOKEND_END);

		int		p_StringPoint = 0;
		while (Char != '"')
		{
			p_TokenString[p_StringPoint] = Char;

			Char = GetNextChar();

			// Check) �������� Ȯ���Ѵ�.
			RETURN_IF(!Char, TOKEND_END);

			++p_StringPoint;
		}
		p_TokenString[p_StringPoint] = NULL;

		return	TOKEND_STRING;
	}


	// Error) 
	return	TOKEND_NOTDEFINED;
}
