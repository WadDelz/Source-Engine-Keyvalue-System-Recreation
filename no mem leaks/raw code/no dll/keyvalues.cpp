#include "keyvalues.h"

unsigned long long atoull(const char* str) {
	if (str == nullptr)
		return 0;

	unsigned long long result = 0;

	while (isdigit(*str)) {
		result = result * 10 + (*str - '0');
		++str;
	}

	return result;
}

bool IsFloat(const std::string& str)
{
	int dot = 0;
	bool did = false;
	for (int i = 0; i < (int)str.length(); i++) {
		did = true;
		if (str[i] == '.')
		{
			dot++;
			if (dot > 1)
				return false;
		}
		else {
			if (!isdigit(str[i]))
				return false;
		}
	}

	if (dot != 1)
		return false;

	return did;
}

bool IsInt(const std::string& str) {

	bool did = false;
	for (int i = 0; i < (int)str.length(); i++) {
		did = true;
		if (!isdigit(str[i])) {
			return false;
		}
	}

	if (!did)
		return false;

	if (atoull(str.c_str()) == 0 || atoull(str.c_str()) == 1)
		return false;

	if (atoull(str.c_str()) > INT_MAX)
		return false;
	else
		return true;
}

bool IsUIint(const std::string& str) {

	bool did = false;
	for (int i = 0; i < (int)str.length(); i++) {
		did = true;
		if (!isdigit(str[i])) {
			return false;
		}
	}

	if (!did)
		return false;

	if (atoull(str.c_str()) == 0 || atoull(str.c_str()) == 1)
		return false;

	if (atoull(str.c_str()) > INT_MAX && atoull(str.c_str()) <= UINT_MAX)
		return true;
	else
		return false;
}

bool IsUInt64(const std::string& str) {

	bool did = false;
	for (int i = 0; i < (int)str.length(); i++) {
		did = true;
		if (!isdigit(str[i])) {
			return false;
		}
	}

	if (!did)
		return false;

	if (atoull(str.c_str()) == 0 || atoull(str.c_str()) == 1)
		return false;

	if (atoull(str.c_str()) > UINT_MAX)
		return true;
	else
		return false;
}

bool IsBool(const std::string& str)
{
	bool did = false;
	for (int i = 0; i < (int)str.length(); i++) {
		did = true;
		if (!isdigit(str[i])) {
			return false;
		}
	}

	if (did)
	{
		if (atoi(str.c_str()) == 0)
			return true;
		else if (atoi(str.c_str()) == 1)
			return true;
	}

	return false;
}

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

keyvalues::keyvalues()
{
	Name = "";
	Value = "";
	NameType = TYPE_NONE;
	ValueType = TYPE_NONE;
	IVal = 0;
	IName = 0;
	tree.kvs = {};
	IsSubKey = true;
}

keyvalues::keyvalues(const std::string& name)
{
	this->IsSubKey = true;
	this->Value = "";
	this->ValueType = TYPE_NONE;
	this->IVal = 0;
	this->tree.kvs = {};

	bool DidPrev = false;
	if (IsInt(name))
	{
		this->NameType = TYPE_INT;
		this->IName = atoi(name.c_str());
		DidPrev = true;
	}
	if (!DidPrev)
	{
		if (IsUIint(name))
		{
			this->NameType = TYPE_UINT;
			this->UIName = (unsigned int)atoll(name.c_str());
			DidPrev = true;
		}
	}
	if (!DidPrev)
	{
		if (IsUInt64(name))
		{
			this->NameType = TYPE_UINT64;
			this->UI64Name = atoull(name.c_str());
			DidPrev = true;
		}
	}
	if (!DidPrev)
	{
		if (IsFloat(name))
		{
			this->NameType = TYPE_FLOAT;
			this->FName = (float)atof(name.c_str());
			DidPrev = true;
		}
	}
	if (!DidPrev)
	{
		if (IsBool(name))
		{
			this->NameType = TYPE_BOOL;
			this->BName = (atoi(name.c_str()) == 0) ? false : true;
			DidPrev = true;
		}
	}
	if (!DidPrev)
	{
		this->IName = 0;
		this->NameType = TYPE_STRING;
		this->Name = name;
	}
}

