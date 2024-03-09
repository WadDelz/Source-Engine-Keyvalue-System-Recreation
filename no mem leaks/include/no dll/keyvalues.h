#ifndef _KEYVALUES_H
#define _KEYVALUES_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>

#pragma once

//IMPORTANT #DEFINE
//If you have a keyvalues* that opened a file. and another keyvalues* that is the first subkey of 
//1st keyvalues*. then you open a new file with the original keyvalues*. the other keyvalues* that you used to get 
//the first subkey of the 1st keyvalues* will get deleted. if you dont want that to happen make this 
//false
#define KEYVALUES_DELETE_ON_OPEN_NEW_FILE true

unsigned long long atoull(const char* str);

class keyvalues;

struct KvTree
{
	std::vector<keyvalues*> kvs;
};

class keyvalues
{
public:

	enum KVTypes_T {
		TYPE_NONE,
		TYPE_INT,
		TYPE_UINT,
		TYPE_UINT64,
		TYPE_FLOAT,
		TYPE_STRING,
		TYPE_BOOL,
	};

	keyvalues();
	keyvalues(const std::string& name);
	keyvalues(const std::string& name, const std::string& value);

	bool OpenFile(const std::string& filename);
	bool OpenBuffer(const std::string& buffer);
	
	const bool IsEmpty() const;
	const bool IsSubkey() const;

	const std::string GetName() const;
	const int GetNameAsInt() const;
	const unsigned int GetNameAsUInt() const;
	const uint64_t GetNameAsUInt64() const;
	const float GetNameAsFloat() const;
	const bool GetNameAsBool() const;
	const bool IsNameEmpty() const;

	const std::string GetString(const std::string& ByVal = "", const std::string& Def = "") const;
	const int GetInt(const std::string& ByVal = "", const int& Def = 0) const;
	const unsigned int GetUInt(const std::string& ByVal = "", const unsigned int& Def = 0) const;
	const uint64_t GetUInt64(const std::string& ByVal = "", const uint64_t& Def = 0) const;
	const float GetFloat(const std::string& ByVal = "", const float& Def = 0) const;
	const bool GetBool(const std::string& ByVal = "", const bool& Def = false) const;
	const bool IsStringEmpty(const std::string& KeyName = "") const;

	const int GetNumSubkeys() const;
	const int GetNumKVPairs() const;
	const int GetNumKeyvalues() const;

	const KVTypes_T GetNameType() const;
	const KVTypes_T GetValueType() const;

	void SetName(const std::string& name);
	void SetNameToInt(const int& name);
	void SetNameToUInt(const unsigned int& name);
	void SetNameToUInt64(const uint64_t& name);
	void SetNameToFloat(const float& name);
	void SetNameToBool(const bool& name);

	void SetString(const std::string& val);
	void SetInt(const int& val);
	void SetUInt(const unsigned int& val);
	void SetUInt64(const uint64_t& val);
	void SetFloat(const float& val);
	void SetBool(const bool& val);

	void SetIsSubkey(const bool& is);

	void UseEscapeSequence(const bool& val);

	void WriteToFile(const std::string& filename);

	void DeleteThis();

	void RemoveEverything();

	void RemoveSubkeys();
	void RemoveKVPairs();
	void RemoveKeyvalues();

	void DeleteSubkeys();
	void DeleteKVPairs();
	void DeleteKeyvalues();

	void AddKeyvalues(keyvalues* m_Sub);
	void RemoveKeyvalues(keyvalues* m_Sub);

	keyvalues* GetFirstSubkey();
	keyvalues* GetNextSubkey();
	keyvalues* GetLastSubkey();

	keyvalues* GetFirstValue();
	keyvalues* GetNextValue();
	keyvalues* GetLastValue();

	keyvalues* GetFirstKeyvalue();
	keyvalues* GetNextKeyvalue();
	keyvalues* GetLastKeyvalue();

	keyvalues* GetParent();
	
	keyvalues* FindKey(const std::string& key);
	keyvalues* FindKeyRecursive(const std::string& key);

	keyvalues* FindSubKey(const std::string& key, bool bCreate = false);
	keyvalues* FindSubKeyRecursive(const std::string& key);

	keyvalues* FindKVPair(const std::string& key, bool bCreate = false);
	keyvalues* FindKVPairRecursive(const std::string& key);

	std::string WriteToString();

	enum TokenType {
		STRING,
		SUBKEY,
		KEY,
		VALUE,
		OPENSCOPE,
		CLOSESCOPE,
	};

	struct Token
	{
		keyvalues::TokenType token;
		std::string value;
	};

private:

	std::vector<Token> GetTokens(const std::string& filename, bool Buf = false);
	void GetTree(const std::vector<Token>& tokens);
	keyvalues* GetTreeKv(const std::vector<Token>& tokens, int& i, keyvalues* prev);
	keyvalues* GetTreeSub(const std::vector<Token>& tokens, const std::string& name, keyvalues* prev);
	keyvalues* m_bPrev;
	
	KVTypes_T NameType;
	KVTypes_T ValueType;

	KvTree tree;
	int Subkey = 0, KVPair = 0, kv = 0;
	bool IsSubKey = false, UsesEscapeSequence = false;

	std::string Name, Value;

	union
	{
		int IName;
		unsigned int UIName;
		uint64_t UI64Name;
		float FName;
		bool BName;
	};

	union
	{
		int IVal;
		unsigned int UIVal;
		uint64_t UI64Val;
		float FVal;
		bool BVal;
	};

	void WriteSubkey(std::ofstream& file, keyvalues* kv, int& scope);
	void WriteKVPair(std::ofstream& file, keyvalues* kv, int& scope);

	void WriteSubkey(std::ostringstream& file, keyvalues* kv, int& scope);
	void WriteKVPair(std::ostringstream& file, keyvalues* kv, int& scope);
};

#define FOR_EACH_SUBKEY(root, kv) \
for (keyvalues* kv = root->GetFirstSubkey(); kv != nullptr; kv = root->GetNextSubkey())

#define FOR_EACH_VALUE(root, kv) \
for (keyvalues* kv = root->GetFirstValue(); kv != nullptr; kv = root->GetNextValue())

#define FOR_EACH_KEYVALUE(root, kv) \
for (keyvalues* kv = root->GetFirstKeyvalue(); kv != nullptr; kv = root->GetNextKeyvalue())

#endif