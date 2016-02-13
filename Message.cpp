/*
 * Message.cpp
 *
 *  Created on: Feb 10, 2016
 *      Author: Adam
 */
#include "Message.h"
#include <ArduinoJson.h>

// I believe this needs to be set to the number of objects in the MessageData struct.
// This does not correspond to the size of the struct itself.
#define MESSAGE_DATA_JSON_SIZE (JSON_OBJECT_SIZE(11))

Message::Message( char *jsonString )
{
	// Intialize a blank message so that if this class is written to JSON, it will be a full message
	InitializeBlankMessage();
	// If a JSON string was passed in, fill out the MessageData
	if( jsonString != 0 )
		Deserialize( _MessageData, jsonString );

	_JsonString = jsonString;
}

void
Message::InitializeBlankMessage( void )
{
	// I don't really know what the default values should be
	_MessageData._Type = TIME;
	_MessageData._Method = GET;
	_MessageData._Hour = 0;
	_MessageData._Minute = 0;
	_MessageData._Month = 0;
	_MessageData._Day = 0;
	_MessageData._Year = 0;
	_MessageData._Red = 0;
	_MessageData._Green = 0;
	_MessageData._Blue = 0;
	_MessageData._Temperature = 0;

}

bool
Message::ParseJson( char * jsonString )
{
	return Deserialize( _MessageData, jsonString );
}

char *
Message::ToJson( void )
{
	Serialize( _MessageData, _JsonString, MAX_BUFFER_SIZE );
	return _JsonString;
}

void
Message::Serialize( const MessageData &messageData, char *json, short maxSize )
{
	StaticJsonBuffer<MESSAGE_DATA_JSON_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();
	root["Type"] = messageData._Type;
	root["Method"] = messageData._Method;
	root["Hour"] = messageData._Hour;
	root["Minute"] = messageData._Minute;
	root["Month"] = messageData._Month;
	root["Day"] = messageData._Day;
	root["Year"] = messageData._Year;
	root["Red"] = messageData._Red;
	root["Green"] = messageData._Green;
	root["Blue"] = messageData._Blue;
	root["Temperature"] = messageData._Temperature;

	root.printTo( json, maxSize);
}

bool
Message::Deserialize( MessageData &messageData, char *json )
{
	StaticJsonBuffer<MESSAGE_DATA_JSON_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(json);
	// To be honest, these casts here could be bogus. It compiles but, idk if it works.
	// I may have to set a temp int variable for each, and cast the message data to the int.
	messageData._Type = (Type)(int)root["Type"];
	messageData._Method =  (Method)(int)root["Method"];
	messageData._Hour = root["Hour"];
	messageData._Minute = root["Minute"];
	messageData._Month = root["Month"];
	messageData._Day = root["Day"];
	messageData._Year = root["Year"];
	messageData._Red = root["Red"];
	messageData._Green = root["Green"];
	messageData._Blue = root["Blue"];
	messageData._Temperature = root["Temperature"];

	return root.success();
}