keyvalues::keyvalues(const std::string& name, const std::string& value)
{
	this->IsSubKey = false;
	this->tree.kvs = {};

	bool DidPrev = false;
	if (IsInt(name))
	{
		this->NameType = TYPE_INT;
		this->IName = atoi(name.c_str());
		DidPrev = true;
	}
	if (!DidPrev)
	{
		if (IsUIint(name))
		{
			this->NameType = TYPE_UINT;
			this->UIName = (unsigned int)atoll(name.c_str());
			DidPrev = true;
		}
	}
	if (!DidPrev)
	{
		if (IsUInt64(name))
		{
			this->NameType = TYPE_UINT64;
			this->UI64Name = atoull(name.c_str());
			DidPrev = true;
		}
	}
	if (!DidPrev)
	{
		if (IsFloat(name))
		{
			this->NameType = TYPE_FLOAT;
			this->FName = (float)atof(name.c_str());
			DidPrev = true;
		}
	}
	if (!DidPrev)
	{
		if (IsBool(name))
		{
			this->NameType = TYPE_BOOL;
			this->BName = (atoi(name.c_str()) == 0) ? false : true;
			DidPrev = true;
		}
	}
	if (!DidPrev)
	{
		this->IName = 0;
		this->NameType = TYPE_STRING;
		this->Name = name;
	}

	DidPrev = false;
	if (IsInt(value))
	{
		this->ValueType = TYPE_INT;
		this->IVal = atoi(value.c_str());
		DidPrev = true;
	}
	if (!DidPrev)
	{
		if (IsUIint(value))
		{
			this->ValueType = TYPE_UINT;
			this->UIVal = (unsigned int)atoll(value.c_str());
			DidPrev = true;
		}
	}
	if (!DidPrev)
	{
		if (IsUInt64(value))
		{
			this->ValueType = TYPE_UINT64;
			this->UI64Val = atoull(value.c_str());
			DidPrev = true;
		}
	}
	if (!DidPrev)
	{
		if (IsFloat(value))
		{
			this->ValueType = TYPE_FLOAT;
			this->FVal = (float)atof(value.c_str());
			DidPrev = true;
		}
	}
	if (!DidPrev)
	{
		if (IsBool(value))
		{
			this->ValueType = TYPE_BOOL;
			this->BVal = (atoi(value.c_str()) == 0) ? false : true;
			DidPrev = true;
		}
	}
	if (!DidPrev)
	{
		this->IVal = 0;
		this->ValueType = TYPE_STRING;
		this->Value = value;
	}
}

bool keyvalues::OpenFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
		return false;

	std::vector<Token> tokens = GetTokens(filename);

	if (tokens.size() == 0)
		return false;

	RemoveEverything();

	GetTree(tokens);

	if (tree.kvs.size() != 0)
		return true;
	else
		return false;
}

bool keyvalues::OpenBuffer(const std::string& buffer)
{
	//3 is the smalles size the buffer can be.
	// eg k v or k{}
	if (buffer.size() < 3)
		return false;

	std::vector<Token> tokens = GetTokens(buffer, true);

	if (tokens.size() == 0)
		return false;

	for (int i = 0; i < (int)tree.kvs.size(); i++)
		tree.kvs[i]->DeleteThis();

	GetTree(tokens);

	if (tree.kvs.size() != 0)
		return true;
	else
		return false;
}

const bool keyvalues::IsEmpty() const
{
	return (tree.kvs.size() == 0) ? true : false;
}

