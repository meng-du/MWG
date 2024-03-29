#ifndef COMMANDER_H
#define COMMANDER_H

#include "Warrior.h"

class Soldier;

class Commander : public Warrior {
public:
	Commander(const std::string& name_, Point location_);

	// update implements Commander behavior
	void update() override;

	// Overrides Warrior's take_hit to summon a servant when attacked.
	void take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr) override;

	// output information about the current state
	void describe() const override;

protected:
	// output the "Neighhh" sound of its horse
	void make_sound() const noexcept override;

private:
    // commander refers to his steward by using a weak_ptr
	std::weak_ptr<Soldier> steward;
    
    // if this commander's steward exists, disband the steward
    void disband_steward();
};

#endif
