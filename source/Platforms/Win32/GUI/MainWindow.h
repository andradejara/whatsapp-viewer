#pragma once

#include <windows.h>
#include <vector>

#include "OpenDatabaseDialog.h"

class Exception;
class Settings;
class WhatsappChat;
class WhatsappMessage;
class WhatsappDatabase;

class MainWindow
{
private:
	HWND dialog;
	std::vector<WhatsappChat *> chats;
	WhatsappDatabase *database;
	std::string tempFilename;
	OpenDatabaseStruct lastDatabaseOpened;
	Settings &settings;

	void openDatabase();
	void closeDatabase();

	void decryptDatabase();
	void clearChats();

	void createChildWindows();
	void setIcon();
	void resizeChildWindows(int width, int height);
	void addChats();
	void addChat(WhatsappChat &chat);
	void selectChat(WhatsappChat *chat);

	void exportChat(WhatsappChat &chat);

	void getTempFilename();
	bool fileExists(const std::string &filename);

	void readSettings();

	static INT_PTR CALLBACK dialogCallback(HWND dialog, UINT message, WPARAM wParam, LPARAM lParam);
	INT_PTR handleMessage(HWND dialog, UINT message, WPARAM wParam, LPARAM lParam);

public:
	MainWindow(Settings &settings);
	~MainWindow();

	bool handleMessages();

	static void displayException(HWND mainWindow, Exception &exception);
};
