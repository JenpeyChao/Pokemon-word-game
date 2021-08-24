#include "Game.h"

using namespace std;

Game::Game(string name){
  m_filename = name;

  m_userPocket = new PokemonList();

  m_list = new PokemonList();
 
  m_enemyPocket = new PokemonList();
}
Game::~Game(){

  delete m_enemyPocket;
  
  delete m_list;
  
  delete m_userPocket;

}

void Game::LoadFile(){
  //opens up the file
  ifstream textFile;
  textFile.open(m_filename);
    
  string type, strong, name, index;

  if (textFile.is_open() ){
    
    while (getline(textFile, index, ',')){
      //reads all the lines in the file and sets them into the variables
      
      getline(textFile, name, ',');
      getline(textFile, type, ',');
     
      textFile >> strong;
      textFile.ignore(256, '\n');
      int number = stoi(index);
      //then inserts the data into the pokemon list
      Pokemon* pokemon = new Pokemon(number, type, strong, name);
      
      m_list->InsertEnd(pokemon);

    }
  }
}

int Game::Start(){
  int battle;
  //loads file, choose teams, then battle
  Game::LoadFile();
  Game::ChooseTeam();
  battle = Game::Battle();

  return battle;
}

void Game::ChooseTeam(){
  int numPokemon = 0;
  int choice = 0;
  int lowestPoke = 1;
  int maxPoke = 151;
  int choosePoke = 5;
  int rndNum;
  //promts the user thel ist of pokemons and asks them to choose 5 
  while (numPokemon < 5){
    cout << "Here is a list of Pokemon you can choose from:" << endl;
    cout << "------------------------------" << endl;
    m_list->Display();
    cout << "------------------------------" << endl;
    cout << "Pick a pokemon by enter the index (" << choosePoke << " left): " << endl;
    cin >> choice;
    while ((choice < lowestPoke) || ( choice > maxPoke)){
	
	cout << "Please pick a valid pokemon" << endl;
	cin >> choice;
    }
    if (choice == lowestPoke){
      lowestPoke += 1;
    }else if (choice == maxPoke){
      maxPoke -= 1;
    }

    choosePoke -= 1;
    numPokemon += 1;
    //take the pokemon and puts it into the users pocket
    m_list->Transfer(choice, m_userPocket);
    m_list->Remove(choice);

  }
  //after the user is done choosing the cpu gets 5 random pokemons placed into their pockets
  numPokemon = 0;

  while (numPokemon < 5){

    rndNum = (rand() % maxPoke + 1 - lowestPoke) + lowestPoke;

    while ((rndNum < lowestPoke) || (rndNum > maxPoke)){

      rndNum = (rand() % maxPoke + 1 - lowestPoke) + lowestPoke;
    }

    numPokemon += 1;
    m_list->Transfer(rndNum, m_enemyPocket);
    m_list->Remove(rndNum);
  }
  //then couts both pockets of pokemons
  cout << "------------------------------" << endl;
  cout << "Print player pocket" << endl;
  m_userPocket->Display();

  cout << "------------------------------" << endl;
  cout << "Print cpu pocket" << endl;
  m_enemyPocket->Display();

}

int Game::Menu(){
  //prompts the user on what to do and returns the number
  int choice = 0;
  cout << "------------------------------" << endl;
  cout << "Menu:" << endl;
  cout << "1. Attack" << endl;
  cout << "2. Swap" << endl;
  cout << "3. ForFeit" << endl;
  cout << "------------------------------" << endl;
  cin >> choice;
  //if the choice isnt between 1-3 then it repromts
  while ((choice < 1) || (choice > 3)){
    cout << "Please try again" << endl;
    cin >> choice;
  }

  return choice;
}

int Game::Battle(){
  int choice = 0;
  int round = 1;
  int dead;
  const int USER_POKE_DEAD = 1, CPU_POKE_DEAD = 2;
  const int USER_WIN = 1, CPU_WIN = 2, QUIT = 3;
  // while choice isnt 3 the battle will keep looping
  while(choice != 3){
    //couts the two fighting pokemons
    cout << "------------------------------" << endl;
    cout << "Round " << round << ":" << endl;

    cout << "CPU's Pokemon: " << m_enemyPocket->GetHead()->GetName() << "("
	 << m_enemyPocket->GetHead()->GetType()
	 << ":" << m_enemyPocket->GetHead()->GetHealth() << " health)" << endl;

    cout << "Your's Pokemon: " << m_userPocket->GetHead()->GetName() << "("
	 << m_userPocket->GetHead()->GetType()
	 << ":" << m_userPocket->GetHead()->GetHealth() << " health)" << endl;
    //promts the menu
    choice = Game::Menu();

    switch(choice){
      
    case 1:
      //checks if the pokemon is strong against each other
      //if user pokemon goes below 0 hp it will return 1
      //if enemy pokemon goes below 0 it will return 2
      //else returns 0
      dead = m_userPocket->Attack(m_enemyPocket);

      //if pokemon dies it gets removed from the team
      //and gets to pick a new pokemon
      if (dead == USER_POKE_DEAD){
	cout << "Your pokemon has been defeated" << endl;
	m_userPocket->Remove(m_userPocket->GetHead()->GetIndex());
	m_userPocket->SwapPokemon();

      }else if (dead == CPU_POKE_DEAD){
	//if cpus pokemon dies it gets removed from their list
	cout << "Cpu's pokemon has been defeated" << endl;
	m_enemyPocket->Remove(m_enemyPocket->GetHead()->GetIndex());
      }
      //checks the size of the teams
      // if its below it breaks the loop
      if (m_userPocket->GetSize() <= 0){
	choice = 3;

      }else if (m_enemyPocket->GetSize() <= 0){
	choice = 3;
      }

      break;
      
    case 2:
      //swaps pokemon around
      m_userPocket->SwapPokemon();
      
      break;
    }
    round += 1;
  }

  //if the user team is 0 or below cpu wins
  if (m_userPocket->GetSize() <= 0){

    return CPU_WIN;

    
    // if the enemy team is 0 or below user wins
  }else if (m_enemyPocket->GetSize() <= 0){

    return USER_WIN;

  }else{
    //else its a forfeit

    return QUIT;
  } 
  
}
