#ifndef _TOKENS_H
#define _TOKENS_H

#include <string>

#pragma once

enum TokenType {
	STRING,
	KEY,
	VALUE,
	SUBKEY,
	OPENSCOPE,
	CLOSESCOPE,
};

struct Token
{
	TokenType token;
	std::string value;
};

#endif