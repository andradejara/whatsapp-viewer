#include <windows.h>

#include "ChatControlMessageWithPreview.h"
#include "../../../../WhatsApp/Message.h"
#include "../../ImageDecoder.h"

ChatControlMessageWithPreview::ChatControlMessageWithPreview(WhatsappMessage &message, int width, ImageDecoder &imageDecoder)
	: ChatControlMessage(message, width), bitmap(NULL), bitmapWidth(0), bitmapHeight(0)
{
	if (message.getRawData() != NULL && message.getRawDataSize() > 0)
	{
		bitmap = imageDecoder.loadImage(message.getRawData(), message.getRawDataSize());

		BITMAP bitmapObject;
		GetObject(bitmap, sizeof(BITMAP), &bitmapObject);
		bitmapWidth = bitmapObject.bmWidth;
		bitmapHeight = bitmapObject.bmHeight;
	}
}

ChatControlMessageWithPreview::~ChatControlMessageWithPreview()
{
	if (bitmap != NULL)
	{
		DeleteObject(bitmap);
	}
}

int ChatControlMessageWithPreview::getPreviewBitmapWidth()
{
	return bitmapWidth;
}

int ChatControlMessageWithPreview::getPreviewBitmapHeight()
{
	return bitmapHeight;
}

void ChatControlMessageWithPreview::renderPreviewBitmap(HDC deviceContext, int x, int y)
{
	if (bitmap != NULL)
	{
		HDC hdcMem = CreateCompatibleDC(deviceContext);
		HGDIOBJ oldBitmap = SelectObject(hdcMem, bitmap);

		BitBlt(deviceContext, x, y, bitmapWidth, bitmapHeight, hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
	}
}
