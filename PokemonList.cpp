#include "PokemonList.h"

using namespace std;

PokemonList::PokemonList(){
  m_head = nullptr;
  m_size = 0;

}

PokemonList::~PokemonList(){
  //removes all the pokemon from the lists at the end
  Pokemon *curr = m_head;

  while (m_head != NULL){

    Pokemon *temp = curr;
    curr = curr->GetNext();
    m_head = curr;
    delete temp;
  
  }
  delete m_head;
  m_head = nullptr;
  m_size = 0;
}
void PokemonList::InsertEnd(Pokemon* pokemon){
  // if theres an empty list then m_head is equal to the first pokemon
  
  
  if (m_head == nullptr){
    
    m_head = pokemon;
    
  }else{
    //else it make a new node and connects the node to the end of the list
    Pokemon *temp = m_head;
    
    while(temp->GetNext() != nullptr){

      temp = temp->GetNext();
    }
    temp->SetNext(pokemon);

    m_size += 1;
  }
}

void PokemonList::Display(){
  // if the size of the list is 0 then theres no pokemon in it 
  if(m_size == 0){
    
    cout << "the list is empty" << endl;

  }else{
    //else it will cout all the pokemon in the list 
    Pokemon *curr = m_head;
    
    while(curr != nullptr){

      cout << *curr;
      curr = curr->GetNext();
    }
  }
}

void PokemonList::Transfer(int index, PokemonList* pokemonList){
  //takes the pokemon the user chose and puts it in the pokemonList
  string type, strong, name;
  
  Pokemon *curr = m_head;

  while (curr->GetIndex() != index){
    //loop through until it hits the right pokemon
    curr = curr->GetNext();
  }
  //once it gets the right pokemon, it tkaes the data from inside
  // and inserts it into the pokemonList
  type = curr->GetType();
  strong = curr->GetStrong();
  name = curr->GetName();
  
  Pokemon *pokemon = new Pokemon(index, type, strong, name);
  
  pokemonList->PokemonList::InsertEnd(pokemon);


}

void PokemonList::Remove(int index){

  Pokemon *curr = m_head;
  Pokemon *prev = m_head;
  const int DIDNT_MOVE = 0;
  int moves = 0;
  while (curr->GetIndex() != index){
    //loops through untill it finds the right pokemon
    prev = curr;
    curr = curr->GetNext();
    moves += 1;
  }
  if (moves == DIDNT_MOVE){
    //if the pokemon is the head of the list
    //then it will remove it and set the next pokemon to the head of the list
    curr = curr->GetNext();
    delete prev;
    m_head = curr;
    m_size -= 1;
  
  }else{
    //if its not the head then it will point to the next next pokemon and remove the
    //current one
    prev->SetNext(curr->GetNext());

    delete curr;
    m_size -= 1;
  }
}

void PokemonList::SwapPokemon(){
  bool hasPoke;
  int pokemon;
  Pokemon *curr = m_head;
  //user picks out a pokemon that they want to switch out 
  cout << "Which Pokemon would you like to choose? (Enter the index#)" << endl;
  Display();
  cin >> pokemon;
  hasPoke = PokemonList::Exist(pokemon);
  while (hasPoke == false){
    //if the pokemon isnt in the list then user has to pick again
    cout << "This is not a valid pokemon, please try again" << endl;
    cin >> pokemon;
    hasPoke = PokemonList::Exist(pokemon);
  }

  if (hasPoke == true){
    Pokemon *swap = m_head;
    Pokemon *prev = m_head;
    while (swap->GetIndex() != pokemon){
      //loops through the list finding the pokemon to swap
      prev = swap;
      swap = swap->GetNext();

    }
    if (curr->GetIndex() == swap->GetIndex()){
      //if the pokemon is the head it wont swap
      cout << "You cant do that, pokemon is already in battle" <<endl;

    }else if (swap->GetNext() == nullptr){
      //if its at the end it will swap
      swap->SetNext(curr->GetNext());
      prev->SetNext(curr);
      m_head = swap;
      curr->SetNext(nullptr);

    }else if(curr->GetNext() == swap){
      //same goes for if the pokemon is next to the head
      Pokemon *temp;
      temp = swap->GetNext();
      swap->SetNext(curr);
      curr->SetNext(temp);
      m_head = swap;
      
    }else{
      //if its in the middle of the list then it will swap as well
      Pokemon *temp;
      
      temp = swap->GetNext();
      swap->SetNext(curr->GetNext());
      curr->SetNext(temp);
      m_head = swap;
      prev->SetNext(curr);
    }
    cout << "You changed your pokemon to:" << swap->GetName() << " (" << swap->GetType()
	 << ":" << swap->GetHealth() << " health)" << endl;
  }
}


