#include "generator.h"

Generator::Generator() {
	std::srand(std::time(nullptr));
}

double Generator::generate_register_adressing_probability() const {
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

double Generator::generate_first_command_type_probability() const {
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

Command::Type Generator::generate_command_type() const {
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

OperandType Generator::generate_operand_type() const {
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
