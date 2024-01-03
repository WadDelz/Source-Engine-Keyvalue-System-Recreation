#include "keyvalues.h"
#include <fstream>
#include <sstream>

std::string ConvertEscapeChars(const std::string& input) {
	std::string result;

	for (size_t i = 0; i < input.length(); ++i) {
		if (input[i] == '\\' && i + 1 < input.length()) {
			switch (input[i + 1]) {
			case 'n':
				result += '\n';
				break;
			case 'b':
				result += '\b';
				break;
			case 't':
				result += '\t';
				break;
			case 'r':
				result += '\r';
				break;
			case '\'':
				result += '"';
				break;
			case '\\':
				result += '\\';
				break;
			default:
				result += input[i];
				break;
			}
			++i;
		}
		else {
			result += input[i];
		}
	}

	return result;
}

bool keyvalues::OpenFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
		return false;

	{
		std::stringstream sstream;
		sstream << file.rdbuf();
		fbuf = sstream.str();
	}

	tokens = GetToken();

	if (tokens.size() != 0)
		return true;
	else
		return false;
}

bool keyvalues::OpenBuffer(const std::string& buffer)
{
	fbuf = buffer;

	tokens = GetToken();

	if (tokens.size() != 0)
		return true;
	else
		return false;
}

std::vector<Token> keyvalues::GetToken()
{
	std::vector<Token> TempTokens;
	std::string buffer;

	bool InStr = false, InComment = false, InNQStr = false;

	for (int j = 0; j < (int)fbuf.length(); j++) {
		char c = fbuf[j];
		if (InStr || InComment || InNQStr)
		{
			if (InStr)
			{
				if (c == '"') {
					InStr = false;
					tokens.push_back({ TokenType::STRING, buffer });
					buffer.clear();
				}
				else {
					buffer.push_back(c);
				}
			}
			else if (InComment)
			{
				if (c == ']') {
					InComment = false;
				}
			}
			else
			{
				if (isspace(c))
				{
					tokens.push_back({ TokenType::STRING, buffer });
					buffer.clear();
					InNQStr = false;
				}
				else
				{
					buffer.push_back(c);
				}
			}
		}
		else {
			if (c == '"') {
				InStr = true;
			}
			else if (c == '[') {
				InComment = true;
			}
			else if (c == '{') {
				tokens.push_back({ TokenType::OPENSCOPE, "{" });
			}
			else if (c == '}') {
				tokens.push_back({ TokenType::CLOSESCOPE, "}" });
			}
			else if (isalnum(c)) {
				buffer.push_back(c);
				InNQStr = true;
			}
		}
	}
	for (int j = 0; j < (int)tokens.size(); j++)
	{
		if (j + 1 < (int)tokens.size()) {
			if (tokens[j].token == TokenType::STRING && tokens[j + 1].token == TokenType::STRING) {
				TempTokens.push_back({ TokenType::KEY, tokens[j].value });
				TempTokens.push_back({ TokenType::VALUE, tokens[j + 1].value });
				if (j + 2 < (int)tokens.size()) {
					j++;
				}
			}
			else if (tokens[j].token == TokenType::STRING && tokens[j + 1].token == TokenType::OPENSCOPE) {
				TempTokens.push_back({ TokenType::SUBKEY, tokens[j].value });
				TempTokens.push_back({ TokenType::OPENSCOPE, "{" });
				if (j + 2 < (int)tokens.size()) {
					j++;
				}
			}
			else if (tokens[j].token == TokenType::STRING && tokens[j + 1].token == TokenType::CLOSESCOPE) {
				TempTokens.push_back({ TokenType::CLOSESCOPE, "}" });
				if (j + 2 < (int)tokens.size()) {
					j++;
				}
			}
		}

		if (tokens[j].token == TokenType::CLOSESCOPE) {
			TempTokens.push_back({ TokenType::CLOSESCOPE, "}" });
		}
	}

	return TempTokens;
}

const std::string keyvalues::GetName() const
{
	if (UsesEscapeSequence) {
		return ConvertEscapeChars(name);
	}
	else {
		return name;
	}
}

const std::string keyvalues::GetString(const std::string& Key, const std::string& defvalue)
{
	if (Key == "")
	{
		if (UsesEscapeSequence) {
			return ConvertEscapeChars(value);
		}
		else {
			return value;
		}
	}
	else {
		int tempv = this->v;
		FOR_EACH_VALUE(this, val)
		{
			if (val->GetName() == Key)
			{
				this->v = tempv;
				return val->GetString();
			}
		}
		this->v = tempv;
		return defvalue;
	}
}

const int keyvalues::GetInt(const std::string& Key, const std::string& defvalue)
{
	if (Key == "")
	{
		return atoi(value.c_str());
	}
	else {
		int tempv = this->v;
		FOR_EACH_VALUE(this, val)
		{
			if (val->GetName() == Key)
			{
				this->v = tempv;
				return atoi(val->GetString().c_str());
			}
		}
		this->v = tempv;
		return atoi(defvalue.c_str());
	}
}

const float keyvalues::GetFloat(const std::string& Key, const std::string& defvalue)
{
	if (Key == "")
	{
		return (float)atof(value.c_str());
	}
	else {
		int tempv = this->v;
		FOR_EACH_VALUE(this, val)
		{
			if (val->GetName() == Key)
			{
				this->v = tempv;
				return (float)atof(val->GetString().c_str());
			}
		}
		this->v = tempv;
		return (float)atof(defvalue.c_str());
	}
}

template<typename T>
const T& keyvalues::GetPtr() const
{
	return *reinterpret_cast<T*>(ptr);
}

const void* keyvalues::GetPtr() const
{
	return ptr;
}


