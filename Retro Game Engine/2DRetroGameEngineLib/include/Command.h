///////////////////////////////////////////////////////////////////////////
// File:           Command.h
// Author:         Jack Kellett
// Date Created:   23/04/2021
// Brief:          This file contains the virtual class for input commands.
///////////////////////////////////////////////////////////////////////////
#ifndef _COMMAND_H_
#define _COMMAND_H_

class Command
{
public:
	virtual ~Command(){}
	virtual void Execute() = 0;
};

#endif // !_COMMAND_H_
