#include "Pokemon.h"
using namespace std;

Pokemon::Pokemon() {
  m_name = "Bulbasaur";
  m_index = 1;
  m_type = "Grass";
  m_strong = "Ground";
  m_health = MAX_HEALTH;
}

Pokemon::Pokemon(int index, string type, string strong, string name){
  m_index = index;
  m_type = type;
  m_strong = strong;
  m_name = name;
  m_health = MAX_HEALTH;
}

Pokemon* Pokemon::GetNext(){
  return m_next;
}

string Pokemon::GetName(){
  return m_name;
}

string Pokemon::GetType(){
  return m_type;
}

int Pokemon::GetIndex(){
  return m_index;
}

int Pokemon::GetHealth(){
  return m_health;
}

string Pokemon::GetStrong(){
  return m_strong;
}

void Pokemon::SetHealth(int hp){
  m_health = hp;
}

void Pokemon::SetNext(Pokemon* pokemon){
  m_next = pokemon;
}

ostream &operator<<(ostream &output, Pokemon &P){

  output << "Index: " << std::left << setw(5) << P.m_index
	 << "Name: " << std::left << setw(13) << P.m_name
	 << "Type: " << std::left << setw(10) << P.m_type
	 << "Health: " << std::left << setw(3) << P.m_health << endl;
  return output;
}
