#include "Hero.h"

void Hero::changeATK(Dice d) {
	def.setATK(d);
}
void Hero::revertATK() {
	def.setATK(base_atk);
}
void Hero::changeDEF(int num) {
	def.setDEF(def.getDEF() + num);
}
void Hero::changeHP(int num) {
	hp = hp + num;
	if (hp > def.getMaxHP())
		hp = def.getMaxHP();
}
void Hero::changeMaxHP(int num) {
	int newMax = def.getMaxHP() + num;
	if (newMax < hp)
		hp = newMax;
	def.setMaxHP(newMax);
}

void Hero::changeMana(int num) {
	mana = mana + num;
	if (mana > maxMana)
		mana = maxMana;
}
void Hero::changeMaxMana(int num) {
	maxMana = maxMana + num;
}

int Hero::getMana() {
	return mana;
}
int Hero::getMaxMana() {
	return maxMana;
}