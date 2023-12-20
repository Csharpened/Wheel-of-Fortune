#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

void printLetters(vector<char> letters);

void printLogo();

void printWheel();

char isLetter(char letter);

class player
{
	private:
		string name;
		double roundMoney;
		double totalMoney;
	public:
		player(string n)
		{
			name=n;
			roundMoney=0;
			totalMoney=0;
		}
		string getName()
		{
			return name;
		}
		double getRound()
		{
			return roundMoney;
		}
		double getTotal()
		{
			return totalMoney;
		}
		void setName(string n)
		{
			name=n;
		}
		void setRound(double r)
		{
			roundMoney=r;
		}
		void setTotal(double t)
		{
			totalMoney=t;
		}
		void addRound(double r)
		{
			roundMoney+=r;
		}
		void addTotal(double t)
		{
			totalMoney+=t;
		}
};

int main()
{
	cout << "Welcome to WHEEL OF FORTUNE" << endl;
	printLogo();
	cout << endl << endl;
	printWheel();
	cout << endl;
	cout << "This game will simulate the popular gameshow." << endl;
	player p1("Player 1");
	player p2("Player 2");
	player p3("Player 3");
	
	srand(time(0));
	int current_player;
	current_player = rand() % 3 + 1;

	string phrase, guessed;
	vector<char>letters;

	for(int i=0; i<3; i++)
	{
		
		cout<<"Enter the puzzle for this round: ";
		getline(cin, phrase);
		for(int i = 0; i < phrase.length(); i++)
			{
				phrase[i] = tolower(phrase[i]);
			}
		guessed=phrase;
		for(int i=0; i<phrase.length(); i++)
		{
			if(phrase[i]!=' ')
			{
				guessed[i]='_';
			}
		}
		
		while(guessed!=phrase)
		{	
			cout << endl;
			cout<<"Puzzle: "<<guessed<<endl;
			printLetters(letters);
			cout << endl;
			cout<<"Player 1's Round Total: $"<<p1.getRound()<<endl;
			cout<<"Player 2's Round Total: $"<<p2.getRound()<<endl;
			cout<<"Player 3's Round Total: $"<<p3.getRound()<<endl<<endl;
			cout << "Player " << current_player << " was chosen!" << endl;
			cout<<"It is Player "<<current_player<<"'s turn."<<endl << endl;
			cout<<"1. Spin the wheel"<<endl;
			cout<<"2. Buy a vowel"<<endl;
			cout<<"3. Solve the puzzle"<<endl << endl;
			cout<<"Enter your choice: ";
			int choice;
			cin >> choice;
			while(cin.fail()) {
        cout << "Enter your choice: ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> choice;
    }
			switch(choice)
			{
				case 1:
					{
						double money=rand()%3000+100;
						cout<<"The wheel spun for $"<<money<<endl << endl;
						char letter;
						while(1)
						{
							cout << "Enter a consonant: ";
							cin >> letter;
							if(isLetter(letter)=='v')
							{
								cout<<"That is a vowel, you must enter a consonant."<<endl << endl;
							}
							else if(isLetter(letter)=='!')
							{
								cout<<"That is not a consonant, you must enter a consonant."<<endl << endl;
							}
							else
							{
								int found=0;
								for(int i=0; i<letters.size(); i++)
								{
									if(letter==letters[i])
									{
										cout<<"That letter has already been guessed."<<endl << endl;
										found=1;
									}
								}
								if(found==0)
								{
									break;
								}
							}
						}
						int occurs = 0;
						for(int i = 0; i < phrase.length(); i++)
						{
							if(phrase[i]==letter)
							{
								occurs++;
								guessed[i]=phrase[i];
							}
						}
						letters.push_back(letter);
						cout << "That letter occurs " << occurs << " times in the phrase." << endl << endl;
						money*=occurs;
						cout << "Player " << current_player << " gets $" << money << endl << endl;
						switch(current_player)
						{
							case 1:
								p1.addRound(money);
								break;
							case 2:
								p2.addRound(money);
								break;
							case 3:
								p3.addRound(money);
								break;
						}
						
					}
					break;
				case 2:
					{
						char vowel;
						int vowelCount;
						double playerMoney;
						switch(current_player)
							{
								case 1:
									{
										playerMoney = p1.getRound();
										break;
									}
								case 2:
									{
										playerMoney = p2.getRound();
										break;
									}
								case 3:
									{
										playerMoney = p3.getRound();
										break;
									}
							}

						if(playerMoney <= 0)
						{
							cout << "You cannot buy a vowel with no money." << endl;
							current_player--;
							break;
						}
						
						
						while(1)
							{
								cout << "Enter the vowel to guess: ";
								cin >> vowel;

								if(isLetter(vowel) != 'v')
								{
									cout << "This is not a vowel" << endl << endl;
								}
								else
								{
									vowel = tolower(vowel);
									break;
								}
							}
						
						int found=0;
						for(int i = 0; i < phrase.length(); i++)
							{
								if(tolower(phrase[i]) == vowel)
								{
									vowelCount++;
									found=1;
									guessed[i]=vowel;
								}
							}
						if(found==1)
						{
							letters.push_back(vowel);
						}
						
						int totalVowel = vowelCount * -50;
						switch(current_player)
						{
							case 1:
								p1.addRound(totalVowel);
								break;
							case 2:
								p2.addRound(totalVowel);
								break;
							case 3:
								p3.addRound(totalVowel);
								break;
						}
						vowelCount = 0;
						break;
					}
				case 3:
					{
						string puzzleGuess;
						cout<<"Enter the puzzle: ";
						cin.ignore();
						getline(cin, puzzleGuess);
						if(puzzleGuess==phrase)
						{
							guessed=puzzleGuess;
						}
						else
						{
							cout<<"That guess is incorrect"<<endl << endl;
						}
						
						break;
					}
			}
			if(guessed == phrase)
			{
				cout << endl;
				letters.clear();
				cout<<"Player " << current_player << " solved the puzzle!" << endl;
				
				switch(current_player)
				{
					case 1:
						p1.addTotal(p1.getRound());
						cout<<"Player 1's Grand Total is: $"<<p1.getTotal()<<endl;
						cout<<"Player 2's Grand Total is: $"<<p2.getTotal()<<endl;
						cout<<"Player 3's Grand Total is: $"<<p3.getTotal()<<endl;
						cout << endl;
						p1.setRound(0);
						p2.setRound(0);
						p3.setRound(0);
						break;
					case 2:
						p2.addTotal(p2.getRound());
						cout<<"Player 1's Grand Total is: $"<<p1.getTotal()<<endl;
						cout<<"Player 2's Grand Total is: $"<<p2.getTotal()<<endl;
						cout<<"Player 3's Grand Total is: $"<<p3.getTotal()<<endl;
						cout << endl;
						p1.setRound(0);
						p2.setRound(0);
						p3.setRound(0);
						break;
					case 3:
						p3.addTotal(p3.getRound());
						cout<<"Player 1's Grand Total is: $"<<p1.getTotal()<<endl;
						cout<<"Player 2's Grand Total is: $"<<p2.getTotal()<<endl;
						cout<<"Player 3's Grand Total is: $"<<p3.getTotal()<<endl;
						cout << endl;
						p1.setRound(0);
						p2.setRound(0);
						p3.setRound(0);
						break;
				}
				
				
			}
			if(current_player==3)
			{
				current_player=1;
			}
			else
			{
				current_player++;
			}
			
		}
		
	}

	if(p1.getTotal() > p2.getTotal() && p1.getTotal() > p3.getTotal())
	{
		cout<<"Player 1 wins the game and their Grand Total is $"<<p1.getTotal()<<endl;
	}
	else if(p2.getTotal() > p3.getTotal())
	{
		cout<<"Player 2 wins the game and their Grand Total is $"<<p2.getTotal()<<endl;
	}
	else
	{
		cout<<"Player 3 wins the game and their Grand Total is $"<<p3.getTotal()<<endl;
	}
	
	return 0;
}

