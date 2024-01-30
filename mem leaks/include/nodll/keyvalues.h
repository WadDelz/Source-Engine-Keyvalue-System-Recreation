
#ifndef _KEYVALUES_H
#define _KEYVALUES_H

#include <string>
#include <vector>
#include "tokens.h"

#pragma once

//------------------------------------------------------------
//------------------------------------------------------------
//	Copyright/created/owned by @valve software
//
//	Disclaimer this keyvalue system is not mine i just recreated it from
//	scratch with std::string, std::ifstream, std::stringstream and std::vector
//
//	The keyvalue system is a file/or buffer reader for cpp. it reads
//	subkeys and keys and values in the file/or buffer (keys and value are also
//	called keyvalue pairs). subkeys are like sections thet can contain keyvalue pairs
//	and/or other subkeys. the subkey starts of with the name declartion then a '{'.
//	if the name declartion has a space in it, it will have to be declared surrounded by 
//	quotes (or " to be precise). NOTE you can still make there be no spaces in the name 
//	and make it be surrounded by a pair of quotes
//	the subkey is then ended with a '}'. remember you can have
//	subkeys in subkeys so as long as you have a '{' and '}' for every subkey 
//
//	keyvalue pairs can be anywhere in the file/or buffer. it can be in subkeys and/or out 
//	of subkeys. keys and values have the same logic as the subkey name. if it has a space
//	it will need to be surrounded by a pair of quotes (or "). keyvalue pairs work like:
//	"keyname" "valuename"
//	the key will have a seperate string to the value and you can get these seperatly
//	by functions.
//
//	comments are opened by [ and closed by ]. you can have [] in "" strings but
//	outside of strings they act as comments.
//
//------------------------------------------------------------
//------------------------------------------------------------
class keyvalues
{
public:
	keyvalues() = default;

	//--------------------------------------------------------
	//
	//	The Open File function returns a bool. so if the file does open
	//	and the file does have something in it then it will return true.
	//	otherwise it will return false because what are you gonna do with
	//	an empty file?? this is also a bool so you can use this in an if
	//	statement
	//	
	//--------------------------------------------------------
	bool OpenFile(const std::string& filename);

	//--------------------------------------------------------
	//
	//	The open buffer function makes it so you can use a plain
	//	string instead of opening a file. again this is a bool so
	//	if the buffer is empty it will return false. this is also
	//	a bool so you can use this in an if statement
	//	
	//--------------------------------------------------------
	bool OpenBuffer(const std::string& buffer);

	//--------------------------------------------------------
	//
	//	the GetFirstSubkey is a very important function. what it does
	//	is it returns name of the 1st subkey and the content inside 
	//	of the 1st subkey. so if this was my file or buffer
	//
	//	"subkey"
	//	{
	//		"key" "value"
	//		"key2" "value2"
	//	}
	//
	//	then it would return subkey2 for the name and only the content 
	//	inside of the subkey. not outside the subkey. so it will use the 
	//	content inside of the subkey until the matching '}' for the '{' of
	//	the opening subkey is found
	//
	//	here is how i would get a nested subkey
	//
	//	keyvalues* main = new keyvalues();
	//	if (!main->OpenFile("main.txt")) {
	//		keyvalues* kv = main->GetFirstSubkey();
	//		if (kv != nullptr) {
	//			KeyValues* kv2 = kv->GetFirstSubkey();
	//			if (kv2 != nullptr)
	//			{
	//				//you now have access to the nested subkey
	//			}
	//		}
	//	}
	//
	//--------------------------------------------------------
	keyvalues* GetFirstSubkey();

	//--------------------------------------------------------
	//
	//	the GetNextSubkey does the exact same thing as the GetFirstSubkey
	//	does except it returns the next subkey instead of the 1st subkey
	//	so if this were my file or buffer
	//
	//	subkey1
	//	{
	//		"nested subkey"
	//		{
	//			"key" "value"
	//		}
	//		"key" "value"
	//	}
	//	subkey2
	//	{
	//		"key" "value"
	//	}
	//
	//	then it would return subkey2. you can use these 2 functions to 
	//	get all the subkeys (not nested) in the file or buffer by a for 
	//	or while loop. thats why i made the FOR_EACH_SUBKEY define for the subkeys
	//
	//--------------------------------------------------------
	keyvalues* GetNextSubkey();

