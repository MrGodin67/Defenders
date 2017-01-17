#pragma once

#include "includes.h"
#include <fstream>
struct _LevelData
{
	int map_width = 0;
	int map_height = 0;
	int cell_width = 0;
	int cell_height = 0;
	int level_index = 0;
	char map_name[256] = { '\0' };
};

class FileHandler
{
private:
	FILE* mainFilePtr = nullptr;
	FILE* tempFilePtr = nullptr;
	std::string text;
	_LevelData data;
public:
	FileHandler() 
	{
		sprintf_s(data.map_name, "%s", "Hello");
	}
	void WriteFile()
	{
		
		FILE * pFile;
		
		 fopen_s(&pFile,"levelData.bin", "wb");
		fwrite(&data, sizeof(_LevelData), 1, pFile);
		fclose(pFile);
		
	}

	void ReadFile()
	{

		FILE * pFile;
		_LevelData _data;
		fopen_s(&pFile, "levelData.bin", "rb");
		fread(&_data, sizeof(_LevelData), 1, pFile);
		fclose(pFile);

	}
};