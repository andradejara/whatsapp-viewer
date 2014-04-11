#pragma once

class WhatsappMessage;

class ChatControlMessage
{
private:
	WhatsappMessage &message;
	WCHAR *wcharDate;
	HGDIOBJ dateFont;

	bool fromMe();

	void renderBox(HDC deviceContext, int y, int left, int right, int color);
	virtual void renderInner(HDC deviceContext, int y, int left, int right) = 0;

protected:
	int getDateHeight(HDC deviceContext, int left, int right);

public:
	ChatControlMessage(WhatsappMessage &message, HGDIOBJ dateFont);
	virtual ~ChatControlMessage();

	virtual void calculateHeight(HWND window) = 0;
	virtual int getHeight() = 0;

	void render(HDC deviceContext, int y, int left, int right);

};
