/*
	Onion HTTP server library
	Copyright (C) 2010-2014 David Moreno Montero and othes

	This library is free software; you can redistribute it and/or
	modify it under the terms of, at your choice:
	
	a. the Apache License Version 2.0. 
	
	b. the GNU General Public License as published by the 
		Free Software Foundation; either version 2.0 of the License, 
		or (at your option) any later version.
	 
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of both libraries, if not see 
	<http://www.gnu.org/licenses/> and 
	<http://www.apache.org/licenses/LICENSE-2.0>.
	*/

#include "parser_block.h"
#include <string.h>

char *onion_parser_block_get_token(onion_parser_block *bl, char delimiter){
	if (onion_parser_block_eof(bl))
		return NULL;
	char *token=bl->p;
	for(;bl->p < bl->end; bl->p++){
		if (*bl->p==delimiter)
			break;
	}
	if (bl->p < bl->end)
		*bl->p=0;
	bl->p++;
	return token;
}
char *onion_parser_block_get_token2(onion_parser_block *bl, char *delimiter, char *rc){
	if (onion_parser_block_eof(bl))
		return NULL;
	char *token=bl->p;
	char c=*bl->p;
	while(c!=delimiter[0] && c!=delimiter[1] && !onion_parser_block_eof(bl)){
		bl->p++;
		c=*bl->p;
	}
	if (rc)
		*rc=c;
	*bl->p=0;
	bl->p++;
	return token;
}

char *onion_parser_block_get_to_nl(onion_parser_block *bl){
	char *r=onion_parser_block_get_token(bl, '\n');

	if (r && ( (bl->p-r) > 1) && bl->p[-2]=='\r') // remove \r if there is something that has data, and last char is \r.
		bl->p[-2]='\0';

	return r;
}

char *onion_str_get_token(char **str, char delimiter){
	char *s=*str;
	if (!*s)
		return NULL;
	char *token=s;
	while(*s!=delimiter && *s){
		s++;
	}
	if (*s){
		*s=0;
		*str=s+1;
	}
	else 
		*str=s;
	return token;
}
char *onion_str_get_token2(char **str, char *delimiter, char *rc){
	char *s=*str;
	if (!*s)
		return NULL;
	char *token=s;
	char c=*s;
	while(c!=delimiter[0] && c!=delimiter[1] && *s){
		s++;
		c=*s;
	}
	if (rc)
		*rc=*s;
	if (*s){
		*s=0;
		*str=s+1;
	}
	else 
		*str=s;
	if (rc)
		*rc=c;
	return token;
}

char *onion_str_strip(char *s){
	if (!s)
		return s;
	while (*s && isspace(*s))
		s++;
	char *r=s;
	
	return r;
}
char* onion_str_unquote(char* str)
{
	if (*str=='"'){
		str++;
		str[strlen(str)-1]='\0';
	}
	return str;
}