std::vector<keyvalues::Token> keyvalues::GetTokens(const std::string& filename, bool buf)
{
	std::string buffer;
	std::vector<Token> TempTokens, Tokens;
	bool InStr = false, InNQStr = false, InComment = false;
	int NumOpen = 0, NumClose = 0;

	if (!buf)
	{
		std::string line;
		std::ifstream file(filename);
		if (!file.is_open())
			return{};

		while (std::getline(file, line))
		{
			for (int i = 0; i < (int)line.length(); i++) {
				char c = line[i];
				if (InStr || InNQStr || InComment)
				{
					if (InStr)
					{
						if (c == '"') {
							TempTokens.push_back({ TokenType::STRING, buffer });
							buffer.clear();
							InStr = false;
						}
						else
						{
							buffer.push_back(c);
						}
					}
					else if (InNQStr)
					{
						if (isspace(c) || c == '{' || c == '}' || c == '"') {
							TempTokens.push_back({ TokenType::STRING, buffer });

							if (c == '{')
							{
								TempTokens.push_back({ TokenType::OPENSCOPE, "{" });
								NumOpen++;
							}
							else if (c == '}')
							{
								TempTokens.push_back({ TokenType::CLOSESCOPE, "}" });
								NumClose++;
							}
							else if (c == '"')
								return{};

							buffer.clear();
							InNQStr = false;
						}
						else
						{
							buffer.push_back(c);
						}
					}
					else if (InComment)
					{
						if (c == '*') {
							i++;
							if (i < (int)line.length())
							{
								if (line[i] == '/')
								{
									InComment = false;
									break;
								}
							}
							else
								return{};
						}
					}
				}
				else
				{
					if (c == '"') {
						InStr = true;
					}
					else if (c == '/') {
						i++;
						if (i < (int)line.length())
						{
							if (line[i] == '/')
								break;
							else if (line[i] == '*')
								InComment = true;
							else
								return{};
						}
						else
							return{};
					}
					else if (c == '{') {
						NumOpen++;
						TempTokens.push_back({ TokenType::OPENSCOPE, "{" });
					}
					else if (c == '}') {
						NumClose++;
						TempTokens.push_back({ TokenType::CLOSESCOPE, "}" });
					}
					else if (isalnum(c)) {
						buffer.push_back(c);
						InNQStr = true;
					}
				}
			}
			if (InNQStr)
			{
				TempTokens.push_back({ TokenType::STRING, buffer });
				buffer.clear();
				InNQStr = false;
			}
		}
	}
	else
	{
		for (int i = 0; i < (int)filename.length(); i++) {
			char c = filename[i];
			if (InStr || InNQStr )
			{
				if (InStr)
				{
					if (c == '"') {
						TempTokens.push_back({ TokenType::STRING, buffer });
						buffer.clear();
						InStr = false;
					}
					else
					{
						buffer.push_back(c);
					}
				}
				else if (InNQStr)
				{
					if (isspace(c) || c == '{' || c == '}' || c == '"') {
						TempTokens.push_back({ TokenType::STRING, buffer });

						if (c == '{')
						{
							TempTokens.push_back({ TokenType::OPENSCOPE, "{" });
							NumOpen++;
						}
						else if (c == '}')
						{
							TempTokens.push_back({ TokenType::CLOSESCOPE, "}" });
							NumClose++;
						}
						else if (c == '"')
							return{};

						buffer.clear();
						InNQStr = false;
					}
					else
					{
						buffer.push_back(c);
					}
				}
				else if (InComment)
				{
					if (c == '*') {
						i++;
						if (i < (int)filename.length())
						{
							if (filename[i] == '/')
							{
								InComment = false;
								break;
							}
						}
						else
							return{};
					}
				}
			}
			else
			{
				if (c == '"') {
					InStr = true;
				}
				else if (c == '/') {
					i++;
					if (i < (int)filename.length())
					{
						if (filename[i] == '*')
							InComment = true;
						else
							return{};
					}
					else
						return{};
				}
				else if (c == '{') {
					NumOpen++;
					TempTokens.push_back({ TokenType::OPENSCOPE, "{" });
				}
				else if (c == '}') {
					NumClose++;
					TempTokens.push_back({ TokenType::CLOSESCOPE, "}" });
				}
				else if (isalnum(c)) {
					buffer.push_back(c);
					InNQStr = true;
				}
			}
		}
	}

	if (InStr)
		return{};

	if (NumClose != NumOpen)
		return{};

	if (buffer.length() != 0 && InNQStr) {
		TempTokens.push_back({ TokenType::STRING, buffer });
	}

	for (int j = 0; j < (int)TempTokens.size(); j++)
	{
		bool did = false;
		if (j + 1 < (int)TempTokens.size()) {
			if (TempTokens[j].token == TokenType::STRING && TempTokens[j + 1].token == TokenType::STRING) {
				Tokens.push_back({ TokenType::KEY, TempTokens[j].value });
				Tokens.push_back({ TokenType::VALUE, TempTokens[j + 1].value });
				j++;
				did = true;
			}
			else if (TempTokens[j].token == TokenType::STRING && TempTokens[j + 1].token == TokenType::OPENSCOPE) {
				Tokens.push_back({ TokenType::SUBKEY, TempTokens[j].value });
				Tokens.push_back({ TokenType::OPENSCOPE, "{" });
				j++;
				did = true;
			}
		}

		if (!did)
		{
			if (TempTokens[j].token == TokenType::CLOSESCOPE) {
				Tokens.push_back({ TokenType::CLOSESCOPE, "}" });
				did = true;
			}
		}

		if (!did)
			return{};
	}

	return Tokens;
}

void keyvalues::GetTree(const std::vector<Token>& Tokens)
{
	KvTree TempTree;
	int Scope = 0;
	for (int i = 0; i < (int)Tokens.size(); i++) {
		if (Tokens[i].token == TokenType::OPENSCOPE) {
			Scope++;
		}
		else if (Tokens[i].token == TokenType::CLOSESCOPE) {
			Scope--;
		}
		else if (Scope == 0 && Tokens[i].token == TokenType::KEY) {
			TempTree.kvs.push_back(GetTreeKv(Tokens, i, this));
		}
		else if (Scope == 0 && Tokens[i].token == TokenType::SUBKEY) {
			int name = i;
			int scope = 0;
			std::vector<Token> TempTokens;
			for (int j = i + 2; j < (int)Tokens.size(); j++) {
				if (Tokens[j].token == TokenType::OPENSCOPE) {
					scope++;
				}
				else if (Tokens[j].token == TokenType::CLOSESCOPE && scope != 0) {
					scope--;
				}
				else if (Tokens[j].token == TokenType::CLOSESCOPE && scope == 0) {
					i = j;
					break;
				}
				TempTokens.push_back({ Tokens[j].token, Tokens[j].value });
			}
			TempTree.kvs.push_back(GetTreeSub(TempTokens, Tokens[name].value, this));
		}
	}
	tree = TempTree;
}

keyvalues* keyvalues::GetTreeSub(const std::vector<Token>& tokens, const std::string& name, keyvalues* prev)
{
	KvTree TempTree;

	keyvalues* KV = new keyvalues(name);
	KV->UsesEscapeSequence = prev->UsesEscapeSequence;
	KV->m_bPrev = prev;
	
	int Scope = 0;
	for (int i = 0; i < (int)tokens.size(); i++) {
		if (tokens[i].token == TokenType::OPENSCOPE) {
			Scope++;
		}
		else if (tokens[i].token == TokenType::CLOSESCOPE) {
			Scope--;
		}
		else if (Scope == 0 && tokens[i].token == TokenType::SUBKEY) {
			int name = i;
			int scope = 0;
			std::vector<Token> TempTokens;
			for (int j = i + 2; j < (int)tokens.size(); j++) {
				if (tokens[j].token == TokenType::OPENSCOPE) {
					scope++;
				}
				else if (tokens[j].token == TokenType::CLOSESCOPE && scope != 0) {
					scope--;
				}
				else if (tokens[j].token == TokenType::CLOSESCOPE && scope == 0) {
					i = j;
					break;
				}
				TempTokens.push_back({ tokens[j].token, tokens[j].value });
			}
			TempTree.kvs.push_back(GetTreeSub(TempTokens, tokens[name].value, KV));
		}
		else if (Scope == 0 && tokens[i].token == TokenType::KEY) {
			TempTree.kvs.push_back(GetTreeKv(tokens, i, KV));
		}
	}

	KV->tree = TempTree;
	return KV;
}