	//--------------------------------------------------------
	//
	//	the GetFirstValue returns the 1st keyvalue pair in the subkey or file.
	//	so if i had "idkkey" "idkval" then it would return the name as idkkey and the
	//	string as idkval. you can do this in subkeys aswell by going
	//
	//	keyvalues* main = new keyvalues();
	//	if (!main->OpenFile("main.txt")) {
	//		keyvalues* kv = main->GetFirstSubkey();
	//		if (kv != nullptr) {
	//			KeyValues* kv2 = kv->GetFirstValue();
	//			if (kv2 != nullptr)
	//			{
	//				//you now have access to the 1st keyvalue pair
	//				//in the subkey
	//			}
	//		}
	//	}
	//
	//	if you dont want to get the value from in the subkey then you can just do 
	//	all that but except make kv be main->GetFirstValue() instead of main->GetFirstSubkey();
	//	once you have done this you CANNOT do any of the keyvalues* Get*() functions on this
	//	keyvalue pair
	//
	//--------------------------------------------------------
	keyvalues* GetFirstValue();

	//--------------------------------------------------------
	//
	//	the GetNextValue is the same thing as the function above except it returns
	//	the next keyvalue pair instead of the 1st keyvalue pair. you can use this in
	//	a loop to get each key in the subkey or file. i made a #define for this loop
	//	its called FOR_EACH_VALUE and it returns each keyvalue pair
	//
	//	so if i had 
	//	"idkkey" "idkval" 
	//	"key2" "value2"
	//
	//	then it would return the name as key2 and the
	//	string as value2 because that keyvalue pair was
	//	the second keyvalue pair in the file/buf/subkey.
	//	you can do this in subkeys aswell by the way.
	//
	//--------------------------------------------------------
	keyvalues* GetNextValue();

	//--------------------------------------------------------
	//
	//	FindKey returns either a keyvalue pair or a subkey section
	//	depending on what it finds first. it looks throuh every subkey 
	//	and keyvalue pair (not ones in subkeys) and if it finds a keyvalue
	//	pair of subkey section then it will return that
	//
	//--------------------------------------------------------
	keyvalues* FindKey(const std::string& key);

	//--------------------------------------------------------
	//
	//	This will return the subkey name if this instance of keyvalues*
	//	is a subkey. but if this instance of keyvalues* is a keyvalue pair 
	//	then it would return the key name
	//
	//--------------------------------------------------------
	const std::string GetName() const;

	//--------------------------------------------------------
	//
	//	This will return ""if this instance of keyvalues*
	//	is a subkey because the subkey only uses 1 string instance 
	//	not 2 like the keyvalue pair.
	//	but if this instance of keyvalues* is a keyvalue pair 
	//	then it would return the key's value
	//
	//	this has 2 arguments but you dont need to input any 
	//	arguments. the 1st 1one is the name of the keyvalue pair you 
	//	want to find, and if it does find that then it will return 
	//	the value of that keyvalue pair, else it will return the default value
	//
	//	if you dont input anything then it will just return the string of
	//	this keyvalue pair or subkey.
	//
	//	if you do use parameters then use them on a subkey only, this wont 
	//	work on keyvalue pairs
	//	
	//--------------------------------------------------------
	const std::string GetString(const std::string& Key = "", const std::string& defvalue = "");

	//--------------------------------------------------------
	//
	//	if the value is an int then it will return the values
	//	value as an int. but if the values value is not an int
	//	then dont worry. it wont return some odd number like 
	//	-243092398531 or something (i just typed a random number)
	//	it will instead return 0
	//
	//	this has 2 arguments but you dont need to input any 
	//	arguments. the 1st one is the name of the keyvalue pair you 
	//	want to find, and if it does find that then it will return 
	//	the value of that keyvalue pair, else it will return the default value
	//
	//	if you dont input anything then it will just return the int of
	//	this keyvalue pair or subkey.
	//
	//	if you do use parameters then use them on a subkey only, this wont 
	//	work on keyvalue pairs
	//
	//--------------------------------------------------------
	const int GetInt(const std::string& Key = "", const std::string& defvalue = "");