void printWheel()
{
	cout << "                  ██████████████                  " << endl;
	cout << "              ████▒▒▒▒▓▓▓▓▓▓▒▒▒▒████              " << endl;
	cout << "          ████▒▒▒▒██████▓▓██████▒▒▒▒████          " << endl;
	cout << "        ██▓▓▒▒████    ██▒▒██    ████▒▒▓▓██        " << endl;
	cout << "      ██▓▓████        ██▒▒██        ████▓▓██      " << endl;
	cout << "    ██▓▓██▓▓██        ██▒▒██        ██▓▓██▓▓██    " << endl;
	cout << "    ██▒▒████▒▒██      ██▒▒██      ██▒▒████▒▒██    " << endl;
	cout << "  ██▒▒██    ██▒▒██    ██▒▒██    ██▒▒██    ██▒▒██  " << endl;
	cout << "  ██▒▒██      ██▓▓██  ██▓▓██  ██▓▓██      ██▒▒██  " << endl;
	cout << "██▒▒██          ██▓▓████▒▒████▓▓██          ██▒▒██" << endl;
	cout << "██▒▒██            ██▓▓██▓▓██▓▓██            ██▒▒██" << endl;
	cout << "██▓▓██████████████████▓▓▓▓▓▓██████████████████▓▓██" << endl;
	cout << "██▓▓▓▓▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▓▓▓▓██" << endl;
	cout << "██▓▓██████████████████▓▓▓▓▓▓██████████████████▓▓██" << endl;
	cout << "██▒▒██            ██▓▓██▓▓██▓▓██            ██▒▒██" << endl;
	cout << "██▒▒██          ██▓▓████▓▓████▓▓██          ██▒▒██" << endl;
	cout << "  ██▒▒██      ██▓▓██  ██▒▒██  ██▓▓██      ██▒▒██  " << endl;
	cout << "  ██▒▒██    ██▒▒██    ██▒▒██    ██▒▒██    ██▒▒██  " << endl;
	cout << "    ██▒▒████▒▒██      ██▒▒██      ██▒▒████▒▒██    " << endl;
	cout << "    ██▓▓██▓▓██        ██▒▒██        ██▓▓██▓▓██    " << endl;
	cout << "      ██▓▓████        ██▒▒██        ████▓▓██      " << endl;
	cout << "        ██▓▓▒▒████    ██▒▒██    ████▒▒▓▓██        " << endl;
	cout << "          ████▒▒▒▒██████▓▓██████▒▒▒▒████          " << endl;
	cout << "              ████▒▒▒▒▓▓▓▓▓▓▒▒▒▒████              " << endl;
	cout << "                  ██████████████                  " << endl;

	
}