keyvalues* keyvalues::GetTreeKv(const std::vector<Token>& Tokens, int& i, keyvalues* prev)
{
	std::string name = Tokens[i].value, value = Tokens[++i].value;
	keyvalues* KV = new keyvalues(name, value);
	KV->m_bPrev = prev;
	KV->UsesEscapeSequence = prev->UsesEscapeSequence;

	return KV;
}

const std::string keyvalues::GetName() const
{
	switch (NameType)
	{
	case TYPE_INT:
		return std::to_string(IName);
	case TYPE_UINT:
		return std::to_string(UIName);
	case TYPE_UINT64:
		return std::to_string(UI64Name);
	case TYPE_FLOAT:
		return std::to_string(FName);
	case TYPE_BOOL:
		return std::to_string(BName);
	case TYPE_STRING:
		if (UsesEscapeSequence)
			return ConvertEscapeChars(Name);
		else
			return Name;
	default:
		return "";
	}
}

const int keyvalues::GetNameAsInt() const
{
	switch (NameType)
	{
	case TYPE_INT:
		return IName;
	case TYPE_FLOAT:
		return (int)FName;
	case TYPE_BOOL:
		return BName;
	default:
		return 0;
	}
}

const unsigned int keyvalues::GetNameAsUInt() const
{
	switch (NameType)
	{
	case TYPE_INT:
		return IName;
	case TYPE_UINT:
		return UIName;
	case TYPE_FLOAT:
		return (unsigned int)FName;
	case TYPE_BOOL:
		return BName;
	default:
		return 0;
	}
}

const uint64_t keyvalues::GetNameAsUInt64() const
{
	switch (NameType)
	{
	case TYPE_INT:
		return IName;
	case TYPE_UINT:
		return UIName;
	case TYPE_UINT64:
		return UI64Name;
	case TYPE_FLOAT:
		return (uint64_t)FName;
	case TYPE_BOOL:
		return BName;
	default:
		return 0;
	}
}

const float keyvalues::GetNameAsFloat() const
{
	switch (NameType)
	{
	case TYPE_INT:
		return (float)IName;
	case TYPE_UINT:
		return (float)UIName;
	case TYPE_UINT64:
		return (float)UI64Name;
	case TYPE_FLOAT:
		return FName;
	case TYPE_BOOL:
		return (float)BName;
	default:
		return 0.0f;
	}
}

const bool keyvalues::GetNameAsBool() const
{
	switch (NameType)
	{
	case TYPE_NONE:
		return false;
	case TYPE_INT:
		return ((IName == 0) ? false : true);
	case TYPE_UINT:
		return true;
	case TYPE_UINT64:
		return true;
	case TYPE_FLOAT:
		return ((FName == 0) ? false : true);
	case TYPE_BOOL:
		return BName;
	default:
		return false;
	}
}

const bool keyvalues::IsNameEmpty() const
{
	return ((Name == ""));
}

const std::string keyvalues::GetString(const std::string& ByVal, const std::string& DefVal) const
{
	if (ByVal.length() == 0) {
		if (this->IsSubKey)
			return "";

		switch (ValueType)
		{
		case TYPE_INT:
			return std::to_string(IVal);
		case TYPE_UINT:
			return std::to_string(UIVal);
		case TYPE_UINT64:
			return std::to_string(UI64Val);
		case TYPE_FLOAT:
			return std::to_string(FVal);
		case TYPE_BOOL:
			return std::to_string(BVal);
		case TYPE_STRING:
			if (UsesEscapeSequence)
				return ConvertEscapeChars(Value);
			else
				return Value;
		default:
			return "";
		}
	}
	else {
		if (!this->IsSubKey)
			return "";

		for (int i = 0; i < (int)tree.kvs.size(); i++) {
			if (tree.kvs[i]->IsSubKey)
				continue;

			if (!tree.kvs[i]->IsSubKey && tree.kvs[i]->GetName() == ByVal) {
				switch (tree.kvs[i]->ValueType)
				{
				case TYPE_INT:
					return std::to_string(tree.kvs[i]->IVal);
				case TYPE_UINT:
					return std::to_string(tree.kvs[i]->UIVal);
				case TYPE_UINT64:
					return std::to_string(tree.kvs[i]->UI64Val);
				case TYPE_FLOAT:
					return std::to_string(tree.kvs[i]->FVal);
				case TYPE_BOOL:
					return std::to_string(tree.kvs[i]->BVal);
				case TYPE_STRING:
					if (UsesEscapeSequence)
						return ConvertEscapeChars(tree.kvs[i]->Value);
					else
						return tree.kvs[i]->Value;
				default:
					return "";
				}
			}
		}
		return DefVal;
	}
	return "";
}

