/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 03:24:12 by bbellavi          #+#    #+#             */
/*   Updated: 2020/09/20 23:32:14 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "interpreter.h"

Token_t		get_next_token(Interpreter_t *inter)
{
	const size_t	len = strlen(inter->input);
	char			current_char;
	Token_t			tok;

	if (inter->index > len - 1)
		return ((Token_t){_EOF, 0});


	// skip whitespaces
	while (isspace(inter->input[inter->index]) && inter->index < len - 1)
		inter->index++;

	current_char = inter->input[inter->index];
	
	if (isdigit(current_char))
	{
		tok = (Token_t){INT, atoi(&inter->input[inter->index])};
		// skip digits so we don't evaluate next digit if number has multi digits
		while (isdigit(inter->input[inter->index]) && inter->index < len - 1)
			inter->index++;
		return (tok);
	}
	else if (current_char == '+')
		tok = (Token_t){OP, '+'};
	else
		tok = (Token_t){ERR, 0};
	
	inter->index++;

	return (tok);
}

int		eat(Interpreter_t *inter, int token_type)
{
	if (token_type == inter->token.type)
		inter->token = get_next_token(inter);
	else
		return (INTER_ERR_PARSING_INPUT);
	return (0);
}

int		eval(char *input)
{
	Interpreter_t	inter = (Interpreter_t){.index = 0, .input = input};
	Token_t			lval;
	Token_t			rval;
	char			op;

	inter.token = get_next_token(&inter);
	lval = inter.token;
	if (eat(&inter, INT) != 0)
		return (0);
	
	op = inter.token.value;
	if (eat(&inter, OP) != 0)
		return (0);
	
	rval = inter.token;
	if (eat(&inter, INT) != 0)
		return (0);
	
	return (lval.value + rval.value);
}

int		main(int argc, char **argv)
{
	if (argc > 1)
	{
		int result = eval(argv[1]);
		
		printf("> %i\n", result);
	}
	return (0);
}