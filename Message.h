/*
 * Message.h
 *
 *  Created on: Feb 10, 2016
 *      Author: Adam
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

// Max buffer size that is used by the ArduinoJson libraries. I went ahead and just made a static size so that
// the user of this message library doesn't have to worry about setting one.
static const short MAX_BUFFER_SIZE = 20;

/**
 * I don't really know why you want this Kevin. Write your own dang explanation.
 */
enum Type
{
	TIME,
	ALARM1,
	ALARM2,
	LIGHT,
	STATE
};

/**
 * I don't really know why you want this Kevin. Write your own dang explanation.
 */
enum Method
{
	GET,
	SET
};

/**
 * This structure is used to conviently store all the data this particular message class wants to parse
 * from a JSON string.
 */
struct MessageData{
	Type _Type;
	Method _Method;
	unsigned char _Hour;
	unsigned char _Minute;
	unsigned char _Month;
	unsigned char _Day;
	unsigned char _Year;
	unsigned char _Red;
	unsigned char _Green;
	unsigned char _Blue;
	unsigned char _Temperature;
};

/**
 * Simple message object that encapsulates the used of the ArduinoJSON library.
 */
class Message
{
public:
	/**
	 * Overridden constructor. I made the json string default to 0 so that users of the Message class can instantiate
	 * the message class before they actually have a json stream to initialize it with.
	 *
	 * @param json A properly formatted JSON string.
	 */
	Message( char * json = 0 );

	~Message(){};
	/**
	 * This is called when the message class is initialized without a JSON string. I'm not really sure
	 * if it is needed, but I don't like playing with uninitialized member data.
	 */
	void
	InitializeBlankMessage( void );

	/**
	 * Method to initialize all the MessageData from a given JSON string
	 *
	 * @param char * A properly formatted JSON string
	 *
	 * @return return true if JSON string was successfully parsed
	 */
	bool
	ParseJson( char * );

	/**
	 * Method to turn all the MessageData in this class to a properly formatted JSON string
	 *
	 * @return A properly formatted JSON string
	 */
	char *
	ToJson( void );

	/**
	 * Internal method to the Message class that encapsulates the use of the ArduinoJSON library's ability
	 * to turn a set of data into a properly formatted JSON string
	 *
	 * @param const MessageData & A set of data to be turned into a properly formatted JSON string
	 * @param char * Pointer to the JSON string created by the JSON library
	 * @param short The max buffer size for the JSON library
	 */
	void
	Serialize( const MessageData &, char *, short );

	/**
	 * Internal method to the Message class that encapsulates the use of the ArduinoJSON library's ability to
	 * initialize the MessageData struct from a properly formatted JSON string
	 *
	 * @param MessageData set of data to be initialized from the given JSON string
	 * @param char * A properly formatted JSON string
	 *
	 * @return returns true if the ArduinoJSON library successfully created a JSON string
	 */
	bool
	Deserialize( MessageData &, char * );

private:
	MessageData _MessageData; /// Member data used to store the contents of a JSON string
	char * _JsonString; /// Member data used to store a properly formatted JSON string

};


#endif /* MESSAGE_H_ */
