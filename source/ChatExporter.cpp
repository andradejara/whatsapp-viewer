#include <fstream>
#include <windows.h>

#include "ChatExporter.h"
#include "Exceptions/Exception.h"
#include "WhatsApp/Chat.h"
#include "WhatsApp/Message.h"
#include "Platforms/Win32/Timestamp.h"

ChatExporter::ChatExporter(WhatsappChat &chat)
	: chat(chat)
{
}

ChatExporter::~ChatExporter()
{
}

void ChatExporter::exportChat(const std::string &filename)
{
	std::ofstream file(filename.c_str());

	if (!file)
	{
		throw Exception("could not open chat export file");
	}

	file << chat.getKey();

	if (chat.getSubject().length() > 0)
	{
		file << "; " << chat.getSubject();
	}

	file << std::endl << std::endl;

	std::vector<WhatsappMessage *> &messages = chat.getMessages();
	for (std::vector<WhatsappMessage *>::iterator it = messages.begin(); it != messages.end(); ++it)
	{
		WhatsappMessage &message = **it;

		file << buildTimestampString(message.getTimestamp()) << "; ";

		if (message.isFromMe())
		{
			file << "ME: ";
		}
		else
		{
			file << "he: ";
		}

		switch (message.getMediaWhatsappType())
		{
			case MEDIA_WHATSAPP_TEXT:
			{
				file << message.getData();
			} break;
			case MEDIA_WHATSAPP_IMAGE:
			{
				file << "[ Image ]";
			} break;
			case MEDIA_WHATSAPP_AUDIO:
			{
				file << "[ Audio ]";
			} break;
		}

		file << std::endl;
	}
}
