#pragma once
#include<map>
#include<Windows.h>

// 1) Definitions
#define	MAX_SIZE_OF_BUFFER		65536	// �б�� Buffer�� ũ��(�Ѳ����� �о���̴� �ִ� ũ��.)

// 2) Common Tokens
#define	TOKEND_NUMBER			1001	// ���ڸ� �ǹ��Ѵ�.
#define	TOKEND_STRING			1002	// ���ڿ��� �ǹ��Ѵ�. (""�� �����ִ� ��)
#define	TOKEND_BLOCK_START		1003	// Block�� ���� �� '{'�� �ǹ��Ѵ�.
#define	TOKEND_BLOCK_END		1004	// Block�� �� �� '}'�� �ǹ��Ѵ�.

#define	TOKEND_END				65534	// File�� ���� �ǹ��Ѵ�.
#define	TOKEND_IDENTIFIER		65535	// ������ �ǹ��Ѵ�.(���⼭�� ������� �ʴ´�.)
#define	TOKEND_NOTDEFINED		65536	// ���ǵ��� ���� ���� �ǹ��Ѵ�. (���� ���� Error)


//-------------------------------------------
//Class Token
//-------------------------------------------
class CTokenDefine
{
public:
	virtual void Init() = 0;

	bool SearchData(LPSTR SearchStr, int &GetValue);

protected:
	void DefineToken(LPCSTR str, int en);

private:
	std::map<std::string, int> m_mapTokenDefine;
	std::map<std::string, int>::iterator m_iter;
};


//-------------------------------------------
//Scene Token
//-------------------------------------------
class CToken_Scene : public CTokenDefine
{
public:
	CToken_Scene();

private:
	virtual void Init();
};

//-------------------------------------------
//TileMap Token
//-------------------------------------------
class CToken_TileMap : public CTokenDefine
{
public:
	CToken_TileMap();

private:
	virtual void Init();
};

enum enToken_TileMap 
{
	tenTM_MapName,
	tenTM_Row,
	tenTM_Column,
	tenTM_CellWidth,
	tenTM_CellHeight,
	tenTM_TileData,
	tenTM_TilePos,
	tenTM_TileName,
};

//-------------------------------------------
//TileSheet Token
//-------------------------------------------
class CToken_TileSheet : public CTokenDefine
{
public:
	CToken_TileSheet();

private:
	virtual void Init();
};

enum enToken_TileSheet
{
	tenTS_Data,
	tenTS_Name,
	tenTS_PathGroup,
	tenTS_Path,
	tenTS_Size,
};


//-------------------------------------------
//Tile Token
//-------------------------------------------
class CToken_Tile : public CTokenDefine
{
public:
	CToken_Tile();

private:
	virtual void Init();
};

enum enToken_Tile
{
	tenT_TileData,
	tenT_TileName,
	tenT_REFSheet,
	tenT_REFPosition,
	tenT_TileType,
	tenT_TileObstacle,
};


