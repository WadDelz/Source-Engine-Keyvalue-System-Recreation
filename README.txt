im 99% sure this has little to no errors at all.

I Recreated The Source Engines Keyvalue System From Scratch In Cpp 
(PLEASE DONT JUDGE THE SOURCE CODE IM NOT THAT GOOD AT CODING :) ) 
also the lib and dll was compiled in vscode 2013 so it might not work 
in newer versions. but the source code probably will (:.

YOU DONT HAVE TO BUT I SUGGEST YOU TO READ THIS. IT EXPLAINS EVERY FUNCTION AND HOW TO USE IT CAUSE THERE ARE ALOT OF FUNCTIONS.

original keyvalues class made by Valve Software 

the keyvalue system is a file and buffer reader. it reads the file or buffer then turns them into a tree of keyvalues. there are 2 types of keyvalues, 1 is called a subkey and 
the other is called a keyvalue pair. subkeys and keyvalue pairs are a little different so ill explain them seperatly. 

KEYVALUE TYPES:
	
	SUBKEYS:
	
		subkeys are abit like a container. it can hold/contain other subkeys and other keyvalue pairs. every subkey has a key that can be represented either by 
		a: string, int, unsigned int, unsigned 64-bit int, float or bool. in the file and buffer the subkey is made by a key then a {. the subkey is then closed by a }. 
		you can have multiple subkeys in subkeys aslong as there is a } for every subkey. you get the key's name by a function. there is a rule for every single subkeys key 
		in the file and or buffer. if the key contains a space anywhere, then it needs to be surrounded by a pair of ". if its not then it could lead to undifiend 
		behaviour. 
		(note that you can have a key with no space and surrounded it with a pair of ")
		
		here is an example of how i would use/make subkeys in the file or buffer.
		
			key
			{
				"nested subkey"
				{
				
				}
			}
		
		note that the file and buffer can have there subkeys on 1 or 2 or 3 etc... lines like the example down below
		
			key { "nested subkey" {} }
		
		or like this:
		
			key { "nested subkey" {
			} }
		
		i just make the subkeys look like how i/valve does because it looks better then the mess above.
		you can get all they sunkeys in a file or buffer by functions (ill explain them in the function sections)
	
	KEYVALUE PAIRS:
	
		keyvalue pairs are abit different to subkeys. with keyvalue pairs you cant hold/contain other subkeys or keyvalue pairs like with subkeys. and with the keyvalue pairs it 
		doesnt just have a key. it also ha a value. so instead of there just being 1 key followed by {, there is a key then the value. the name and value 
		is also represented by either a: string, int, unsigned int, unsigned 64-bit int, float or bool. you can get the key and value by seperate functions.
		the keyvalue's key and value have the exact same logic to the subkeys key. if in the file or buffer the key and or value has a space. 
		it needs to be surrounded by a pair of ". 
		(note that you can have a key with no space and surrounded it with a pair of ")
		keyvalues can be placed anywhere in the file or buffer. 
		
		here is an example of a keyvalue pair 
		
			"key" "value"
			
		here is an example of subkeys with keyvalue pairs
		
			"entities"
			{
				"weapon_portalgun"
				{
					targetname portalgun
					"origin" "0 250 0"
					"angles "1 254 43"
				}
			}
			
		remember that you can have the subkeys and or keyvalue pairs on different lines i just make it look like that to orginise them.
		you can get all they keyvalue pairs in a file or buffer by functions (ill explain them in the function sections)
		
	
COMMENTS:

	there are 2 types comments for the file but only 1 type for the buffer. in the file there are 2 types of comments. 1 type is just a standerd c++ comment
	
	example:
	
		key value //this is a comment. the line will end here so this "key2" "value2" wont get recognised as a keyvalue pair
		
	and the other is the multi line comment
	
		subkey {
		
			/*the multi line comment starts by a / then a *. it spreads across multiple lines (or just 1)
			and stops when it hits a * followed by a /
						
			so the code below 
			
			subkey {
				"nested key" "nested value"
			}
			key1 val2
			
			wont get recognised. this will be the end of the comment > */
			
			key value // this keyvalue pair will get recognised
		}
	
	in the buffer only the /* one works because it reads the entire thing as a string not like the file that reads it line by line 
	(note that just because the file is read line by line it doesnt mean that you cant start a key and or value on 1 line using the " and end it
	on another line because you can do that).
	
IMPORTANT DEFINE

	there is a #define in keyvalues.h file. this is what it does:
	
	If you have a keyvalues* that opened a file. and another keyvalues* that is the first subkey of 
	1st keyvalues*. then you open a new file with the original keyvalues*. the other keyvalues* that you used to get 
	the first subkey of the 1st keyvalues* will get deleted. if you dont want that to happen make this 
	false
	
	KEYVALUES_DELETE_ON_OPEN_NEW_FILE true

FUNCTIONS:
	note whenever i say only works on subkeys i usually mean only works on subkeys and the main keyvalues* (the keyvalues* that you make
	with the new keyword).
	
	here are a list of all the function in the keyvalue class (that are public)
		
		--------------------------- Constructors ---------------------------
		keyvalues();
		keyvalues(const std::string& name);
		keyvalues(const std::string& name, const std::string& value);
		
		There are 3 constructors. (only use the 2nd and 3rd constructor when doing keyvalue making
									explination to that later).
		
		the 1st constructor is the default constructor. it sets every keyvalue member/variable to its
		default state.
		
		the 2nd constructor is abit differant. this constructor takes in a string. this string will make 
		it so this keyvalues* will act like a subkey. meaning you can put other subkeys or keyvalue pairs 
		in this keyvalues* (note i will explain what keyvalue making is abit later and how to do it). 
		it also makes the key's name be the input name.
		
		the 3rd constructor takes in 2 strings. this makes it so this keyvalues* is a keyvalue pair.
		the 2 strings sets the keyvalues*'s key's name and value's name. this will act like a keyvalue
		pair.
		----------------------------------------------------------------------
		
		
		
		--------------------------- Open Functions ---------------------------
		bool OpenFile(const std::string& filename);
		bool OpenBuffer(const std::string& buffer);
		
		these are the 2 functions that open the file and buffer. 
		
		OpenFile opens up a file. it then tokenises it. after that it parses it then makes it so this 
		keyvalues* instance will have all the keyvalue data from the file (inluding keyvalue pairs, subkeys
		subkeys names, etc...) it is a bool so if the file fails to open, the file is empty or it fails
		to tokenise because of errors it will return false. so you can use this in an if statement.
		
		e.g
		
		keyvalues* kv = new keyvalues();
		if (!kv->OpenFile("main.txt"))
			//do what you want!! return, print error message etc...

		the OpenBuffer function does the exact same thing as the OpenFile Execpt it Opens/uses a string as an 
		input instead of a filename. its also a bool.
		----------------------------------------------------------------------
		
		
		
		--------------------------- Is Functions ---------------------------
		const bool IsEmpty() const;
		const bool IsSubkey() const;
		
		the IsEmpty function returns true if there are no keyvalues* (like subkeys or keyvalue pairs) 
		in the current keyvalues*. note you should only use this on keyvalues* that are subkeys because
		keyvalue pairs dont have any keyvalue pairs and subkeys in them.
		
		the IsSubkey function returns true if the current keyvalues* is a subkey. this is usefull for the 
		GetKeyvalue functions (explination later).
		---------------------------------------------------------------------
	
	
	
		--------------------------- GetName Functions ---------------------------
		const std::string GetName() const;
		const int GetNameAsInt() const;
		const unsigned int GetNameAsUInt() const;
		const uint64_t GetNameAsUInt64() const;
		const float GetNameAsFloat() const;
		const bool GetNameAsBool() const;
		const bool IsNameEmpty() const;
		
		now there are alot of functions for the get name.
		
		i need to tell you about the keyvalue type system before i explain how to use this.
		so when the keyvalue pair or subkey is created. it does a check to see if the key or value is either 
		
		TYPE_INT = an int: 						not equal to 0 or 1, more then or equal to -2147483647 and less then or equal to 2147483647.
		TYPE_UINT = an unsigned int: 			not equal to 0 or 1, more then 2147483647 and less then or equal to 4294967295.
		TYPE_UINT64 = an unsigned 64-bit int: 	not equal to 0 or 1, more then 4294967295 and less then or equal to 9223372036854775808.
		TYPE_FLOAT = a float:					more then or equal to 1.175494351e-38 and less then or equal to 3.402823466e+38F. (uses decimle place)
		TYPE_BOOL = a bool:						equal to 0 or 1.
		TYPE_STRING = a string: 				if none of the conditions above are true.
		
		it then gives the keyvalues*'s key and value a type based on what it is above. (when you make a keyvalues* with an empty constructor it makes the 
		type TYPE_NONE which is no type). it then gives the type of variable the the value of the key or value (there are ints, unsigned ints, 
		unsigned 64 bit ints, etc... stored in 2 unions (1 for the key, 1 for the value) in the keyvalues* class for the name and value (a union is a 
		static cpp function/thing that holds data, sorry shit explination look it up and you'll understand what it is if you dont already. 
		it'll make the rest of this explination make sense)).

		the reason i made the type system is so the keyvalue system knows if it can or cant get it/the key or value. for example if 
		the key/name is an unsigned int and i wanted to get it/(the name) as an int using the GetNameAsInt function there would be a problem. it 
		doesnt know what type the keyvalues*'s name is. and because its an unsigned int (aka bigger then an int) it wouldnt work and could crash (maybe). 
		but because i made the type system, it'll know that i cant get the int because the name is an unsigned int. anyways onto the functions.
		
		the Get functions returns the value of the key in the keyvalue pair or subkey. so if i had this as my subkey
		
			"bob" {
				"hello" "world"
			}
			
		and i used GetName on the subkey. it would then return "bob" (without the ") because bob is the name of the key of the subkey. same 
		thing for the keyvalue pair in the subkey. if i used GetName on it. it would return "hello" (without the "). if i tried to use any other 
		GetName function like GetNameAsInt() then because of the type system. it knows the keys type is a TYPE_STRING so it would just return 0.
		
		the rules apply for the key as they do for the types (more then ... and less then ...) so if the keys value was 432432 it would know 
		thats an int. so i could get that by using GetNameAsInt() GetNameAsUInt() GetNameAsUInt64() GetNameAsFloat() or GetName() (GetName() works
		cause it converts the int to a string) and the other functions that i mentioned work because they can store data that is that big.
		
		if i used GetBool() then it would return true if the key isnt 0 and false if the key is 0.
		
		the IsNameEmpty() function returns true if the key doesnt contain anything. so if this was my keyvalue pair
		
			"" "hello"
			
		and i used IsNameEmpty() it would return true cause there is nothing in the name. it will return true though if i had " "
		as my name cause a space is something.
		-------------------------------------------------------------------------
		
		
		
		--------------------------- GetValue Functions ---------------------------
		const std::string GetString(const std::string& ByVal = "", const std::string& Def = "") const;
		const int GetInt(const std::string& ByVal = "", const int& Def = 0) const;
		const unsigned int GetUInt(const std::string& ByVal = "", const unsigned int& Def = 0) const;
		const uint64_t GetUInt64(const std::string& ByVal = "", const uint64_t& Def = 0) const;
		const float GetFloat(const std::string& ByVal = "", const float& Def = 0) const;
		const bool GetBool(const std::string& ByVal = "", const bool& Def = false) const;
		const bool IsStringEmpty(const std::string& KeyName = "") const;
		
		there are 2 ways you can use these functions. 
		
		the 1st way is the normal way. the normal way only works on keyvalue pairs. and it returns the value of the keyvalue pair. 
		if you use this function this way then you need to not input any parameters into the function. the same type system for the 
		key is also applied for the value. so if the value is an unsigned int and i try to use GetInt() then it wont work and will
		return 0.
		
		the 2nd way is the differant way. this way only works on subkeys. if you decide to input a string into the 1st function
		parameter. then it will search every keyvalue pair in this subkey. (only the ones in this subkey not the keyalue pairs in nested subkeys)
		and if it finds a keyvalue pair with the key's value being that of the input parameter, then it will return the value of thay keyvalue pair.
		if it doesnt find a keyvalue pair with its key having the value of the input parameter then it will just return the input value of the 2nd parameter.
		
		the IsStringEmpty has the same logic with the parameters.
		
		so if you use no parameters it will return if the value of the string is empty/has nothing in it like "". this version only
		works on keyvalue pairs.
		
		the 2nd version is used on subkeys. and if it finds a keyvalue pair in this subkey (not in nested subkeys) that has the same name
		then it will return if the key's value is empty (like "").
		--------------------------------------------------------------------------
		
		
		
		--------------------------- GetNum Functions ---------------------------
		const int GetNumSubkeys() const;
		const int GetNumKVPairs() const;
		const int GetNumKeyvalues() const;
		
		these functions only work on subkeys and not keyvalue pairs. it returns the ammount of: subkeys, keyvalue pairs and (subkeys and keyvalue pairs).
		so if i had a subkey that contained 2 subkeys and 5 keyvalue pairs. then i used GetNumKeyvalues() then it would return 7 cause thats the total
		number of keyvalues* in this subkey. (note it doesnt use nested subkeys or keyvalue pairs)
		------------------------------------------------------------------------



		--------------------------- GetType Functions ---------------------------
		const KVTypes_T GetNameType() const;
		const KVTypes_T GetValueType() const;
		
		i know i listed the types before but imma list them again.
		
		TYPE_NONE.
		TYPE_INT.
		TYPE_UINT.
		TYPE_UINT64.
		TYPE_FLOAT.
		TYPE_STRING.
		TYPE_BOOL.
		
		the GetNameType() function returns the type of the key's value. the GetValueType() returns the type of the value's value. (the types are defined
		in keyvalues::KVTypes_T. (its an enum)
		-------------------------------------------------------------------------
		
		
		
		--------------------------- SetName Functions ----------------------------
		void SetName(const std::string& name);
		void SetNameToInt(const int& name);
		void SetNameToUInt(const unsigned int& name);
		void SetNameToUInt64(const uint64_t& name);
		void SetNameToFloat(const float& name);
		void SetNameToBool(const bool& name);
		
		this sets the key's value of the subkey or keyvalue pair to the input name. this also sets the type so if i did SetNameToFloat() it would set the
		keys type to TYPE_FLOAT.
		--------------------------------------------------------------------------
		
		
		
		--------------------------- SetValue Functions ----------------------------
		void SetString(const std::string& val);
		void SetInt(const int& val);
		void SetUInt(const unsigned int& val);
		void SetUInt64(const uint64_t& val);
		void SetFloat(const float& val);
		void SetBool(const bool& val);
		
		the same thing as the SetName functrions except it sets the value's value not the key's value.
		this doesnt work on subkeys.
		---------------------------------------------------------------------------
		
		
		
		--------------------------- SetSubkey Functions ----------------------------
		void SetIsSubkey(const bool& is);
		
		this is used for keyvalue making (explination later). if the input value is true then it will make it so this keyvalues* is a subkey and
		vice versa.	
		--------------------------------------------------------------------------
		
		
		
		--------------------------- Escape Sequence ----------------------------
		void UseEscapeSequence(const bool& val);
		
		(use this before using OpenFile or OpenBuffer)
		every subkey/keyvalue pair made from this keyvalues* will use the escape sequence if the input val is true. if any keyvalues* does use
		the escape sequence then when using GetName or GetString then it will return the name (or string) with the escape sequence. that kinda didnt
		make sence so here is an example.
		
		if this was my keyvalue pair
		
		"print" "hello\nworld"
		
		and that keyvalue pair uses the escape sequence. if i used GetString it would return the string with the escape sequence. so it would return
		
		hello
		world
		
		instead of 
		
		hello\nworld
		
		these are the usable escape sequence characters that are valid
		
		\n - newline
		\t - tab
		\b - backspace
		\r - return carrage character
		\' - "
		\\ = \
		------------------------------------------------------------------------
		
		
		
		--------------------------- Write To File ----------------------------
		void WriteToFile(const std::string& filename);
		
		only works on subkeys. this function writes every single keyvalue pair and subkey in that keyvalues* to the input 
		file. it also makes the file valid so i can use OpenFile on the file. 
		-----------------------------------------------------------------------
		
		
		
		--------------------------- Delete This ----------------------------
		void DeleteThis();
		
		if you want to delete a keyvalues* then use DeleteThis and not delete keyvalues*name. this deletes every subkey and keyvalue
		pair inside this (including nested) then deletes that instance of the keyvalues*.
		--------------------------------------------------------------------
		
		
		
		--------------------------- Remove Everything ----------------------------
		void RemoveEverything();
		
		sets every string to "" resets every bool and union. and also sets the type to TYPE_NONE. if KEYVALUES_DELETE_ON_OPEN_NEW_FILE 
		is true then it will delete every single subkey and keyvalue pair inside this (including nested). if it is set to false though it
		will only remove then.
		--------------------------------------------------------------------------
		
		
		
		--------------------------- Remove Keyvalues ----------------------------
		void RemoveSubkeys();
		void RemoveKVPairs();
		void RemoveKeyvalues();
		
		these only work on subkeys. the RemoveSubkeys removes (doesnt delete) every subkey in this keyvalues* from the current keyvalues*. 
		the RemoveKVPairs does the same thing but just for keyvalue pairs. the RemoveKeyvalues() removes every keyvalues* in this.
		-------------------------------------------------------------------------
		
		
		
		--------------------------- Delete Keyvalues ----------------------------
		void DeleteSubkeys();
		void DeleteKVPairs();
		void DeleteKeyvalues();
		
		these functions are the exact same as the functions above except it deletes the keyvalues* not removes them from this
		keyvalues*.
		-------------------------------------------------------------------------
		
		
		
		--------------------------- Keyvalue Making ----------------------------
		void AddKeyvalues(keyvalues* m_Sub);
		void RemoveKeyvalues(keyvalues* m_Sub);
		
		you can make your own keyvalue structure without opening a file or buffer. the AddKeyvalues function makes it so you
		add the input keyvalues* (you need to make a new keyvalues then set its key's value and or value's value, you
		can do this by the constructor or by SetName or SetNameTo*** and Set***. also note that the constructors gives the 
		right type the right value. so if the input name for the constructor was "1321" it would make the type a TYPE_INT.
		also also note that if you use the 1st constructor (the one that takes in just a name and no value) then it automatically 
		makes that keyvalues* a subkey. and if you do the 2nd constructor (the one that takes in a name and value) then it makes 
		it a keyvalue pair.) to the keyvalues* that you use the -> on's tree. (a tree is a structure that holds all the subkeys and 
		keyvalue pairs). this is why i made the SetIsSubkey and IsSubkey function so you can add subkeys and add keyvalue pairs. 
		(note you cant use this function on keyvalue pairs it only works on subkeys)
		
		the RemoveKeyvalues function goes through every keyvalue* in the keyvalues*'s tree (the keyvalues* that you use -> on).
		if it finds that exact keyvalue pointer (the one that is the same as the input pointer) then it will remove it from the 
		tree.
		-------------------------------------------------------------------------
		
		
		
		--------------------------- Get Subkey Functions ----------------------------
		keyvalues* GetFirstSubkey();
		keyvalues* GetNextSubkey();
		keyvalues* GetLastSubkey();
		
		these functions are kind of the boss of the keyvalues class. without them you coundnt get subkeys. these functions only work on subkeys.
		
		the GetFirstSubkey function returns the 1st subkey in the file/buffer/current keyvalues* instance. that isnt a good explination so
		here is an example.
		
		say this is my file:
		
		
		"weapon_ar2"
		{
			"targetname" "bob"
			"origin" "323 24 654"
			"keyvalues" 
			{
				"key" "value"
			}
		}
		"instant_trigger"
		{
			"origin" "0 0 100"
			"keyvalues" 
			{
				"radius" "100"
				"ontrigger" "!player,sethealth,0,0,-1"
			}
		}
		"logic_auto"
		{
			"keyvalues" 
			{
				"onmapspawn" "idk some output"
			}
		}
		
		and i opened it. then made a new keyvalues* that uses the GetFirstSubkey function on the keyvalues* that i used to open 
		the file. then it would return a keyvalues* with the name being that of the 1st subkey (in this case weapon_ar2) and 
		all that subkeys data. (every keyvalue pair and subkey in it)
		
		the GetNextSubkey returns the next subkey in the file/buffer/current keyvalues* instance (not nested subkeys). i can use this function multiple
		times to get each subkey in a file. so if i had the keyvalues* that i used to get the first subkey and i made it so that keyvalues*
		had the value GetNextValue() using the keyvalues* that i used to get the first subkey. 
		
		example:
		
		keyvalues* kv = new keyvalues();
		if (!kv->OpenFile("main.txt"))
			return;
			
		keyvalues* kv2 = kv->GetFirstSubkey();
		kv2 = kv->GetNextSubkey();
		
		then i printed the name of the kv2. it would print instant_trigger. i made a #define that and its called FOR_EACH_SUBKEY. 
		it gets every single subkey (1 after the other) in the current keyvalues* instance. if there are no more subkeys in that main 
		keyvalues* (the one that you used GetFirstSubkey on) then it would return nullptr.
		
		the GetLastSubkey() returns the last subkey in the file/buffer/current keyvalues* instance. so in the example above it would
		return a subkey with the name being logic_auto and the subkeys and keyvalue pairs of that subkey.
		-----------------------------------------------------------------------------
		
		
		
		--------------------------- Get Keyvalue Pairs Functions ----------------------------
		keyvalues* GetFirstValue();
		keyvalues* GetNextValue();
		keyvalues* GetLastValue();
		
		these functions get the keyvalue pairs. so if this was my file/buffer/current keyvalues* instance
		
		"main"
		{
			"name" "bob"
			"age" "65"
			"height" "6.1"
		}
		
		and this was my code:
		
		keyvalues* main = new keyvalue();
		if (!main->OpenFile("main.txt"))
			return;
		
		keyvalues* kv = main->GetFirstSubkey();
		keyvalues* kv2 = kv->GetFirstValue();
		//print kv2's name '\n
		kv2 = kv->GetNextSubkey();
		//print kv2's name '\n
		
		then it would print out
		
		name
		age
		
		you cant use any GetKeyvalue functions on keyvalue pairs.
		
		GetLastValue does the same as the GetLastValue except for keyvalue pairs.
		-------------------------------------------------------------------------------------
		
		
		
		--------------------------- Get Keyvalues Functions ----------------------------
		keyvalues* GetFirstKeyvalue();
		keyvalues* GetNextKeyvalue();
		keyvalues* GetLastKeyvalue();
		
		same as above goes through keyvalues* (not nested keyvalues) and returns it but this time it returns it if
		its a keyvalue pair or a subkey.
		
		GetLastKeyvalue returns the last keyvalue (not keyvalue pairs in subkeys).
		--------------------------------------------------------------------------------
		
		
		
		--------------------------- Get Keyvalue Parent Functions ----------------------------
		keyvalues* GetParent();
		
		this returns the parent of this keyvalues*. so if i had a keyvalues* that was a subkey in a nested subkey and i used
		GetParent on that nested subkey. it would return the subkey that the nested subkey is in. this also works for keyvalue pairs.
		so if i had a keyvalue pair in a subkey. and i used GetParent then it would return the subkey that the keyvalue pair is in.
		--------------------------------------------------------------------------------------
		
		
		
		--------------------------- Find Key Functions ----------------------------
		keyvalues* FindKey(const std::string& key);
		keyvalues* FindKeyRecursive(const std::string& key);
		
		keyvalues* FindSubKey(const std::string& key, bool bCreate);
		keyvalues* FindSubKeyRecursive(const std::string& key);
	
		keyvalues* FindKVPair(const std::string& key, bool bCreate);
		keyvalues* FindKVPairRecursive(const std::string& key);
		
		these functions can only be used on subkeys. the FindSubKey function returns a keyvalues*. it looks through each subkey (not nested
		subkeys). and if the subkey's key has the same value as the input name. then it will return that subkey. if u input bCreate as true then if
		the subkey doesnt get found. it will make a new subkey with that name and add it to the keyvalues* that u used the FindSubKey function on. 
		the FindSubKeyRecursive looks through every subkey. that means nested subkeys aswell. the FindKVPair and FindKVPairRecursive does the 
		same thing as the functions above. except these 2 functions search for keyvalue pairs and not subkey and if not found will make a new keyvalue
		pair with the input name and an empty string. the FindKey and FindKeyRecursive does the same things as above except it doesnt care if its 
		a subkey or not. so it returns the 1st keyvalues* it finds. if there are no keyvalues* with the name then it will return nullptr.
		----------------------------------------------------------------------------
		
		
		
		--------------------------- Write To String -----------------------------
		std::string WriteToString();
		
		write to string returns the entire keyvalues* class as a string. it makes the string look like how the file
		looks when you use WriteToFile.
		-------------------------------------------------------------------------
		
DEFINES
	
	------------------------------------------------------------------------------------------------
	#define FOR_EACH_SUBKEY(root, kv) \
	for (keyvalues* kv = root->GetFirstSubkey(); kv != nullptr; kv = root->GetNextSubkey())
	
	for each subkey goes through every subkey in the root's keyvalues* 1 by 1. it then makes it so the kv is the current subkey. it keeps doing this 
	until there are no subkeys left. (note it doesnt get nested subkeys)
	------------------------------------------------------------------------------------------------
	
	
	------------------------------------------------------------------------------------------------
	#define FOR_EACH_VALUE(root, kv) \
	for (keyvalues* kv = root->GetFirstValue(); kv != nullptr; kv = root->GetNextValue())
	
	for each value goes through every keyvalue pair in the root's keyvalues* 1 by 1. it then makes it so the kv is the current keyvalue pair. it 
	keeps doing this until there are no keyvalue pairs left. (note it doesnt get nested keyvalue pairs)
	------------------------------------------------------------------------------------------------
	
	
	------------------------------------------------------------------------------------------------
	#define FOR_EACH_KEYVALUE(root, kv) \
	for (keyvalues* kv = root->GetFirstKeyvalue(); kv != nullptr; kv = root->GetNextKeyvalue())
	
	for each value goes through every keyvalues* in the root's keyvalues* 1 by 1. it then makes it so the kv is the current keyvalues*. it 
	keeps doing this until there are no keyvalues* left. (note it doesnt get nested keyvalues)
	------------------------------------------------------------------------------------------------
