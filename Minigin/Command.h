#pragma once
#include <iostream>
class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
	
};

class JumpCommand: public Command
{
public:
	void Execute() override { std::cout << "Jump\n"; };
};

class FireCommand : public Command
{
public:
	void Execute() override { std::cout << "Fire\n"; };
};


class DuckCommand : public Command
{
public:
	void Execute() override { std::cout << "Duck\n"; };
};

class FartCommand : public Command
{
public:
	void Execute() override { std::cout << "Fart\n"; };
};