const int keyvalues::GetInt(const std::string& ByVal, const int& DefVal) const
{
	if (ByVal.length() == 0) {
		if (this->IsSubKey)
			return 0;

		switch (ValueType)
		{
		case TYPE_INT:
			return IVal;
		case TYPE_FLOAT:
			return (int)FVal;
		case TYPE_BOOL:
			return (int)BVal;
		default:
			return 0;
		}
	}
	else {
		if (!this->IsSubKey)
			return 0;

		for (int i = 0; i < (int)tree.kvs.size(); i++) {
			if (tree.kvs[i]->IsSubKey)
				continue;

			if (!tree.kvs[i]->IsSubKey && tree.kvs[i]->GetName() == ByVal) {
				switch (tree.kvs[i]->ValueType)
				{
				case TYPE_INT:
					return tree.kvs[i]->IVal;
				case TYPE_FLOAT:
					return (int)tree.kvs[i]->FVal;
				case TYPE_BOOL:
					return tree.kvs[i]->BVal;
				default:
					return 0;
				}
			}
		}
		return DefVal;
	}
}

const unsigned int keyvalues::GetUInt(const std::string& ByVal, const unsigned int& DefVal) const
{
	if (ByVal.length() == 0) {
		if (this->IsSubKey)
			return 0;

		switch (ValueType)
		{
		case TYPE_INT:
			return IVal;
		case TYPE_UINT:
			return UIVal;
		case TYPE_FLOAT:
			return (unsigned int)FVal;
		case TYPE_BOOL:
			return BVal;
		default:
			return 0;
		}
	}
	else {
		if (!this->IsSubKey)
			return 0;

		for (int i = 0; i < (int)tree.kvs.size(); i++) {
			if (tree.kvs[i]->IsSubKey)
				continue;

			if (!tree.kvs[i]->IsSubKey && tree.kvs[i]->GetName() == ByVal) {
				switch (tree.kvs[i]->ValueType)
				{
				case TYPE_INT:
					return tree.kvs[i]->IVal;
				case TYPE_UINT:
					return tree.kvs[i]->UIVal;
				case TYPE_FLOAT:
					return (unsigned int)tree.kvs[i]->FVal;
				case TYPE_BOOL:
					return (unsigned int)tree.kvs[i]->BVal;
				default:
					return 0;
				}
			}
		}
		return DefVal;
	}
}

const uint64_t keyvalues::GetUInt64(const std::string& ByVal, const uint64_t& DefVal) const
{
	if (ByVal.length() == 0) {
		if (this->IsSubKey)
			return 0;

		switch (ValueType)
		{
		case TYPE_INT:
			return IVal;
		case TYPE_UINT:
			return UIVal;
		case TYPE_UINT64:
			return UI64Val;
		case TYPE_FLOAT:
			return (uint64_t)FVal;
		case TYPE_BOOL:
			return BVal;
		default:
			return 0;
		}
	}
	else {
		if (!this->IsSubKey)
			return 0;

		for (int i = 0; i < (int)tree.kvs.size(); i++) {
			if (tree.kvs[i]->IsSubKey)
				continue;

			if (!tree.kvs[i]->IsSubKey && tree.kvs[i]->GetName() == ByVal) {
				switch (tree.kvs[i]->ValueType)
				{
				case TYPE_INT:
					return tree.kvs[i]->IVal;
				case TYPE_UINT:
					return tree.kvs[i]->UIVal;
				case TYPE_UINT64:
					return tree.kvs[i]->UI64Val;
				case TYPE_FLOAT:
					return (uint64_t)tree.kvs[i]->FVal;
				case TYPE_BOOL:
					return tree.kvs[i]->BVal;
				default:
					return 0;
				}
			}
		}
		return DefVal;
	}
}

const float keyvalues::GetFloat(const std::string& ByVal, const float& DefVal) const
{
	if (ByVal.length() == 0) {
		if (this->IsSubKey)
			return 0.0f;

		switch (ValueType)
		{
		case TYPE_INT:
			return (float)IVal;
		case TYPE_UINT:
			return (float)UIVal;
		case TYPE_UINT64:
			return (float)UI64Val;
		case TYPE_FLOAT:
			return FVal;
		case TYPE_BOOL:
			return (float)BVal;
		default:
			return 0.0f;
		}
	}
	else {
		if (!this->IsSubKey)
			return 0.0f;

		for (int i = 0; i < (int)tree.kvs.size(); i++) {
			if (tree.kvs[i]->IsSubKey)
				continue;

			if (!tree.kvs[i]->IsSubKey && tree.kvs[i]->GetName() == ByVal) {
				switch (tree.kvs[i]->ValueType)
				{
				case TYPE_INT:
					return (float)tree.kvs[i]->IVal;
				case TYPE_UINT:
					return (float)tree.kvs[i]->UIVal;
				case TYPE_UINT64:
					return (float)tree.kvs[i]->UI64Val;
				case TYPE_FLOAT:
					return tree.kvs[i]->FVal;
				case TYPE_BOOL:
					return (float)tree.kvs[i]->BVal;
				default:
					return 0.0f;
				}
			}
		}
		return DefVal;
	}
}

