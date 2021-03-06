#pragma once
/*
* This class will be responsible for applying different
* types of statuses to the Character class.
* STATUS: Burning, Wet, Chilled, Frozen, Conductive, Stunned
*/
class Status
{
private:
	float statusDuration = 0.0f;
	float DOT = 0.0f; //Damage over time

	//How long each status will last
	float burningDuration = 5.0f;
	float wetDuration = 7.0f;
	float chilledDuration = 5.0f;
	float frozenDuration = 5.0f;
	float conductiveDuration = 7.0f;
	float stunnedDuration = 5.0f;

	bool Burning = false;
	bool Wet = false;
	bool Chilled = false;
	bool Frozen = false;
	bool Conductive = false;
	bool Stunned = false;
	bool Normal = true;

public:
	float getDuration() { return statusDuration; }
	void setDuration(float amt) { statusDuration = amt; }

	float getDOT() { return DOT; }
	void setDOT(float amt) { DOT = amt; }

	void setBurning() { Burning = true; Normal = false; statusDuration = burningDuration; DOT = 0.5f; }
	void setWet() { Wet = true; Normal = false; statusDuration = wetDuration; DOT = 0.0f; }
	void setChilled() { Chilled = true; Normal = false; statusDuration = chilledDuration; DOT = 0.0f; }
	void setFrozen() { Frozen = true; Normal = false; statusDuration = frozenDuration; DOT = 0.0f; }
	void setConductive() { Conductive = true; Normal = false; statusDuration = conductiveDuration; DOT = 0.0f; }
	void setStunned() { Stunned = true; Normal = false; statusDuration = stunnedDuration; DOT = 0.0f; }
	void setNormal() { Normal = true; Burning = false; Wet = false; Chilled = false; Frozen = false; Conductive = false; Stunned = false; statusDuration = 0.0f; DOT = 0.0f; }

	float getBurningDuration() { return burningDuration; }
	float getWetDuration() { return wetDuration; }
	float getChilledDuration() { return chilledDuration; }
	float getFrozenDuration() { return frozenDuration; }
	float getConductiveDuration() { return conductiveDuration; }
	float getStunnedDuration() { return stunnedDuration; }

	bool isNormal() { return Normal; }
	bool isBurning() { return Burning; }
	bool isWet() { return Wet; }
	bool isChilled() { return Chilled; }
	bool isFrozen() { return Frozen; }
	bool isConductive() { return Conductive; }
	bool isStunned() { return Stunned; }
};

/*
* BURNING:
* >Applied when hit wit a FIRE attack
* >Character takes damage over time.
* >BURNING removed if character is hit with a WATER attack.
* >Character's airRES increase to 1.5 so they take 50% more damage from AIR attacks.
* 
* WET:
* >Applied when hit with a WATER attack
* >Character's electrictyRES increased to 1.5.
* >WET removed when hit with an ICE attack. Replaced with FROZEN instead.
* >WET removed when hit with a ELECTRICTY attack. Replaced with STUNNED instead.
* >WET removed when hit with a FIRE attack.
* 
* CHILLED:
* >Applied when hit with and ICE attack
* >Slows the movement speed (moveSpeed) of the Character
* >Character airRES increased to 1.5.
* >CHILLED removed when hit with a WATER attack. Replaced with FROZEN instead.
* >CHILLED removed when hit with a FIRE attack.
* 
* FROZEN:
* >Applied when hit with both WATER and ICE attacks. (See WET and CHILLED)
* >Character can not move while FROZEN.
* >Character earthRES increased to 1.5.
* >FROZEN removed when hit with a FIRE attack.
* >FROZEN removed when hit with an EARTH attack.
* 
* CONDUCTIVE:
* >Applied when hit with an ELECTRICTY attack.
* >When hit with another ELECTRICTY attack, will send a shock attack to a nearby enemy.
* >CONDUCTIVE removed when hit with a WATER attack. Replaced with STUNNED instead.
* 
* STUNNED:
* >Applied when hit with ELECTRICTY and WATER attacks. (See WET and CONDUCTIVE)
* >Character can not moved while STUNNED.
*/