	//--------------------------------------------------------
	//
	//	basically the same as above so..
	// 
	//	if the value is a floating point number then it will return 
	//	the values value as a float. but if the values value is not an float
	//	then dont worry. it wont return some odd number like 
	//	-3423.0025344242e1 or something (i just typed a random number again)
	//	it will instead return 0
	//
	//	this has 2 arguments but you dont need to input any 
	//	arguments. the 1st one is the name of the keyvalue pair you 
	//	want to find, and if it does find that then it will return 
	//	the value of that keyvalue pair, else it will return the default value
	//
	//	if you dont input anything then it will just return the float of
	//	this keyvalue pair or subkey.
	//
	//	if you do use parameters then use them on a subkey only, this wont 
	//	work on keyvalue pairs
	//
	//--------------------------------------------------------
	const float GetFloat(const std::string& Key = "", const std::string& defvalue = "");

	//--------------------------------------------------------
	//
	//	gets the pointer (you cant set the pointer in the file but 
	//	you can use the SetPtr function to set the pointer
	//
	//--------------------------------------------------------
	template<typename T>
	const T& GetPtr() const;

	//--------------------------------------------------------
	//
	// Same as above but without template
	//
	//--------------------------------------------------------
	const void* GetPtr() const;


	//--------------------------------------------------------
	//
	//	If this is set to true. the all the keys and values from now
	//	on (this includes: subkeys, keyvalue pairs, nested subkeys etc...)
	//	will use the escape sequence. the default value is false so it will
	//	not use the escape sequence. so if this was my name "hello\nworld" and 
	//	this were my value "bb\ts" and i did UseEscapeSequence(true)
	//	then i did GetName would be 
	//
	//	hello
	//	world
	//
	//	and my value would be 
	//
	//	bb	s
	//
	//	but if i didnt change DoEscapeSequence then the name and string
	//	would stay the same and wouldnt be changed
	// 
	//	here is a list of escape sequence charactors
	//	
	//	\n = newline
	//	\t = tab
	//	\b = backspace
	//	\r = carriage return character
	//	\' = "
	//	\\ = \
	//
	//--------------------------------------------------------
	void UseEscapeSequence(bool val);

	//--------------------------------------------------------
	//
	//	sets the pointer to the input pointer of the function
	//
	//--------------------------------------------------------
	void SetPtr(void* newptr);

	//--------------------------------------------------------
	//
	//	Sets the value to the input string of the function
	//
	//--------------------------------------------------------
	void SetName(const std::string& value);

	//--------------------------------------------------------
	//
	//	Sets the value to the input int of the function
	//
	//--------------------------------------------------------
	void SetValue(const std::string& value);

	//--------------------------------------------------------
	//
	//	Sets the value to the input int of the function
	//
	//--------------------------------------------------------
	void SetValue(const int& value);

	//--------------------------------------------------------
	//
	//	Sets the value to the input float of the function
	//
	//--------------------------------------------------------
	void SetValue(const float& value);

private:

	std::vector<Token> GetToken();
	std::vector<Token> tokens;
	std::string fbuf;

	keyvalues* m_bPeer;
	keyvalues* m_bVal;

	bool UsesEscapeSequence = false;

	int i = 0, FirstSubkey = 0, v = 0, FirstKey = 0;

	std::string name, value;

	//void ptr
	void* ptr;
};

//--------------------------------------------------------
//
//	here are the defines for FOR_EACH_SUBKEY and FOR_EACH_VALUE
//	it returns each subkey/keyvalue pair 1 after the other.
//	you can also do this in subkeys or nested subkeys
//
//--------------------------------------------------------
#define FOR_EACH_SUBKEY(root, kv) \
for (keyvalues* kv = root->GetFirstSubkey(); kv != nullptr; kv = root->GetNextSubkey())

#define FOR_EACH_VALUE(root, kv) \
for (keyvalues* kv = root->GetFirstValue(); kv != nullptr; kv = root->GetNextValue())

#endif