const bool keyvalues::GetBool(const std::string& ByVal, const bool& DefVal) const
{
	if (ByVal.length() == 0) {
		if (this->IsSubKey)
			return false;

		switch (ValueType)
		{
		case TYPE_INT:
			return true;
		case TYPE_UINT:
			return true;
		case TYPE_UINT64:
			return true;
		case TYPE_FLOAT:
			return ((FVal == 0) ? false : true);
		case TYPE_BOOL:
			return BVal;
		default:
			return false;
		}
	}
	else {
		if (!this->IsSubKey)
			return false;

		for (int i = 0; i < (int)tree.kvs.size(); i++) {
			if (tree.kvs[i]->IsSubKey)
				continue;

			if (!tree.kvs[i]->IsSubKey && tree.kvs[i]->GetName() == ByVal) {
				switch (tree.kvs[i]->ValueType)
				{
				case TYPE_INT:
					return true;
				case TYPE_UINT:
					return true;
				case TYPE_UINT64:
					return true;
				case TYPE_FLOAT:
					return ((tree.kvs[i]->FVal == 0) ? false : true);
				case TYPE_BOOL:
					return tree.kvs[i]->BVal;
				default:
					return false;
				}
			}
		}
		return DefVal;
	}
}

const bool keyvalues::IsStringEmpty(const std::string& KeyName) const
{
	if (KeyName == "") {
		if (!this->IsSubKey)
			return ((GetString() == ""));
		else
			return true;
	}

	if (!this->IsSubKey)
		return true;

	for (int i = 0; i < (int)tree.kvs.size(); i++)
	{
		if (tree.kvs[i]->IsSubKey)
			continue;

		if (tree.kvs[i]->Name == KeyName)
			return ((tree.kvs[i]->GetString() == ""));
	}

	return true;
}


const keyvalues::KVTypes_T keyvalues::GetNameType() const
{
	return NameType;
}

const keyvalues::KVTypes_T keyvalues::GetValueType() const
{
	return ValueType;
}

const bool keyvalues::IsSubkey() const
{
	return IsSubKey;
}

void keyvalues::SetName(const std::string& name)
{
	NameType = TYPE_STRING;
	Name = name;
}

void keyvalues::SetNameToInt(const int& name)
{
	NameType = TYPE_INT;
	IName = name;
}

void keyvalues::SetNameToUInt(const unsigned int& name)
{
	NameType = TYPE_UINT;
	UIName = name;
}

void keyvalues::SetNameToUInt64(const uint64_t& name)
{
	NameType = TYPE_UINT64;
	UI64Name = name;
}

void keyvalues::SetNameToFloat(const float& name)
{
	NameType = TYPE_FLOAT;
	FName = name;
}

void keyvalues::SetNameToBool(const bool& name)
{
	NameType = TYPE_BOOL;
	BName = name;
}

void keyvalues::SetString(const std::string& val)
{
	if (this->IsSubKey)
		return;

	ValueType = TYPE_STRING;
	Value = val;
}

void keyvalues::SetInt(const int& val)
{
	if (this->IsSubKey)
		return;

	ValueType = TYPE_INT;
	IVal = val;
}

void keyvalues::SetUInt(const unsigned int& val)
{
	if (this->IsSubKey)
		return;

	ValueType = TYPE_UINT;
	UIVal = val;
}

void keyvalues::SetUInt64(const uint64_t& val)
{
	if (this->IsSubKey)
		return;

	ValueType = TYPE_UINT64;
	UI64Val = val;
}

void keyvalues::SetFloat(const float& val)
{
	if (this->IsSubKey)
		return;

	ValueType = TYPE_FLOAT;
	FVal = val;
}

void keyvalues::SetBool(const bool& val)
{
	if (this->IsSubKey)
		return;

	ValueType = TYPE_BOOL;
	BVal = val;
}

void keyvalues::UseEscapeSequence(const bool& val)
{
	UsesEscapeSequence = val;
}

void keyvalues::AddKeyvalues(keyvalues* m_Sub)
{
	if (!this->IsSubKey)
		return;

	m_Sub->m_bPrev = this;
	m_Sub->UsesEscapeSequence = this->UsesEscapeSequence;
	tree.kvs.push_back(m_Sub);
}

void keyvalues::RemoveKeyvalues(keyvalues* m_Sub)
{
	if (!this->IsSubKey)
		return;

	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		if (tree.kvs[i] == m_Sub) {
			tree.kvs[i]->DeleteThis();
		}
	}
}

void keyvalues::RemoveKeyvalues()
{
	if (!this->IsSubKey)
		return;

	tree.kvs.clear();
}

void keyvalues::RemoveSubkeys()
{
	if (!this->IsSubKey)
		return;

	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		if (tree.kvs[i]->IsSubKey)
		{
			tree.kvs.erase(tree.kvs.begin() + i);
		}
	}
}

void keyvalues::RemoveKVPairs()
{
	if (!this->IsSubKey)
		return;

	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		if (!tree.kvs[i]->IsSubKey)
		{
			tree.kvs.erase(tree.kvs.begin() + i);
		}
	}
}

