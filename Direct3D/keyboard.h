#pragma once

#include <Windows.h>
#include <unordered_map>
class alignas(16) SimpleKeyboardServer
{
	friend class SimpleKeyboard;
	std::unordered_map<UINT_PTR, bool> key_map;
public:
	SimpleKeyboardServer(){}
	
	void OnKeyPress(WPARAM& key)
	{
		key_map[key] = true;
	}
	void OnKeyRelease(WPARAM& key)
	{
		key_map[key] = false;
	}
	
};

class alignas(16) SimpleKeyboard
{
	SimpleKeyboardServer& server;
public:
	SimpleKeyboard(SimpleKeyboardServer& srv)
		:server(srv)
	{}
	bool KeyPressed(UINT_PTR key)
	{
		return server.key_map[key];
	}
};