bool PokemonList::Exist(int index){
  Pokemon *curr = m_head;
  while (curr != nullptr){
    //checks to see if the pokemon is in the list
    //if it is then it returns true, if not then it returns false
    if (curr->GetIndex() == index)
      return true;

    curr = curr->GetNext();
    
  }
  return false;
}

int PokemonList::GetSize(){
  return m_size;
}

Pokemon* PokemonList::GetHead(){
  return m_head;
}

int PokemonList::Attack(PokemonList* enemyList){
  string cpuType, userType;
  int cpuHealth, userHealth;
  const string GROUND = "Ground", GRASS = "Grass", FIRE = "Fire", ICE = "Ice", WATER = "Water",
    BUG = "Bug", PSYCHIC = "Psychic", NORMAL = "Normal", FAIRY = "Fairy", POISON = "Poison",
    ELECTRIC = "Electric", DRAGON = "Dragon", FIGHTING = "Fighting", ROCK = "Rock",
    GHOST = "Ghost";
  
  Pokemon *user = m_head;
  
  cpuHealth = enemyList->GetHead()->GetHealth();

  userHealth = user->GetHealth();

  cpuType = enemyList->GetHead()->GetType();

  userType = user->GetType();

  if(((cpuType == GRASS) && (userType == GROUND)) || ((cpuType == GROUND) && (userType == GRASS))){
    //if cpu is grass and user is ground or the converse of that 
    if (cpuType == GRASS){
      // if the cpu is grass then the user is ground
      //and it will do strong damage to the user and normal damage to the cpu
      user->SetHealth(userHealth - STRONG_DAMAGE);
      enemyList->GetHead()->SetHealth(cpuHealth - DAMAGE2ENEMY);
      cout <<"CPU'S pokemon took 2 damage" << endl << "Your pokemon took 5 damage" << endl;

    }else{
      //if its the other way around then it will do strong damage to the cpu
      //and normal damage to the user
      user->SetHealth(userHealth - DAMAGE2USER);
      enemyList->GetHead()->SetHealth(cpuHealth - STRONG_DAMAGE);
      cout << "CPU's pokemon took 5 damage" << endl << "Your pokemon took 3 damage" << endl;

    }
  }else if (((cpuType == FIRE) && (userType == ICE)) || ((cpuType == ICE) && (userType == FIRE))){
    //if cpu is fire and user is ice or the converse of that 

    if (cpuType == FIRE){
      //if the cpu is fire then the user is ice
      //will do strong damage to the user and normal damage to the cpu
      user->SetHealth(userHealth - STRONG_DAMAGE);
      enemyList->GetHead()->SetHealth(cpuHealth - DAMAGE2ENEMY);
      cout <<"CPU'S pokemon took 2 damage" << endl << "Your pokemon took 5 damage" << endl;

    }else{
      //and the other way around
      user->SetHealth(userHealth - DAMAGE2USER);
      enemyList->GetHead()->SetHealth(cpuHealth - STRONG_DAMAGE);
      cout << "CPU's pokemon took 5 damage" << endl << "Your pokemon took 3 damage" << endl;

    }
  }else if (((cpuType == WATER) && (userType == FIRE)) || ((cpuType == FIRE) && (userType == WATER))){
    //if cpu is water and user is fire or the other way around

    if (cpuType == WATER){
      //if the cpu is water then it will do strong to user
      //and normal damage to the cpu
      user->SetHealth(userHealth - STRONG_DAMAGE);
      enemyList->GetHead()->SetHealth(cpuHealth - DAMAGE2ENEMY);
      cout <<"CPU'S pokemon took 2 damage" << endl << "Your pokemon took 5 damage" << endl;
    }else{
      //and the other way around
      user->SetHealth(userHealth - DAMAGE2USER);
      enemyList->GetHead()->SetHealth(cpuHealth - STRONG_DAMAGE);
      cout << "CPU's pokemon took 5 damage" << endl << "Your pokemon took 3 damage" << endl;
    }

  }else if (((cpuType == BUG) && (userType == PSYCHIC)) || ((cpuType == PSYCHIC) && (userType == BUG))){    //if cpu is bug and user is psychic or the other way around

    if (cpuType == BUG){
      //if the cpu is bug then it will do strong to user
      //and normal damage to the cpu
      user->SetHealth(userHealth - STRONG_DAMAGE);
      enemyList->GetHead()->SetHealth(cpuHealth - DAMAGE2ENEMY);
      cout <<"CPU'S pokemon took 2 damage" << endl << "Your pokemon took 5 damage" << endl;
      
    }else{
      //and the other way around
      user->SetHealth(userHealth - DAMAGE2USER);
      enemyList->GetHead()->SetHealth(cpuHealth - STRONG_DAMAGE);
      cout << "CPU's pokemon took 5 damage" << endl << "Your pokemon took 3 damage" << endl;
      
    }
  }else if (((cpuType == NORMAL) && (userType == FAIRY)) || ((cpuType == FAIRY) && (userType == NORMAL))){    //if the cpu is normal and the user is fairy or the other way around

    if (cpuType == NORMAL){
      //if the cpu is normal then it does strong damage to the user
      //and normal to he cpu
      user->SetHealth(userHealth - STRONG_DAMAGE);
      enemyList->GetHead()->SetHealth(cpuHealth - DAMAGE2ENEMY);
      cout <<"CPU'S pokemon took 2 damage" << endl << "Your pokemon took 5 damage" << endl;
      
    }else{
      //and the other way around
      user->SetHealth(userHealth - DAMAGE2USER);
      enemyList->GetHead()->SetHealth(cpuHealth - STRONG_DAMAGE);
      cout << "CPU's pokemon took 5 damage" << endl << "Your pokemon took 3 damage" << endl;
      
    }
  }else if (((cpuType == POISON) && (userType == GRASS)) || ((cpuType == GRASS) && (userType == POISON))){    //if the cpu is poison and the user is grass or the other way around 

    if (cpuType == POISON){
      //if the cpu is poison then it does strong damage to the user
      //and normal to the cpu
      user->SetHealth(userHealth - STRONG_DAMAGE);
      enemyList->GetHead()->SetHealth(cpuHealth - DAMAGE2ENEMY);
      cout <<"CPU'S pokemon took 2 damage" << endl << "Your pokemon took 5 damage" << endl;

    }else{
      //and the other way around
      user->SetHealth(userHealth - DAMAGE2USER);
      enemyList->GetHead()->SetHealth(cpuHealth - STRONG_DAMAGE);
      cout << "CPU's pokemon took 5 damage" << endl << "Your pokemon took 3 damage" << endl;
      
    }
  }else if (((cpuType == ELECTRIC) && (userType == WATER)) || ((cpuType == WATER) && (userType == ELECTRIC))){
    //if cpu is electric and user is water or other way around 

    if (cpuType == ELECTRIC){
      //if cpu is electric then it does strong damage to user
      //and normal dmaage to cpu
      user->SetHealth(userHealth - STRONG_DAMAGE);
      enemyList->GetHead()->SetHealth(cpuHealth - DAMAGE2ENEMY);
      cout <<"CPU'S pokemon took 2 damage" << endl << "Your pokemon took 5 damage" << endl;

    }else{
      //and other way around
      user->SetHealth(userHealth - DAMAGE2USER);
      enemyList->GetHead()->SetHealth(cpuHealth - STRONG_DAMAGE);
      cout << "CPU's pokemon took 5 damage" << endl << "Your pokemon took 3 damage" << endl;
      
    }
  }else if (((cpuType == GROUND) && (userType == POISON)) || ((cpuType == POISON) && (userType == GROUND))){
    //if cpu is ground and user is poison or the other way around

    if (cpuType == GROUND){
      //if cpu is ground then it does strong to hte user and normal for cpu
      user->SetHealth(userHealth - STRONG_DAMAGE);
      enemyList->GetHead()->SetHealth(cpuHealth - DAMAGE2ENEMY);
      cout <<"CPU'S pokemon took 2 damage" << endl << "Your pokemon took 5 damage" << endl;
      
    }else{
      //and other way around 
      user->SetHealth(userHealth - DAMAGE2USER);
      enemyList->GetHead()->SetHealth(cpuHealth - STRONG_DAMAGE);
      cout << "CPU's pokemon took 5 damage" << endl << "Your pokemon took 3 damage" << endl;
      
    }
  }else if (((cpuType == FAIRY) && (userType == DRAGON)) || ((cpuType == DRAGON) && (userType == FAIRY))){
    //if cpu is fairy and user is dragon or the other way around 

    if (cpuType == FAIRY){
      //if cpu is fairy then it does srtong to the user and normal for cpu
      user->SetHealth(userHealth - STRONG_DAMAGE);
      enemyList->GetHead()->SetHealth(cpuHealth - DAMAGE2ENEMY);
      cout <<"CPU'S pokemon took 2 damage" << endl << "Your pokemon took 5 damage" << endl;

    }else{
      //and othe way around
      user->SetHealth(userHealth - DAMAGE2USER);
      enemyList->GetHead()->SetHealth(cpuHealth - STRONG_DAMAGE);
      cout << "CPU's pokemon took 5 damage" << endl << "Your pokemon took 3 damage" << endl;
      
    }

  }else if (((cpuType == FIGHTING) && (userType == ROCK)) || ((cpuType == ROCK) && (userType == FIGHTING))){
    //if cpu is fighting and user is rock and other way around

    if (cpuType == FIGHTING){
      //if cpu is fighting then it does strong to the user and normal for cpu 
      user->SetHealth(userHealth - STRONG_DAMAGE);
      enemyList->GetHead()->SetHealth(cpuHealth - DAMAGE2ENEMY);
      cout <<"CPU'S pokemon took 2 damage" << endl << "Your pokemon took 5 damage" << endl;

    }else{
      //and other way around 
      user->SetHealth(userHealth - DAMAGE2USER);
      enemyList->GetHead()->SetHealth(cpuHealth - STRONG_DAMAGE);
      cout << "CPU's pokemon took 5 damage" << endl << "Your pokemon took 3 damage" << endl;

    }
  }else if (((cpuType == PSYCHIC) && (userType == FIGHTING)) || ((cpuType == FIGHTING) && (userType == PSYCHIC))){
    //if cpu is psychic and user is fighting or other way around 

    if (cpuType == PSYCHIC){
      //if user is psychic  then it does strong to the user and normal for cpu
      user->SetHealth(userHealth - STRONG_DAMAGE);
      enemyList->GetHead()->SetHealth(cpuHealth - DAMAGE2ENEMY);
      cout <<"CPU'S pokemon took 2 damage" << endl << "Your pokemon took 5 damage" << endl;

    }else{
      //and other way around
      user->SetHealth(userHealth - DAMAGE2USER);
      enemyList->GetHead()->SetHealth(cpuHealth - STRONG_DAMAGE);
      cout << "CPU's pokemon took 5 damage" << endl << "Your pokemon took 3 damage" << endl;
      
    }

  }else if (((cpuType == ROCK) && (userType == BUG)) || ((cpuType == BUG) && (userType == ROCK))){
    //if cpu is rock and user is bug or other way around

    if (cpuType == ROCK){
      // if cpu is rock  then it does strong to the user and normal for cpu
      user->SetHealth(userHealth - STRONG_DAMAGE);
      enemyList->GetHead()->SetHealth(cpuHealth - DAMAGE2ENEMY);
      cout <<"CPU'S pokemon took 2 damage" << endl << "Your pokemon took 5 damage" << endl;

    }else{
      //and other way around 
      user->SetHealth(userHealth - DAMAGE2USER);
      enemyList->GetHead()->SetHealth(cpuHealth - STRONG_DAMAGE);
      cout << "CPU's pokemon took 5 damage" << endl << "Your pokemon took 3 damage" << endl;
      
    }
  }else if (((cpuType == DRAGON) && (userType == ELECTRIC)) || ((cpuType == ELECTRIC) && (userType == DRAGON))){
    //if cpu is dragon and user is electric or other way around 

    if (cpuType == DRAGON){
      //if cpu is dragon then it does strong to the user and normal for cpu
      user->SetHealth(userHealth - STRONG_DAMAGE);
      enemyList->GetHead()->SetHealth(cpuHealth - DAMAGE2ENEMY);
      cout <<"CPU'S pokemon took 2 damage" << endl << "Your pokemon took 5 damage" << endl;

    }else{
      //and other way around
      user->SetHealth(userHealth - DAMAGE2USER);
      enemyList->GetHead()->SetHealth(cpuHealth - STRONG_DAMAGE);
      cout << "CPU's pokemon took 5 damage" << endl << "Your pokemon took 3 damage" << endl;
      
    }
  }else if (((cpuType == GHOST) && (userType == GHOST)) || ((cpuType == GHOST) && (userType == GHOST))){
    //if both are ghost then they both do strong damage to each other 

    user->SetHealth(userHealth - STRONG_DAMAGE);
    enemyList->GetHead()->SetHealth(cpuHealth - STRONG_DAMAGE);
    cout <<"CPU'S pokemon took 5 damage" << endl << "Your pokemon took 5 damage" << endl;
    
  }else if (((cpuType == ICE) && (userType == NORMAL)) || ((cpuType == NORMAL) && (userType == ICE))){
    //if cpu is ice and user is normal or other way around 

    if (cpuType == ICE){
      //if cpu is ice then it does strong to the user and normal for cpu
      user->SetHealth(userHealth - STRONG_DAMAGE);
      enemyList->GetHead()->SetHealth(cpuHealth - DAMAGE2ENEMY);
      cout <<"CPU'S pokemon took 2 damage" << endl << "Your pokemon took 5 damage" << endl;

    }else{
      //and other way around 
      user->SetHealth(userHealth - DAMAGE2USER);
      enemyList->GetHead()->SetHealth(cpuHealth - STRONG_DAMAGE);
      cout << "CPU's pokemon took 5 damage" << endl << "Your pokemon took 3 damage" << endl;

    }
  }else{
    // if the user and cpu isnt strong against each other then
    //they both do normal damage to each other 
    user->SetHealth(userHealth - DAMAGE2USER);
    enemyList->GetHead()->SetHealth(cpuHealth - DAMAGE2ENEMY);
    cout << "CPU's pokemon took 2 damage" << endl << "Your pokemon took 3 damage" << endl;
  }

  if ((user->GetHealth() == 0) || (userHealth < 0)){
    //if the user pokemon health does to 0 or below 0 then it returns 1
    return 1;
  }
  else if (cpuHealth <= 0){
    //if the health for cpu goes down to 0 or below then it returns 2
    return 2;
  }else{
  //else it will return 0 
  return 0;
  }
}