void keyvalues::DeleteSubkeys()
{
	if (!this->IsSubKey)
		return;

	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		if (tree.kvs[i]->IsSubKey) {
			tree.kvs[i]->DeleteThis();
		}
	}
}

void keyvalues::DeleteKVPairs()
{
	if (!this->IsSubKey)
		return;

	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		if (!tree.kvs[i]->IsSubKey) {
			tree.kvs[i]->DeleteThis();
		}
	}
}

void keyvalues::DeleteKeyvalues()
{
	if (!this->IsSubKey)
		return;

	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		tree.kvs[i]->DeleteThis();
	}
}

void keyvalues::SetIsSubkey(const bool& is)
{
	IsSubKey = is;
}

keyvalues* keyvalues::GetFirstSubkey()
{
	if (!this->IsSubKey)
		return nullptr;

	Subkey = 0;
	for (; Subkey < (int)tree.kvs.size(); Subkey++) {
		if (tree.kvs[Subkey]->IsSubKey) {
			return tree.kvs[Subkey];
		}
	}
	return nullptr;
}

keyvalues* keyvalues::GetNextSubkey()
{
	if (!this->IsSubKey)
		return nullptr;

	Subkey++;
	for (; Subkey < (int)tree.kvs.size(); Subkey++) {
		if (tree.kvs[Subkey]->IsSubKey) {
			return tree.kvs[Subkey];
		}
	}
	return nullptr;
}

keyvalues* keyvalues::GetLastSubkey()
{
	if (!this->IsSubKey)
		return nullptr;

	keyvalues* ret = nullptr;
	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		if (tree.kvs[i]->IsSubKey)
			ret = tree.kvs[i];
	}
	return ret;
}

keyvalues* keyvalues::GetFirstValue()
{
	if (!this->IsSubKey)
		return nullptr;

	KVPair = 0;
	for (; KVPair < (int)tree.kvs.size(); KVPair++) {
		if (!tree.kvs[KVPair]->IsSubKey) {
			return tree.kvs[KVPair];
		}
	}
	return nullptr;
}

keyvalues* keyvalues::GetNextValue()
{
	if (!this->IsSubKey)
		return nullptr;

	KVPair++;
	for (; KVPair < (int)tree.kvs.size(); KVPair++) {
		if (!tree.kvs[KVPair]->IsSubKey) {
			return tree.kvs[KVPair];
		}
	}
	return nullptr;
}

keyvalues* keyvalues::GetLastValue()
{
	if (!this->IsSubKey)
		return nullptr;

	keyvalues* ret = nullptr;
	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		if (!tree.kvs[i]->IsSubKey)
			ret = tree.kvs[i];
	}
	return ret;
}

keyvalues* keyvalues::GetFirstKeyvalue()
{
	if (!this->IsSubKey)
		return nullptr;

	kv = 0;
	if (kv < (int)tree.kvs.size())
	{
		return tree.kvs[0];
	}
	return nullptr;
}

keyvalues* keyvalues::GetNextKeyvalue()
{
	if (!this->IsSubKey)
		return nullptr;

	kv++;
	if (kv < (int)tree.kvs.size())
	{
		return tree.kvs[kv];
	}
	return nullptr;
}

keyvalues* keyvalues::GetLastKeyvalue()
{
	if (!this->IsSubKey)
		return nullptr;

	return (tree.kvs.size() != 0) ? tree.kvs[tree.kvs.size() - 1] : nullptr;
}

keyvalues* keyvalues::GetParent()
{
	return (m_bPrev) ? m_bPrev : nullptr;
}

keyvalues* keyvalues::FindKey(const std::string& name)
{
	if (!this->IsSubKey)
		return nullptr;

	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		if (tree.kvs[i]->GetName() == name) {
			return tree.kvs[i];
		}
	}
	return nullptr;
}

keyvalues* keyvalues::FindKeyRecursive(const std::string& name)
{
	if (!this->IsSubKey)
		return nullptr;

	if (this->Name == name)
		return this;

	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		keyvalues* kv = tree.kvs[i]->FindKeyRecursive(name);
		if (kv != nullptr)
			return kv;
	}

	return nullptr;
}

keyvalues* keyvalues::FindSubKey(const std::string& name, bool bCreate)
{
	if (!this->IsSubKey)
		return nullptr;

	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		if (tree.kvs[i]->GetName() == name && tree.kvs[i]->IsSubKey) {
			return tree.kvs[i];
		}
	}

	if (bCreate)
	{
		keyvalues* kv = new keyvalues(name);
		this->AddKeyvalues(kv);

		return kv;
	}

	return nullptr;
}

keyvalues* keyvalues::FindSubKeyRecursive(const std::string& name)
{
	if (!this->IsSubKey)
		return nullptr;

	if (this->Name == name && this->IsSubKey)
		return this;

	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		keyvalues* kv = tree.kvs[i]->FindKeyRecursive(name);
		if (kv != nullptr)
			return kv;
	}

	return nullptr;
}

keyvalues* keyvalues::FindKVPair(const std::string& name, bool bCreate)
{
	if (!this->IsSubKey)
		return nullptr;

	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		if (tree.kvs[i]->GetName() == name && !tree.kvs[i]->IsSubKey) {
			return tree.kvs[i];
		}
	}

	if (bCreate)
	{
		keyvalues* kv = new keyvalues(name, "");
		this->AddKeyvalues(kv);

		return kv;
	}

	return nullptr;
}

