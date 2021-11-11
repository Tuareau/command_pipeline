#include "generator.h"

void Generator::seed() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

double Generator::generate_register_adressing_probability() {
	double probability = 0.0;
	const int P = rand() % 3 + 1;
	switch (P) {
	case 1:
		probability = 0.9;
		break;
	case 2:
		probability = 0.8;
		break;
	case 3:
		probability = 0.6;
		break;
	default:
		throw std::logic_error("Generator::generate_adressing_probability(): probability type mismatch");
		break;
	}
	return probability;
}

double Generator::generate_first_command_type_probability() {
	double probability = 0.0;
	const int P = rand() % 3 + 1;
	switch (P) {
	case 1:
		probability = 0.9;
		break;
	case 2:
		probability = 0.7;
		break;
	case 3:
		probability = 0.5;
		break;
	default:
		throw std::logic_error("Generator::generate_command_type_probability(): probability type mismatch");
		break;
	}
	return probability;
}

Command::Type Generator::generate_command_type() {
	double fst_cmd_prob = generate_first_command_type_probability();
	int fst_cmd_prob_per_cent = static_cast<int>(fst_cmd_prob * 100);

	int probability = rand() % 100 + 1;
	if (probability >= 100 - fst_cmd_prob_per_cent) {
		return Command::Type::FIRST;
	}
	else {
		return Command::Type::SECOND;
	}
}

OperandType Generator::generate_operand_type() {
	double register_prob = generate_register_adressing_probability();
	int register_prob_per_cent = static_cast<int>(register_prob * 100);

	int probability = rand() % 100 + 1;
	if (probability >= 100 - register_prob_per_cent) {
		return OperandType::REGISTER;
	}
	else {
		return OperandType::MEMORY;
	}
}

ClockCycles Generator::generate_clc(const Command & cmd, Pipeline::Stage stage) {
	ClockCycles clc = 0;
	switch (stage) {
	case Pipeline::Stage::DECODE:
		clc = 1;
		break;
	case Pipeline::Stage::FETCH_LEFT_OPERAND:
		clc = Generator::generate_memory_access_clc(cmd.left_operand_type());
		break;
	case Pipeline::Stage::FETCH_RIGHT_OPERAND:
		clc = Generator::generate_memory_access_clc(cmd.right_operand_type());
		break;
	case Pipeline::Stage::EXECUTE:
		clc = Generator::generate_execution_clc(cmd.type());
		break;
	case Pipeline::Stage::WRITE_BACK:
		clc = Generator::generate_memory_access_clc(cmd.right_operand_type());
		break;
	default:
		throw std::logic_error("Pipeline::stage_to_index(): stage type mismatch");
		break;
	}
	return clc;
}

ClockCycles Generator::generate_memory_access_clc(const OperandType op_type) {
	if (op_type == OperandType::REGISTER) {
		return ClockCycles(1);
	}
	else {
		ClockCycles clc(1);
		auto probability = generate_register_adressing_probability();
		if (probability >= 0.6) {
			clc = 10;
		}
		if (probability >= 0.8) {
			clc = 5;
		}
		if (probability >= 0.9) {
			clc = 2;
		}
		return clc;
	}
}

ClockCycles Generator::generate_execution_clc(const Command::Type cmd_type) {
	if (cmd_type == Command::Type::FIRST) {
		return ClockCycles(1);
	}
	else {
		ClockCycles clc(1);
		auto probability = generate_first_command_type_probability();
		if (probability >= 0.5) {
			clc = 16;
		}
		if (probability >= 0.7) {
			clc = 8;
		}
		if (probability >= 0.9) {
			clc = 4;
		}
		return clc;
	}
}
