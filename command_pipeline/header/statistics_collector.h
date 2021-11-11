#pragma once

#ifndef _STATS_COLLECTOR_H_
#define _STATS_COLLECTOR_H_

#include <iostream>
#include <iomanip>
#include <vector>

#include "command.h"

class StatisticsCollector
{
private:
	void print_command_type(const Command & cmd) const;
	void print_operand_type(const OperandType) const;

public:
	void print_commands(std::vector<Command> & commands) const;

};

#endif