void printLogo()
{
	cout<<" __          ___               _          __   ______         _                    "<<endl;
	cout<<" \\ \\        / / |             | |        / _| |  ____|       | |                   "<<endl;
	cout<<"  \\ \\  /\\  / /| |__   ___  ___| |   ___ | |_  | |__ ___  _ __| |_ _   _ _ __   ___ "<<endl;
	cout<<"   \\ \\/  \\/ / | '_ \\ / _ \\/ _ \\ |  / _ \\|  _| |  __/ _ \\| '__| __| | | | '_ \\ / _ \\"<<endl;
	cout<<"    \\  /\\  /  | | | |  __/  __/ | | (_) | |   | | | (_) | |  | |_| |_| | | | |  __/"<<endl;
	cout<<"     \\/  \\/   |_| |_|\\___|\\___|_|  \\___/|_|   |_|  \\___/|_|   \\__|\\__,_|_| |_|\\___|"<<endl;
	
}

void printLetters(vector<char>letters)
{
	cout<<"Letters already guessed: ";
	for(int i=0; i<letters.size(); i++)
	{
		cout<<letters[i]<<" ";
	}
	cout<<endl;
}

char isLetter(char letter)
{
	vector<char>allLetters{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','G','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int found=0;
	for(int i=0; i<allLetters.size(); i++)
	{
		if(letter==allLetters[i])
		{
			found=1;
		}
	}
	if(found==0)
	{
		return '!';
	}

	vector<char>vowels{'a','e','i','o','u','A','E','I','O','U'};
	found=0;
	for(int i=0; i<vowels.size(); i++)
	{
		if(letter==vowels[i])
		{
			found=1;
		}
	}
	if(found==1)
	{
		return 'v';
	}
	else
	{
		return 'c';
	}
}