keyvalues* keyvalues::GetFirstSubkey()
{
	if (m_bPeer == nullptr)
	{
		keyvalues* kv = new keyvalues;
		for (; i < (int)tokens.size(); i++) {
			if (tokens[i].token == TokenType::SUBKEY) {
				if (i + 2 < (int)tokens.size()) {
					int scope = 0;
					std::vector<Token> KvToks;
					kv->name = tokens[i].value;
					for (int j = i + 1; j < (int)tokens.size(); j++) {
						if (tokens[j].token == TokenType::OPENSCOPE) {
							scope++;
						}
						else if (tokens[j].token == TokenType::CLOSESCOPE && scope != 1) {
							scope--;
						}
						else if (tokens[j].token == TokenType::CLOSESCOPE && scope == 1) {
							if (i + 1 < (int)tokens.size()) {
								FirstSubkey = j + 1;
								i = j + 1;
							}
							kv->tokens = KvToks;
							kv->UseEscapeSequence(UsesEscapeSequence);
							kv->ptr = ptr;
							m_bPeer = kv;
							return kv;
						}
						KvToks.push_back({ tokens[j].token, tokens[j].value });
					}
				}
				else {
					return nullptr;
				}
			}
		}
		delete kv;
		return nullptr;
	}
	else {
		i = FirstSubkey;
		return m_bPeer;
	}
	return nullptr;
}

keyvalues* keyvalues::GetNextSubkey()
{
	if (m_bPeer != nullptr)
	{
		keyvalues* kv = new keyvalues;
		for (; i < (int)tokens.size(); i++) {
			if (tokens[i].token == TokenType::SUBKEY) {
				if (i + 2 < (int)tokens.size()) {
					int scope = 0;
					std::vector<Token> KvToks;
					kv->name = tokens[i].value;
					for (int j = i + 1; j < (int)tokens.size(); j++) {
						if (tokens[j].token == TokenType::OPENSCOPE) {
							scope++;
						}
						else if (tokens[j].token == TokenType::CLOSESCOPE && scope != 1) {
							scope--;
						}
						else if (tokens[j].token == TokenType::CLOSESCOPE && scope == 1) {
							if (i + 1 < (int)tokens.size()) {
								i = j + 1;
							}
							kv->tokens = KvToks;
							kv->UseEscapeSequence(UsesEscapeSequence);
							kv->ptr = ptr;
							return kv;
						}
						KvToks.push_back({ tokens[j].token, tokens[j].value });
					}
				}
			}
		}
		delete kv;
		return nullptr;
	}
	return nullptr;
}

keyvalues* keyvalues::GetFirstValue()
{
	if (m_bVal == nullptr)
	{
		keyvalues* kv = new keyvalues;
		bool InScope = false;
		int scope = 0;
		for (; v < (int)tokens.size(); v++) {
			if (InScope)
			{
				if (tokens[v].token == TokenType::OPENSCOPE) {
					scope++;
				}
				else if (tokens[v].token == TokenType::CLOSESCOPE && scope != 1) {
					scope++;
				}
				else if (tokens[v].token == TokenType::CLOSESCOPE && scope == 1) {
					InScope = false;
				}
			}
			else
			{
				if (tokens[v].token == TokenType::SUBKEY) {
					InScope = true;
				}
				if (tokens[v].token == TokenType::KEY) {
					kv->name = tokens[v].value;
					kv->value = tokens[v + 1].value;
					kv->ptr = ptr;
					kv->UseEscapeSequence(UsesEscapeSequence);
					
					FirstKey = v + 2;
					v = v + 2;

					m_bVal = kv;
					return kv;
				}
			}
		}
		delete kv;
		return nullptr;
		
	}
	else {
		v = FirstKey;
		return m_bVal;
	}
	return nullptr;
}

keyvalues* keyvalues::GetNextValue()
{
	keyvalues* kv = new keyvalues;
	if (m_bVal != nullptr)
	{
		bool InScope = false;
		int scope = 0;
		for (; v < (int)tokens.size(); v++) {
			if (InScope)
			{
				if (tokens[v].token == TokenType::OPENSCOPE) {
					scope++;
				}
				else if (tokens[v].token == TokenType::CLOSESCOPE && scope != 1) {
					scope++;
				}
				else if (tokens[v].token == TokenType::CLOSESCOPE && scope == 1) {
					InScope = false;
				}
			}
			else
			{
				if (tokens[v].token == TokenType::SUBKEY) {
					InScope = true;
				}
				if (tokens[v].token == TokenType::KEY) {
					kv->name = tokens[v].value;
					kv->value = tokens[v + 1].value;
					kv->ptr = ptr;
					kv->UseEscapeSequence(UsesEscapeSequence);
				
					v = v + 2;
					return kv;
				}
			}
		}
	}
	delete kv;
	return nullptr;
}

keyvalues* keyvalues::FindKey(const std::string& key)
{
	int tmpi = i, tmpv = v;
	FOR_EACH_SUBKEY(this, kv)
	{
		if (kv->GetName() == key)
		{
			this->i = tmpi;
			return kv;
		}
	}
	this->i = tmpi;
	FOR_EACH_VALUE(this, kv)
	{
		if (kv->GetName() == key)
		{
			this->v = tmpv;
			return kv;
		}
	}
	return nullptr;
}

void keyvalues::UseEscapeSequence(bool val)
{
	UsesEscapeSequence = val;
}

void keyvalues::SetPtr(void* newptr)
{
	ptr = newptr;
}

void keyvalues::SetName(const std::string& name)
{
	this->name = name;
}

void keyvalues::SetValue(const std::string& name)
{
	this->name = value;
}

void keyvalues::SetValue(const int& name)
{
	this->value = std::to_string(name);
}

void keyvalues::SetValue(const float& name)
{
	this->value = std::to_string(name);
}