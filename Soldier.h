#ifndef SOLDIER_H
#define SOLDIER_H

#include "Warrior.h"

/*
A Soldier is an Warrior that if attacked, it will start attacking its attacker.
*/
class Soldier : public Warrior {
public:
	Soldier(const std::string& name_, Point location_);

	// Construct a Soldier with specified health
	Soldier(const std::string& name_, Point location_, int health_);

	// Overrides Warrior's take_hit to counter-attack when attacked.
	void take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr) override;

	// output information about the current state
	void describe() const override;
    
protected:
    // output the "Clang" sound of the sword
    void make_sound() const noexcept override;
};

#endif
