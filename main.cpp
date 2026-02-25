#include <iostream>
#include "Enemies/SuperMutant.h"
#include "Character.h"
#include "Weapons/Weapon.h"



int main(){
  Weapon w1("Pistol", 25, 100, 1);
  SuperMutant sm1("Giant Super Mutant", 150, 100, w1);
  Character c1("Vault Dweller", 100, 50, {w1});
  c1.attack(sm1, w1);
  sm1.attack(c1);



  return 0;
}
