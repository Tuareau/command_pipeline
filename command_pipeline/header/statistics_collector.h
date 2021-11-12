#pragma once

#ifndef _STATS_COLLECTOR_H_
#define _STATS_COLLECTOR_H_

#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

#include "pipeline.h"
#include "command.h"

using ClockCycles = std::time_t;
class ExecutingCommand;

class StatisticsCollector
{
private:
	size_t commands_count;
	ClockCycles clc;
	ClockCycles total_clc;

	void print_command_type(const Command & cmd) const;
	void print_operand_type(const OperandType) const;
	void print_stage(Pipeline::Stage stage) const;

public:
	explicit StatisticsCollector(size_t commands_count);

	void print_commands(const std::vector<Command> & commands) const;
	void print_clc_state(const std::map<size_t, ExecutingCommand> & executing_commands) const;
	void print_statistics() const;

	void increase_clock_cycles();
	void add_total_clock_cycles(ClockCycles clc);

};

#endif
