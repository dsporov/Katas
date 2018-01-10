#include "stdafx.h"

#include <string>

class Fighter
{
private:
	std::string name;

	int health;

	int damagePerAttack;

public:
	Fighter(std::string name, int health, int damagePerAttack)
	{
		this->name = name;
		this->health = health;
		this->damagePerAttack = damagePerAttack;
	}

	~Fighter() { };

	std::string getName()
	{
		return name;
	}

	int getHealth()
	{
		return health;
	}

	int getDamagePerAttack()
	{
		return damagePerAttack;
	}

	void setHealth(int value)
	{
		health = value;
	}
};

std::string declareWinner(Fighter* fighter1, Fighter* fighter2, std::string firstAttacker) {
	int h1 = fighter1->getHealth();
	int h2 = fighter2->getHealth();

	int d1 = fighter1->getDamagePerAttack();
	int d2 = fighter2->getDamagePerAttack();

	int n1 = h1 / d2 + (h1 % d2 != 0);
	int n2 = h2 / d1 + (h2 % d1 != 0);

	if (n1 > n2)
		return fighter1->getName();
	if (n2 > n1)
		return fighter2->getName();
	return firstAttacker;
	/*
	if (fighter2->getName() == firstAttacker)
	std::swap(fighter1, fighter2);

	for (;;) {
	fighter2->setHealth(fighter2->getHealth() - fighter1->getDamagePerAttack());
	if (fighter2->getHealth() <= 0)
	return fighter1->getName();

	fighter1->setHealth(fighter1->getHealth() - fighter2->getDamagePerAttack());
	if (fighter1->getHealth() <= 0)
	return fighter2->getName();
	}*/
}


/*
int main() {
	Fighter fighter1("Lew", 10, 2);
	Fighter fighter2("Harry", 5, 4);

	std::string expected1 = "Harry";
	std::string actual1 = declareWinner(&fighter1, &fighter2, "Harry");

	std::string expected2 = "Lew";
	std::string actual2 = declareWinner(&fighter1, &fighter2, "Lew");

	return 0;
}
*/