keyvalues* keyvalues::FindKVPairRecursive(const std::string& name)
{
	if (!this->IsSubKey)
		return nullptr;

	if (this->Name == name && !this->IsSubKey)
		return this;

	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		keyvalues* kv = tree.kvs[i]->FindKeyRecursive(name);
		if (kv != nullptr)
			return kv;
	}

	return nullptr;
}

void keyvalues::DeleteThis()
{
	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		if (tree.kvs[i] != nullptr) {
			tree.kvs[i]->DeleteThis();
		}
	}
	if (m_bPrev)
	{
		for (int i = 0; i < (int)m_bPrev->tree.kvs.size(); i++) {
			if (m_bPrev->tree.kvs[i] == this) {
				m_bPrev->tree.kvs.erase(m_bPrev->tree.kvs.begin() + i);
				break;
			}
		}
	}
	delete this;
}

void keyvalues::RemoveEverything()
{
	m_bPrev = nullptr;

	NameType = TYPE_NONE;
	ValueType = TYPE_NONE;

	Subkey = 0;
	KVPair = 0;
	kv = 0;

	IsSubKey = true;
	UsesEscapeSequence = false;

	Name = "";
	Value = "";

	IName = 0;
	IVal = 0;

	if (KEYVALUES_DELETE_ON_OPEN_NEW_FILE)
		DeleteKeyvalues();
	else
		RemoveKeyvalues();
}

void keyvalues::WriteSubkey(std::ofstream& file, keyvalues* kv, int& scope)
{
	for (int i = 0; i < scope; i++) {
		file << '\t';
	}
	file << '"' << kv->GetName() << '"' << '\n';
	for (int i = 0; i < scope; i++) {
		file << '\t';
	}
	file << "{\n";
	scope++;

	for (int i = 0; i < (int)kv->tree.kvs.size(); i++) {
		if (kv->tree.kvs[i]->IsSubKey)
		{
			WriteSubkey(file, kv->tree.kvs[i], scope);
		}
		else
		{
			WriteKVPair(file, kv->tree.kvs[i], scope);
		}
	}
	scope--;
	for (int i = 0; i < scope; i++) {
		file << '\t';
	}
	file << "}\n";
}

void keyvalues::WriteKVPair(std::ofstream& file, keyvalues* kv, int& scope)
{
	for (int i = 0; i < scope; i++) {
		file << '\t';
	}
	file << '"' << kv->GetName() << '"' << ' ' << '"' << kv->GetString() << '"' << '\n';
}

void keyvalues::WriteToFile(const std::string& filename)
{
	std::ofstream file(filename);
	if (!file.is_open())
		return;

	int scope = 0;

	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		if (tree.kvs[i]->IsSubKey)
		{
			WriteSubkey(file, tree.kvs[i], scope);
		}
		else
		{
			WriteKVPair(file, tree.kvs[i], scope);
		}
	}
}

void keyvalues::WriteSubkey(std::ostringstream& file, keyvalues* kv, int& scope)
{
	for (int i = 0; i < scope; i++) {
		file << '\t';
	}
	file << '"' << kv->GetName() << '"' << '\n';
	for (int i = 0; i < scope; i++) {
		file << '\t';
	}
	file << "{\n";
	scope++;

	for (int i = 0; i < (int)kv->tree.kvs.size(); i++) {
		if (kv->tree.kvs[i]->IsSubKey)
		{
			WriteSubkey(file, kv->tree.kvs[i], scope);
		}
		else
		{
			WriteKVPair(file, kv->tree.kvs[i], scope);
		}
	}
	scope--;
	for (int i = 0; i < scope; i++) {
		file << '\t';
	}
	file << "}\n";
}

void keyvalues::WriteKVPair(std::ostringstream& file, keyvalues* kv, int& scope)
{
	for (int i = 0; i < scope; i++) {
		file << '\t';
	}
	file << '"' << kv->GetName() << '"' << ' ' << '"' << kv->GetString() << '"' << '\n';
}

std::string keyvalues::WriteToString()
{
	std::string str;
	std::ostringstream file(str);

	int scope = 0;

	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		if (tree.kvs[i]->IsSubKey)
		{
			WriteSubkey(file, tree.kvs[i], scope);
		}
		else
		{
			WriteKVPair(file, tree.kvs[i], scope);
		}
	}
	str = file.str();
	return str;
}

const int keyvalues::GetNumSubkeys() const
{
	if (!this->IsSubKey)
		return 0;

	int num = 0;

	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		if (tree.kvs[i]->IsSubKey)
			num++;
	}

	return num;
}

const int keyvalues::GetNumKVPairs() const
{
	if (!this->IsSubKey)
		return 0;

	int num = 0;

	for (int i = 0; i < (int)tree.kvs.size(); i++) {
		if (!tree.kvs[i]->IsSubKey)
			num++;
	}

	return num;
}

const int keyvalues::GetNumKeyvalues() const
{
	if (!this->IsSubKey)
		return 0;

	return tree.kvs.size();
}