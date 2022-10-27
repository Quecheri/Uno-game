#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>


import <ctime>;
import <cstdlib>;
import <regex>;
import <ranges>;
import <random>;
export import <thread>;
import <chrono>;


import MenuInputTextBox;
import TextBox;
import MenuButton;
import Player;
import WyrzuconeKarty;
import DostepneKarty;
import Connection;


export module Game;

export class Game
{

public:
	Game()
	{
		//inicjalizacja
		Deck = std::make_unique<DostepneKarty>();
		Wyrzucone = std::make_unique<WyrzuconeKarty>();
		CreatePlayers();
		music.openFromFile("Music/fun-life.wav");
		music.play();
		music.setLoop(true);
		music.setVolume(50);
	}
	/// <summary>
	/// Loads menu buttons
	/// </summary>
	void LoadButtons()
	{
		//Start
		InteractableObjects.emplace_back(std::make_unique<MenuButton>("images/Rescaled/Start.png", 0, 1));
		//quit
		InteractableObjects.emplace_back(std::make_unique<MenuButton>("images/Rescaled/Quit.png", 4, 0));
		//Connect
		InteractableObjects.emplace_back(std::make_unique<MenuButton>("images/Rescaled/Connect.png", 2, 3));
		//Serwer
		InteractableObjects.emplace_back(std::make_unique<MenuButton>("images/Rescaled/StartSerwer.png", 3, 2));
		//Options
		InteractableObjects.emplace_back(std::make_unique<MenuButton>("images/Rescaled/Options.png", 1, 4));
		//Back
		InteractableObjects.emplace_back(std::make_unique<MenuButton>("images/Rescaled/Back.png", 5, 5));
		//Play
		InteractableObjects.emplace_back(std::make_unique<MenuButton>("images/Rescaled/Play.png", 0, 6));
		//KoniecTury
		InteractableObjects.emplace_back(std::make_unique<MenuButton>("images/Rescaled/Accept.png", 7, 91));
		//TextBox
		InteractableObjects.emplace_back(std::make_unique<MenuInputTextBox>("images/Rescaled/TextBox.png", 4, 21, "127.0.0.1", 20, 20));
		InteractableObjects.emplace_back(std::make_unique<MenuInputTextBox>("images/Rescaled/TextBox.png", 4, 23, RandomizeStartingSeed(), 20, 20));
		InteractableObjects.emplace_back(std::make_unique<MenuInputTextBox>("images/Rescaled/TextBox.png", 2, 22, "Janusz", 20, 20));
		//Przycisk akceptacji i odrzucenia
		InteractableObjects.emplace_back(std::make_unique<MenuButton>("images/Rescaled/Subtract.png", 6, 11));
		InteractableObjects.emplace_back(std::make_unique<MenuButton>("images/Rescaled/Add.png", 7, 12));
		InteractableObjects.emplace_back(std::make_unique<MenuButton>("images/Rescaled/RulesSmall.png", 7, 13));

		NonInteractableObjects.emplace_back(std::make_unique<TextBox>("Enter your name: ", 1, 51, 10, 15));
		NonInteractableObjects.emplace_back(std::make_unique<TextBox>("Enter Ip Adress: ", 3, 52, 10, 15));
		NonInteractableObjects.emplace_back(std::make_unique<TextBox>("Enter seed: ", 3, 53, 30, 15));
		NonInteractableObjects.emplace_back(std::make_unique<TextBox>("Wprowadz dane",13,54));
		NonInteractableObjects.emplace_back(std::make_unique<TextBox>("Volume",1,55,60,30));
		NonInteractableObjects.emplace_back(std::make_unique<NotInteractableObject>("images/Rescaled/SoundBar.png",2,60));
		
	}
	/// <summary>
	/// Create players
	/// </summary>
	void CreatePlayers()
	{
		PlayerList.push_back(std::make_unique<Player>(1, true, "PC1"));
		PlayerList.push_back(std::make_unique<Player>(2, true, "PC2"));
		PlayerList.push_back(std::make_unique<Player>(3, true, "PC3"));
		PlayerList.push_back(std::make_unique<Player>(4, true, "PC4"));
	}
	/// <summary>
	/// Sets starting state of players
	/// </summary>
	void ClearPlayers()
	{
		PlayerList[0]->SetName("PC1");
		PlayerList[1]->SetName("PC2");
		PlayerList[2]->SetName("PC3");
		PlayerList[3]->SetName("PC4");
		PlayerList[0]->SetPC(true);
		PlayerList[1]->SetPC(true);
		PlayerList[2]->SetPC(true);
		PlayerList[3]->SetPC(true);
	}
	/// <summary>
	/// returns random number in string
	/// </summary>
	/// <returns></returns>
	inline std::string RandomizeStartingSeed()
	{
		std::mt19937 gen(time(nullptr));
		int res = gen();
		return std::to_string(std::abs(res));
	}
	/// <summary>
	/// zwraca Index Obiektu w wektorze obiektów
	/// </summary>
	/// <param name="MenuPosition"></param>
	/// <returns></returns>
	int GetObjectOnPosition(int& MenuPosition)
	{
		if (MenuPosition < 0)return -1;
		for (int i = 0; i < InteractableObjects.size(); i++)
			if (InteractableObjects[i]->IndexPosition == MenuPosition && InteractableObjects[i]->IsVisible)return i;
		return -1;
	}
	/// <summary>
	/// Zwraca Index pozycji w menu
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	int GetPositionInMenu(const sf::Vector2i& pos)
	{
		
		if (pos.x >= 450 && pos.x <= 680)//Mid Menu
		{
			if (pos.y >= 100 && pos.y <= 180)return 0;
			if (pos.y >= 190 && pos.y <= 270)return 1;
			if (pos.y >= 280 && pos.y <= 360)return 2;
			if (pos.y >= 370 && pos.y <= 450)return 3;
			if (pos.y >= 460 && pos.y <= 540)return 4;
			if (pos.y >= 550 && pos.y <= 630)return 5;
			return -1;
		}
		else if (pos.y >= 280 && pos.y <= 360)
		{
			if (pos.x >= 350 && pos.x <= 450)return 6;
			if (pos.x >= 690 && pos.x <= 790)return 7;
			return -1;
		}
		else return -1;
	}
	/// <summary>
	/// Changes hoovered object
	/// </summary>
	/// <param name="pos"></param>
	void CheckHoovered(sf::Vector2i pos)
	{
		int pom = GetPositionInMenu(sf::Mouse::getPosition(window));
		CurentHovered = GetObjectOnPosition(pom);
	}
	/// <summary>
	/// SetActiveObject, Deactivate others
	/// </summary>
	/// <param name="pos"></param>
	void SetActive(int pos)
	{
		int location = GetObjectOnPosition(pos);
		for (int i = 0; i < InteractableObjects.size(); i++)
			if (i == location)
			{
				InteractableObjects[i]->Active(true);
				InteractableObjects[i]->ObjectSprite.setColor(sf::Color::Green);
			}
			else
			{
				InteractableObjects[i]->Active(false);

			}
	}
	/// <summary>
	/// Deactivate button on position
	/// </summary>
	/// <param name="pos"></param>
	void DeactivateButton(int pos)
	{
		int location = GetObjectOnPosition(pos);
		if (location > -1)
			if (InteractableObjects[location]->isButton())
				InteractableObjects[location]->Active(false);

	}
	/// <summary>
	/// Checks wheter Text box is active
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	bool TextBoxIsActive(int& pos)
	{
		for (int i = 0; i < InteractableObjects.size(); ++i)
			if (InteractableObjects[i]->IsActive && InteractableObjects[i]->isText())
			{
				pos = i;
				return true;
			}
		return false;
	}
	/// <summary>
	/// Changes scene in menu
	/// </summary>
	/// <param name="ID"></param>
	void ChangeScene(int ID)
	{
		switch (ID)
		{
		case 0://quit
		{
			window.close();
			break;
		}
		case 1://Gra
		{
			for (auto& el : InteractableObjects)
			{
				el->IsVisible = false;

			}
			for (auto& el : NonInteractableObjects)
			{
				el->IsVisible = false;
			}

			SetStatus(0);
			BeginSingleplayerGame("gracz");
			break;
		}
		case 2://serwer
		{
			for (auto& el : InteractableObjects)
				if (el->GetID() == 22 || el->GetID() == 23 || el->GetID() == 5 || el->GetID() == 6)
					el->IsVisible = true;
				else
					el->IsVisible = false;
			for (auto& el : NonInteractableObjects)
				if (el->GetID() == 51 || el->GetID() == 53 || el->GetID() == 54)
					el->IsVisible = true;
				else
					el->IsVisible = false;
			break;
		}
		case 3://connect
		{
			for (auto& el : InteractableObjects)
				if (el->GetID() == 5 || el->GetID() == 21 || el->GetID() == 22 || el->GetID() == 6)
					el->IsVisible = true;
				else
					el->IsVisible = false;
			for (auto& el : NonInteractableObjects)
				if (el->GetID() == 51 || el->GetID() == 52 || el->GetID() == 54)
					el->IsVisible = true;
				else
					el->IsVisible = false;

			break;
		}
		case 4://opcje
		{
			for (auto& el : InteractableObjects)
				if (el->GetID() == 5 || el->GetID() == 11 || el->GetID() == 12)
					el->IsVisible = true;
				else
					el->IsVisible = false;
			for (auto& el : NonInteractableObjects)
			{
				if (el->GetID() == 55)
					el->IsVisible = true;
				else if (el->GetID() == 60)
				{
					el->IsVisible = true;
					el->ObjectSprite.setTextureRect(sf::IntRect(0, (music.getVolume() / 10.0) * 80, 240, 80));
				}
				else
					el->IsVisible = false;
			}
			break;
		}
		case 5://Scena Podstawowa
		{
			for (auto& el : InteractableObjects)
				if (el->GetID() == 1 || el->GetID() == 0 || el->GetID() == 3 || el->GetID() == 4 || el->GetID() == 2|| el->GetID() == 13)
					el->IsVisible = true;
				else
					el->IsVisible = false;
			for (auto& el : NonInteractableObjects)
				el->IsVisible = false;
			break;
		}
		case 6://Play
		{
			bool server = false;
			bool IsGood = true;
			std::string seedOrIp;
			std::string name;
			for (auto& el : InteractableObjects)
			{
				if (el->GetID() == 23 && el->IsVisible)
				{
					seedOrIp = el->text.getString();
					server = true;
					if (!IsNumber(seedOrIp))
					{
						IsGood = false;
						break;
					}

				}
				else if (el->GetID() == 22 && el->IsVisible)
				{
					name = el->text.getString();
				}

				else if (el->GetID() == 21 && el->IsVisible)
				{
					seedOrIp = el->text.getString();
					std::regex ValidIpAddressRegex("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");
					if (!std::regex_match(seedOrIp, ValidIpAddressRegex))
					{

						IsGood = false;
						break;
					}
				}

			}
			if (IsGood)
			{
				for (auto& el : NonInteractableObjects)
					if (el->GetID() == 54) {
						el->text.setString("Connecting...");
						el->text.setFillColor(sf::Color::Green);
					}
				if (InicjalizeConnection(server, seedOrIp, name) == true)
				{
					for (auto& el : InteractableObjects)
						el->IsVisible = false;

					for (auto& el : NonInteractableObjects)
						el->IsVisible = false;
					SetStatus(0);
					online = true;
					StartGameLoop();
					ChangeScene(5);

				}
				else for (auto& el : NonInteractableObjects)
					if (el->GetID() == 54) {
						el->text.setString("Connecting error");
						el->text.setFillColor(sf::Color::Red);
					}
			}
			else
			{
				for (auto& el : NonInteractableObjects)
					if (el->GetID() == 54) {
					el->text.setString("Wrong input");
					el->text.setFillColor(sf::Color::Red);
				
					}
			}
			break;


		}
		case 11:
		{
			float volume = music.getVolume();
			if (volume > 10)
				music.setVolume(volume - 10.0);
			else
				music.setVolume(0);

			for (auto& el : NonInteractableObjects)
				if (el->GetID() == 60)
					el->ObjectSprite.setTextureRect(sf::IntRect(0, (music.getVolume() / 10.0) * 80, 240, 80));
			
			break;
		}
		case 12:
		{
			float volume = music.getVolume();
			if (volume < 90)
				music.setVolume(volume + 10.0);
			else
				music.setVolume(100);
			for (auto& el : NonInteractableObjects)
				if (el->GetID() == 60)
					el->ObjectSprite.setTextureRect(sf::IntRect(0, (music.getVolume() / 10.0) * 80, 240, 80));
			
			break;
		}
		case 13:
		{
			bool input = false;
			std::string Zasady= "Aby wyjsc wcisnij dowolny przycisk!\n\n\n";
			TextBox RulesBox(Zasady, 1, 66, -400, -100);
			Zasady += "1.Wygrywasz gre, pozbywajac sie wszystkich kart.\n";
			Zasady += "2.Mozesz rzucic karte jezeli jest tego samego koloru co ostatnio rzucona.\n";
			Zasady += "3.Mozesz rzucic karte jezeli jest tej samej figury.\n";
			Zasady += "4.Mozesz rzucic dowolna ilosc tych samych(figura/numer) kart jednoczesnie.\n";
			Zasady += "5.Karta +2 zmusza nastepnego gracza do pociagniecia 2 kart.\n";
			Zasady += "6.Karta +4 zmusza nastepnego gracza do pociagniecia 4 kart.\n";
			Zasady += "7.Karta <-/-> odwraca kolejke.\n";
			Zasady += "8.Karta 'Color' Zmienia kolor.\n";
			Zasady += "9.Karta 'Block' Zmusza gracza do pominiecia kolejki.\n";
			Zasady += "10.Karty 0-9 sa neutralne.\n";
			Zasady += "11.Mozesz odbic karte +2/+4/Block rzucajac ta sama karte.\n";
			Zasady += "12.Odbicie karty +2/+4 sumuje ich efekt.\n";
			RulesBox.text.setString(Zasady);
			window.clear();
			window.draw(RulesBox.text);
			window.display();
			while (!input)
			{
				sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
					if (event.type == sf::Event::TextEntered)
						input = true;
					if (event.type == sf::Event::MouseButtonReleased)
						input = true;
				}	
				
			}
		}
		}
	}
	/// <summary>
	/// Colors hovered object
	/// </summary>
	void ColorObjects()
	{
		for (int i = 0; i < InteractableObjects.size(); i++)
		{
			if (!InteractableObjects[i]->IsActive && InteractableObjects[i]->IsVisible)
				if (i == CurentHovered)
					InteractableObjects[i]->ObjectSprite.setColor(sf::Color::Cyan);
				else
					InteractableObjects[i]->ObjectSprite.setColor(sf::Color::White);
		}
	}
	/// <summary>
	/// Start GUI, Sets variables
	/// </summary>
	void StartGUI()
	{
		bool Pressed = false;
		int PressedPosition = -2;
		float windowHeight = 800;
		float windowWidth = 1200;

		window.create(sf::VideoMode(windowWidth, windowHeight), "Uno!",sf::Style::Titlebar|sf::Style::Close);
		window.setFramerateLimit(120);
		NotInteractableObject MenuBkg("images/Rescaled/MenuBkg.png", 100, 100);
		LoadButtons();
		ChangeScene(5);
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::MouseButtonPressed)
				{
					Pressed = true;
					int pom = GetPositionInMenu(sf::Mouse::getPosition(window));
					if (pom > -1)
					{
						PressedPosition = pom;
						SetActive(PressedPosition);
					}
				}
				if (event.type == sf::Event::MouseButtonReleased)
				{

					Pressed = false;
					DeactivateButton(PressedPosition);
					int pom = GetPositionInMenu(sf::Mouse::getPosition(window));

					if (pom == PressedPosition)
					{
						pom = GetObjectOnPosition(pom);
						if (pom > -1)
						{
							if (InteractableObjects[pom]->isButton())
								ChangeScene(InteractableObjects[pom]->GetID());
						}
					}
				}
				if (event.type == sf::Event::MouseMoved)
				{
					if (!Pressed)
					{
						CheckHoovered(sf::Mouse::getPosition(window));
					}
				}
				if (event.type == sf::Event::TextEntered)
				{
					int pom;
					if (TextBoxIsActive(pom))
					{
						InteractableObjects[pom]->EneteredFromKeyBoard(event.text.unicode);
					}
				}
			}
			window.clear();
			window.draw(MenuBkg.ObjectSprite);
			ColorObjects();
			for (auto& el : InteractableObjects)
			{
				if (el->IsVisible)
				{
					window.draw(el->ObjectSprite);
					if (el->isText())window.draw(el->text);
				}
			}
			for (auto& el : NonInteractableObjects)
			{
				if(el-> GetID()==60 && el->IsVisible)window.draw(el->ObjectSprite);
				if (el->IsVisible)window.draw(el->text);
			}
			window.display();
		}
	}
	/// <summary>
	/// Load cards, sets IsLoaded to true after positive loading
	/// </summary>
	void GenerateCards()
	{
		Deck->GenerateDeck();
		IsLoaded = true;
	}
	/// <summary>
	///Deals the cards to players
	/// </summary>
	void DealTheCards()
	{
		for (int i = 0; i < 7; i++)
		{
			PlayerList[0]->DrawOne(move(Deck->DrawFromDeck()));
			PlayerList[1]->DrawOne(move(Deck->DrawFromDeck()));
			PlayerList[2]->DrawOne(move(Deck->DrawFromDeck()));
			PlayerList[3]->DrawOne(move(Deck->DrawFromDeck()));
		}
		//pierwsza karta
		do
		{
			Wyrzucone->getCollection()->push_back(move(Deck->DrawFromDeck()));
		} while (Wyrzucone->getCollection()->back()->isNormal() == false);

	}
	/// <summary>
	/// Draw n card from deck to player hand
	/// </summary>
	/// <param name="n"></param>
	/// <returns></returns>
	int PlayerDraw(int n)
	{
		if (!Deck->isEmpty())
		{
			int id = Deck->getCollection()->back()->getID();
			for (int i = 0; i < n; i++)
			{
				PlayerList[CurrentPlayer]->DrawOne(move(Deck->DrawFromDeck()));
				if (Deck->isEmpty()) {
					Deck->Reshuffle(Wyrzucone->getCollection(), GenerateFromSeed());
					Wyrzucone->ClearPilleAfterReshuffle();
				}
			}
			return id;
		}
		else
		{
			
			return -1;
		}
	}
	/// <summary>
	/// Returns Color in string
	/// </summary>
	/// <param name="ColorNumber"></param>
	/// <returns></returns>
	std::string getColorInText(int ColorNumber) {
		switch (ColorNumber)
		{
		case 0:	return "Red";
		case 1:	return "Green";
		case 2:	return "Blue";
		case 3:	return "Yellow";
		default:return "Black";
		}
	}
	/// <summary>
	/// Return number in string
	/// </summary>
	/// <param name="Number"></param>
	/// <returns></returns>
	std::string getNumberInText(int Number) {

		switch (Number)
		{
		case 10:	return "Stop";
		case 11:	return "Reverse";
		case 12:	return "Draw 2";
		case 13:	return "Draw 4";
		case 14:	return "Change Color";
		default:	return std::to_string(Number);
		}
	}
	/// <summary>
	/// Returns gamestate
	/// </summary>
	/// <returns></returns>
	int CheckGameStatus()
	{
		return GameStatus;
	}
	/// <summary>
	/// Return PlayerList
	/// </summary>
	/// <returns></returns>
	std::vector<std::unique_ptr<Player>>* getPlayerList() { return &PlayerList; }
	/// <summary>
	/// Changes current player Either++ or -- depending on Reversed bool.
	/// </summary>
	void NextPlayer() {
		if (!Reversed)CurrentPlayer++;
		else CurrentPlayer--;
		if (CurrentPlayer == 4)CurrentPlayer = 0;
		else if (CurrentPlayer == -1)CurrentPlayer = 3;

		
	}
	/// <summary>
	/// Thorws card. Process card action before throwing
	/// </summary>
	/// <param name="CardInHandLocation"></param>
	void Throw(int CardInHandLocation)
	{
		ProcessCardAction(PlayerList[CurrentPlayer]->getHand()->getCardNumber(CardInHandLocation));

		Wyrzucone->getCollection()->push_back(move(PlayerList[CurrentPlayer]->getHand()->getCard(CardInHandLocation)));
		PlayerList[CurrentPlayer]->getHand()->EfficientRemove(CardInHandLocation);
		if (PlayerList[CurrentPlayer]->getHand()->GetSize() == 0)GameStatus = 9;
	}
	/// <summary>
	/// Checks wheter string is a number
	/// </summary>
	/// <param name="s"></param>
	/// <returns></returns>
	bool IsNumber(const std::string& s)
	{
		std::string::const_iterator it = s.begin();
		while (it != s.end() && std::isdigit(*it)) ++it;
		return !s.empty() && it == s.end();
	}
	/// <summary>
	/// Reset Current seed number
	/// </summary>
	void ClearSeedCounter()
	{
		CurrentSeedNumber = 0;
	}
	/// <summary>
	/// Takes single int from seed
	/// </summary>
	/// <returns></returns>
	int GenerateFromSeed()
	{
		int iseed = seed[CurrentSeedNumber] - '0';
		CurrentSeedNumber++;
		if (CurrentSeedNumber = seed.length())CurrentSeedNumber = 0;
		return iseed;
	}

	/*0:"Red";
	1:"Green";
	2:"Blue";
	3:"Yellow";*/

	/// <summary>
	/// Lets player choose a color
	/// </summary>
	/// <param name="color"></param>
	void GraczWybieraKolor(int color)
	{
		MoveCode += "C";
		if (color == 1)
		{
			MoveCode += "1;";
			CurrentColor = 1;

		}
		else if (color == 2)
		{
			MoveCode += "2;";
			CurrentColor = 2;
		}
		else if (color == 3)
		{
			MoveCode += "0;";
			CurrentColor = 0;
		}
		else if (color == 4)
		{
			MoveCode += "3;";
			CurrentColor = 3;
		}
	}
	/// <summary>
	/// returns a player object
	/// </summary>
	/// <returns></returns>
	Player* GetPlayer() { return PlayerList[CurrentPlayer].get(); }
	/// <summary>
	/// Process action associated with card
	/// </summary>
	/// <param name="cardNumber"></param>
	void ProcessCardAction(int cardNumber)//po rzucie akcje
	{
		//<10 normalne
		if (cardNumber == 10)
		{
			ChangeEventFlag(true);
			SetStatus(2);
		}//Stop
		else if (cardNumber == 11) {
			Reversed = !Reversed;
			SetStatus(0);
		}//reverse
		else if (cardNumber == 12) {
			ChangeEventFlag(true);
			if (CurrentCombo == 1)CurrentCombo = 2;
			else CurrentCombo += 2;
			SetStatus(1);
		}//+2
		else if (cardNumber == 13) {
			SetStatus(4);
			ChangeEventFlag(true);
			if (CurrentCombo == 1)CurrentCombo = 4;
			else CurrentCombo += 4;

			if (PlayerList[CurrentPlayer]->IsPC())
			{
				CurrentColor = PlayerList[CurrentPlayer]->GetFavouriteColor();
				SetStatus(1);
			}
			else if (!PlayerList[CurrentPlayer]->GetLocalPlayer())
			{
				SetStatus(1);
				CurrentColor = NewCurrentColor;
			}

		}//+4
		else if (cardNumber == 14) {
			SetStatus(3);
			if (PlayerList[CurrentPlayer]->IsPC())
			{
				CurrentColor = PlayerList[CurrentPlayer]->GetFavouriteColor();
				SetStatus(0);
			}
			else if (!PlayerList[CurrentPlayer]->GetLocalPlayer())
			{
				CurrentColor = NewCurrentColor;
				SetStatus(0);
			}

		}//color
	}
	/// <summary>
	/// sets event flag
	/// </summary>
	/// <param name="ev"></param>
	void ChangeEventFlag(bool EventFlag) { Event = EventFlag; }
	/// <summary>
    /// swaps reversed flag
    /// </summary>
	void ChangeReverseFlag() { Reversed = !Reversed; }

	/// <summary>
	/// returns current combo number
	/// </summary>
	/// <returns>int current combo</returns>
	int GetCurrentCombo() { return CurrentCombo; }
	/// <summary>
	/// Adds number to currentcombo
	/// </summary>
	/// <param name="Number"></param>
	void IncreaseCurrentCombo(int& Number) { CurrentCombo += Number; }
	/// <summary>
	/// set current combo to 1
	/// </summary>
	void ResetCurrentCombo() { CurrentCombo = 1; }
	/// <summary>
	/// AI throw card
	/// </summary>
	void PCThrow()
	{
		CardsToThrow.push_back(GetPlayer()->GetChosenCardId());
		std::vector<int> temp;
		PlayerList[CurrentPlayer]->SearchForMore(temp, GetPlayer()->getHand()->getCardNumber(CardsToThrow[CardsToThrow.size() - 1]));
		for (int i = 0; i < temp.size(); ++i)
		{
			if (CardsToThrow[0] != temp[i])CardsToThrow.push_back(temp[i]);
		}

	}
	/// <summary>
	/// Loads Current top card values
	/// </summary>
	void UpdateTopCard()
	{
		CurrentCard = Wyrzucone.get()->getCollection()->back()->getNumber();
		if (Wyrzucone.get()->getCollection()->back()->getColor() != 4)CurrentColor = Wyrzucone.get()->getCollection()->back()->getColor();
	}
	/// <summary>
	/// gets next player
	/// </summary>
	/// <returns>Int nexplayer id</returns>
	int GetNextPlayer()
	{
		if (!Reversed)
		{
			if (CurrentPlayer == 3)return 0;
			else return CurrentPlayer + 1;
		}
		else {
			if (CurrentPlayer == 0)return 3;
			else return CurrentPlayer - 1;
		}
	}
	/// <summary>
/// gets last player
/// </summary>
/// <returns>Int Lastplayer id</returns>
	int GetBeforePlayer()
	{
		if (Reversed)
		{
			if (CurrentPlayer == 3)return 0;
			else return CurrentPlayer + 1;
		}
		else {
			if (CurrentPlayer == 0)return 3;
			else return CurrentPlayer - 1;
		}
	}
	/// <summary>
	/// Sets game status
	/// </summary>
	/// <param name="NewStatus"></param>
	void SetStatus(int NewStatus)
	{
		GameStatus = NewStatus;
	}
	/// <summary>
	/// Cheks wheter card i eligable to play
	/// </summary>
	/// <param name="CardId"></param>
	/// <returns></returns>
	bool isEligable(int CardId)
	{
		int offset = CardId % 16;
		int cardNumber = (CardId - offset) / 16;
		if (!Event)
		{
			if (cardNumber == CurrentCard || offset == CurrentColor || offset == 4)
			{
				return true;
			}
			return false;
		}
		else if (Event)
		{
			if (GameStatus == 2 && (CardId - offset) / 16 == 10)return true;
			else if (GameStatus == 1)
			{
				if (CurrentCard == 12)//+2
				{
					if (cardNumber == 12 || cardNumber == 13)return true;
				}
				else if (CurrentCard == 13 && cardNumber == 13)return true;
			}
		}
		return false;
	}
	/// <summary>
	/// Prepares card for draw animation
	/// </summary>
	/// <param name="CardInHandPos"></param>
	void PreDraw(int CardInHandPos)///
	{
		PlayerList[CurrentPlayer]->getHand()->getCollection()->at(CardInHandPos)->ThisCardSprite->ObjectSprite.setRotation(0);
		PlayerList[CurrentPlayer]->getHand()->getCollection()->at(CardInHandPos)->ThisCardSprite->ObjectSprite.setPosition(650, 300);
	}
	/// <summary>
	/// Process Ai move
	/// </summary>
	void AIMove()
	{

		for (int i = 0; i < GetPlayer()->getHand()->GetSize(); i++)
		{
			GetPlayer()->CalculateAiMove(i, GameStatus, CurrentCard, CurrentColor, PlayerList[GetNextPlayer()].get(), PlayerList[GetBeforePlayer()].get());
		}
		if (GetPlayer()->GetChosenCardValue() < 0)
		{
			if (GameStatus == 2)
			{
				SetStatus(0);
				ChangeEventFlag(false);
			}
			else {


				if (GetCurrentCombo() > 1)
				{
					if (isEligable(PlayerDraw(1)))
					{
						SetStatus(0);
						ChangeEventFlag(false);
					
						CardsToDraw.push_back(PlayerList[CurrentPlayer]->GetHandSize() - 1);
						//Throw(GetPlayer()->getHand()->GetSize() - 1);
						CardsToThrow.push_back(GetPlayer()->getHand()->GetSize() - 1);
					}
					else
					{
						SetStatus(0);
						ChangeEventFlag(false);
						
						for (int i = 0; i < GetCurrentCombo() - 1; i++)
						{
							PlayerDraw(1);
							CardsToDraw.push_back(PlayerList[CurrentPlayer]->GetHandSize() - 1);
						}
						ResetCurrentCombo();

					}
				}
				else
				{
					PlayerDraw(1);
					SetStatus(0);
					ChangeEventFlag(false);
					CardsToDraw.push_back(PlayerList[CurrentPlayer]->GetHandSize() - 1);
				}

			}
		}
		else {
			PCThrow();
		}


	}
	/// <summary>
	/// Process Recived Move code from external source
	/// </summary>
	/// <param name="moveCode"></param>
	void ProcessRecivedMove(std::string moveCode)
	{
		std::regex wzor("([A-Z]{1}\\d)");
		std::string Code;
		auto words_begin = std::sregex_iterator(moveCode.begin(), moveCode.end(), wzor);
		auto words_end = std::sregex_iterator();
		for (std::sregex_iterator i = words_begin; i != words_end; i++)
		{
			std::smatch match = *i;
			Code = match.str();

			switch (Code[0])
			{
			case 'T':
			{
				CardsToThrow.push_back(Code[1] - '0');
				break;
			}
			case 'D':
			{
				PlayerDraw(Code[1] - '0');
				CardsToDraw.push_back(PlayerList[CurrentPlayer]->GetHandSize() - 1);
			
				break;
			}
			case 'E':
			{
				if (Code[1] == '0')ChangeEventFlag(false);
				else if (Code[1] == '1')ChangeEventFlag(true);
				break;
			}
			case 'R':
			{
				if (Code[1] == '0')ResetCurrentCombo();
				break;
			}
			case 'B':
			{
				if (Code[1] == '1')
				break;
			}
			case 'C':
			{

				if (Code[1] == '0')NewCurrentColor = 0;
				else if (Code[1] == '1')NewCurrentColor = 1;
				else if (Code[1] == '2')NewCurrentColor = 2;
				else if (Code[1] == '3')NewCurrentColor = 3;
				break;
			}
			case 'S':
			{
				if (Code[1] == '1')SetStatus(1);
				if (Code[1] == '0')SetStatus(0);
				break;
			}

			}
		}
	}
	/// <summary>
	/// Inicjalize online conneciton
	/// </summary>
	/// <param name="Option"></param>
	/// <param name="SeedOrIP"></param>
	/// <param name="name"></param>
	/// <returns>True if alright</returns>
	bool InicjalizeConnection(int Option, std::string SeedOrIP, std::string name)
	{
		while (!IsLoaded)
		{
			
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
		ClearSeedCounter();
		ClearPlayers();
		Deck->RestartDeck();
		if (Option == 1)
		{
			
			std::string gameSeed = SeedOrIP;
			connection.OpenServerConnection();
			std::string Concatenated = gameSeed + "$" + name;
			if (connection.SendString(Concatenated) == -1)return false;
			std::string ClientName = connection.LoadGameRules();
			seed = gameSeed;
			int offset = ((gameSeed[1] - '0') % 4);
			int pos = (gameSeed[0] - '0') % 4;
			if (offset == 0)offset++;
			for (int i = 0; i < ClientName.length(); i++)
			{
				if (ClientName[i] == '$')
					ClientName = ClientName.substr(0,i);
				
			}
			PlayerList[pos]->SetPC(false);//Pierwszy gracz
			PlayerList[pos]->IsLocalPlayer();//Pierwszy gracz
			localPlayer = pos;
			PlayerList[pos]->SetName(name);//Pierwszy gracz
			for (int i = 0; i < offset; i++)
			{
				pos++;
				if (pos == 4)pos = 0;
			}
			PlayerList[pos]->SetPC(false);//Drugi gracz
			PlayerList[pos]->SetName(ClientName);//Drugi gracz

			return true;
		}
		else if (Option == 0)
		{
			connection.ClientConnect(SeedOrIP);
			std::string gameSeed="";
			std::string ServName="";
			int CharNum = 0;
			std::string message= connection.LoadGameRules();
			for (int i = 0; i < message.length(); i++)
			{
				if (message[i] == '$')
				{
					if (gameSeed.length() == 0)
					{
						gameSeed = message.substr(CharNum, i - CharNum);
						CharNum = i+1;

					}
					else
					{
						ServName = message.substr(CharNum, i-CharNum);
						CharNum = i + 1;
						break;
					}
				}
			}
			if (connection.SendString(name) == -1)return false;
			if (gameSeed == "ex1")return false;
			seed = gameSeed;
			int offset = (gameSeed[1] - '0') % 4;
			int pos = (gameSeed[0] - '0') % 4;
			if (offset == 0)offset++;
			PlayerList[pos]->SetPC(false);//Pierwszy gracz
			PlayerList[pos]->SetName(ServName);
			for (int i = 0; i < offset; i++)
			{
				pos++;
				if (pos == 4)pos = 0;
			}
			PlayerList[pos]->IsLocalPlayer();//Drugi gracz
			localPlayer = pos;
			PlayerList[pos]->SetPC(false);//Drugi gracz
			PlayerList[pos]->SetName(name);//Drugi gracz
			return true;
		}

	}
	/// <summary>
	/// Sets up hands on correct positions
	/// </summary>
	/// <param name="StartingPosition"></param>
	void SetUpHandDraw(int StartingPosition)
	{

		if (StartingPosition > 3 || StartingPosition < 0)StartingPosition = 0;
		for (int i = 0; i < 4; i++)
		{
			PlayerList[StartingPosition]->getHand()->PositionHand(i, PlayerList[StartingPosition]->GetHandSize());
			StartingPosition++;
			if (StartingPosition == 4)StartingPosition = 0;

		}

	}
	/// <summary>
	/// Clears board and hands after game
	/// </summary>
	void ClearOldBoard()
	{
		Deck->ReturnCards(PlayerList[0]->getHand()->getCollection());
		PlayerList[0]->getHand()->ClearHand();
		Deck->ReturnCards(PlayerList[1]->getHand()->getCollection());
		Deck->ReturnCards(PlayerList[2]->getHand()->getCollection());
		Deck->ReturnCards(PlayerList[3]->getHand()->getCollection());
		Deck->ReturnCards(Wyrzucone->getCollection());
		PlayerList[1]->getHand()->ClearHand();
		PlayerList[2]->getHand()->ClearHand();
		PlayerList[3]->getHand()->ClearHand();
		Wyrzucone->ClearWholePille();
		if (online)
		{
			online = false;
			connection.ShutDown();
		}
		CurrentCombo = 1;
		connection.ClearBuffer();
		ChangeEventFlag(false);
		Reversed=false;
		SetStatus(0);
	}
	/// <summary>
	/// Starts gameloop
	/// </summary>
	void StartGameLoop()
	{

		ChangeEventFlag(false);
		while (!IsLoaded)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
		CurrentPlayer = 0;
		if (!Wyrzucone->isEmpty())ClearOldBoard();
		Deck->RandomizeStartingPostions(seed);
		Deck->PerfectShuffle(GenerateFromSeed());
		
		DealTheCards();
		std::vector<int>ListaKart;
		sf::Event event;

		SetUpHandDraw(localPlayer);
		Deck->SetDeckPosition(650, 300);
		Wyrzucone->SetPillePosition(450, 300);
		MenuButton EndButton("images/Rescaled/EndTurn.png", 9, 91);
		MenuButton ColorPopUp("images/Rescaled/ColorPopUpH.png", 10, 92);
		MenuButton CColor("images/Rescaled/CurentColor.png", 11, 92);
		TextBox Ending("Wygral gracz: ", 2, 100, -200, 0);
		TextBox EndingTimer("Koniec za: ", 2, 100, -100, 100);
		NotInteractableObject GameBkg("images/Rescaled/GameBkg.png", 100, 100);
		NotInteractableObject ActivePlayer("images/Rescaled/arrow.png",12,12);
		ActivePlayer.ObjectSprite.setOrigin(54, 63);
		ActivePlayer.ObjectSprite.setScale(0.5, 0.5);
		

		Ending.text.setScale(2, 2);
		EndButton.ObjectSprite.setTextureRect(sf::IntRect(0, 0, 200, 52));
		ColorPopUp.ObjectSprite.setTextureRect(sf::IntRect(0, 0, 400, 400));
		CColor.ObjectSprite.setTextureRect(sf::IntRect(0, 0, 30, 120));
		EndButton.IsVisible = true;
		bool stickToMouse = false;
		bool Setup = true;
		bool NotYetMoved = true;
		bool WyrzuconoKarte = false;
		bool CardDrawn = false;
		bool DeckActive = false;
		bool ComsRecived = false;
		int touchedCard = -1;
		int PlayerThrowCardNum = -1;
		std::vector<int>TouchedCards;
		std::jthread TimerThread(&Game::BackgroundClock,this);
		std::jthread ComsThread(&Connection::MonitorCommunication, &connection);
		while (window.isOpen() && GameStatus != 10)
		{

			UpdateTopCard();
			CColor.ObjectSprite.setTextureRect(sf::IntRect(CurrentColor * 30, 0, 30, 120));
			
			if (GetPlayer()->IsPC())//PC
			{
				if (PauseTimeElapsed)
				{
					if (NotYetMoved)
					{
						NotYetMoved = false;
						AIMove();
						SetUpHandDraw(localPlayer);
						for (int i = 0; i < CardsToDraw.size(); ++i)
							PreDraw(CardsToDraw[i]);
						
					}
					if (CardsToThrow.size() == 0 && CardsToDraw.size() == 0)
					{
						UpdateTopCard();
						SetUpHandDraw(localPlayer);
						Deck->SetDeckPosition(650, 300);
						Wyrzucone->SetPillePosition(450, 300);
						if (GameStatus == 9)SetStatus(10);
						else
						{
							StartTimer(500);
							NextPlayer();
						}
						NotYetMoved = true;
					}
				}
			}
			else if (GetPlayer()->GetLocalPlayer())//gracz
			{
				if (NotYetMoved)
				{
					MoveCode = "";
					NotYetMoved = false;
				}
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
					if (event.type == sf::Event::MouseButtonPressed)
					{

						sf::Vector2i pom = sf::Mouse::getPosition(window);
						if (GameStatus == 0 || GameStatus == 2 || GameStatus == 1)
						{

							if (pom.y >= 600 && pom.y <= 720)
							{

								touchedCard = PlayerList[localPlayer]->getHand()->FindTouchedCard(pom);
								if (touchedCard > -1)
								{
									PlayerList[localPlayer]->getHand()->RepositionOnMouse(pom, touchedCard);
									stickToMouse = true;

								}
							}

						}
						if (GameStatus == 0 || GameStatus == 1)
							if (!CardDrawn)
							{
								if (pom.y >= 300 && pom.y <= 420 && pom.x >= 650 && pom.x <= 730)//Próba ci¹gniêcia
								{
									if (Deck->getCollection()->size() > 0)
										DeckActive = true;

								}
							}

						if (GameStatus == 3 || GameStatus == 4)
						{

							if (pom.x >= 499 && pom.y >= 377 && pom.x <= 581 && pom.y <= 461)//green
							{
								ColorPopUp.ObjectSprite.setTextureRect(sf::IntRect(400, 0, 400, 400));
								ColorPopUp.IsActive = true;
							}
							else if (pom.x >= 599 && pom.y >= 377 && pom.x <= 681 && pom.y <= 461)//Blue
							{
								ColorPopUp.ObjectSprite.setTextureRect(sf::IntRect(800, 0, 400, 400));
								ColorPopUp.IsActive = true;
							}
							else if (pom.x >= 499 && pom.y >= 477 && pom.x <= 581 && pom.y <= 561)//Red
							{
								ColorPopUp.ObjectSprite.setTextureRect(sf::IntRect(1200, 0, 400, 400));
								ColorPopUp.IsActive = true;
							}
							else if (pom.x >= 599 && pom.y >= 477 && pom.x <= 681 && pom.y <= 561)//Yellow
							{
								ColorPopUp.ObjectSprite.setTextureRect(sf::IntRect(1600, 0, 400, 400));
								ColorPopUp.IsActive = true;
							}
							if (ColorPopUp.IsActive)
							{
								if (pom.x >= 690 && pom.y >= 426 && pom.x <= 773 && pom.y <= 509)//accept
								{
									GraczWybieraKolor(ColorPopUp.ObjectSprite.getTextureRect().left / 400);
									ColorPopUp.IsActive = false;
									GameStatus -= 3;
								}
							}

						}
						if (pom.y >= 500 && pom.y <= 552)
						{
							if (pom.x >= 490 && pom.x <= 690)
							{
								if (GameStatus != 3 && GameStatus != 4)
									if (GameStatus == 2 || WyrzuconoKarte || CardDrawn)
									{
										EndButton.ObjectSprite.setTextureRect(sf::IntRect(0, 52, 200, 52));
										EndButton.IsActive = true;
									}

							}
						}
					}
					if (event.type == sf::Event::MouseButtonReleased)
					{
						sf::Vector2i pom = sf::Mouse::getPosition(window);
						if (stickToMouse)
						{
							float dist = std::sqrt(std::pow(pom.x - 490, 2) + std::pow(pom.y - 360, 2));
							if (dist < 120)
							{
								if (isEligable(GetPlayer()->getHand()->GetCardID(touchedCard)))//Czy mo¿na j¹ rzuciæ
								{
									if (WyrzuconoKarte)
									{
										if (GetPlayer()->getHand()->getCardNumber(touchedCard) == PlayerThrowCardNum)
										{
											std::regex wzor("([A-Z]{1}\\d)");
											std::string Code;
											int tempnumber = touchedCard;

											auto words_begin = std::sregex_iterator(MoveCode.begin(), MoveCode.end(), wzor);
											auto words_end = std::sregex_iterator();
											for (std::sregex_iterator i = words_begin; i != words_end; i++)
											{
												std::smatch match = *i;
												Code = match.str();
												
												if (Code[0] == 'T')
												{
													if ((Code[1] - '0') <= tempnumber)tempnumber++;
												}
											}
											PlayerThrowCardNum = GetPlayer()->getHand()->getCardNumber(touchedCard);
											Throw(touchedCard);
											Wyrzucone->SetPillePosition(450, 300);
											MoveCode += "T";
											MoveCode += std::to_string(tempnumber);
											MoveCode += ";";
										}
										else
											TouchedCards.emplace_back(touchedCard);
									}
									else
									{
										PlayerThrowCardNum = GetPlayer()->getHand()->getCardNumber(touchedCard);
										Throw(touchedCard);
										Wyrzucone->SetPillePosition(450, 300);
										MoveCode += "T";
										MoveCode += std::to_string(touchedCard);
										MoveCode += ";";
										WyrzuconoKarte = true;
									}

								}
								else
								{
									TouchedCards.emplace_back(touchedCard);
								}
							}
							else
								TouchedCards.emplace_back(touchedCard);
							stickToMouse = false;
						}
						if (DeckActive)
							if (pom.y >= 300 && pom.y <= 420 && pom.x >= 650 && pom.x <= 730)//Ci¹gnij
							{

								DeckActive = false;
								CardDrawn = true;
								SetStatus(0);
								MoveCode += "S";
								MoveCode += std::to_string(0);
								MoveCode += ";";
								MoveCode += "R";
								MoveCode += std::to_string(0);
								MoveCode += ";";
								for (int i = 0; i < CurrentCombo; ++i)
								{
									PlayerDraw(1);
									MoveCode += "D";
									MoveCode += std::to_string(1);
									MoveCode += ";";
									PlayerList[CurrentPlayer]->getHand()->PositionHand(0, PlayerList[CurrentPlayer]->GetHandSize());
									PlayerList[CurrentPlayer]->getHand()->getCollection()->at(PlayerList[CurrentPlayer]->GetHandSize() - 1)->ThisCardSprite->ObjectSprite.setPosition(650, 300);
									TouchedCards.push_back(PlayerList[CurrentPlayer]->GetHandSize() - 1);
								}
								CurrentCombo = 1;
								ChangeEventFlag(false);
								MoveCode += "E";
								MoveCode += std::to_string(0);
								MoveCode += ";";
							}

						if (EndButton.IsActive)//koniec rundy
						{
							EndButton.IsActive = false;
							EndButton.ObjectSprite.setTextureRect(sf::IntRect(0, 0, 200, 52));
							if (pom.y >= 500 && pom.y <= 552)
								if (pom.x >= 490 && pom.x <= 690)
								{

									if (online)
									{
										if (!CardDrawn&& !WyrzuconoKarte)
										{
											if (Event==true)
											{
												MoveCode += "E";
												MoveCode += std::to_string(0);
												MoveCode += ";";
												ChangeEventFlag(false);
											}
											if (GameStatus == 2)
											{
												MoveCode += "S";
												MoveCode += std::to_string(0);
												MoveCode += ";";
												SetStatus(0);
											}
										}
										connection.SendString(MoveCode);
									}
									if (GameStatus == 9)
									{
										SetStatus(10);
									}
									else
									{
										StartTimer(500);
										NextPlayer();
									}
									NotYetMoved = true;
									WyrzuconoKarte = false;
									CardDrawn = false;
									SetUpHandDraw(localPlayer);
									Deck->SetDeckPosition(650, 300);
									Wyrzucone->SetPillePosition(450, 300);
								}
						}

					}
					if (event.type == sf::Event::MouseMoved)
					{
						
						if (stickToMouse)
						{
							sf::Vector2i pom2 = sf::Mouse::getPosition(window);
							PlayerList[localPlayer]->getHand()->RepositionOnMouse(pom2, touchedCard);
						}
					}
				}
			}
			else
			{
				window.pollEvent(event);
				if (connection.IsAnswerRecived())
				{
					ProcessRecivedMove(connection.GetLastMessage());
					SetUpHandDraw(localPlayer);
					for (int i = 0; i < CardsToDraw.size(); ++i)
						PreDraw(CardsToDraw[i]);
					ComsRecived = true;
					connection.ClearMessage();
				}
				if (NotYetMoved)
				{
					NotYetMoved = false;
					connection.StartListening();
					

				}
				if (CardsToThrow.size() == 0 && CardsToDraw.size() == 0 && ComsRecived)
				{
					UpdateTopCard();
					SetUpHandDraw(localPlayer);
					Deck->SetDeckPosition(650, 300);
					Wyrzucone->SetPillePosition(450, 300);
					if (GameStatus == 9)SetStatus(10);
					else
					{
						StartTimer(500);
						NextPlayer();
					}
					ComsRecived = false;
					NotYetMoved = true;
				}
				Setup = false;
			}

			
			int pom=0;
			
			int distance = CurrentPlayer - localPlayer;
			pom += distance;
			if (pom > 3)pom -= 4;
			if (pom < 0)pom += 4;
			switch (pom)
			{
				case 0:
				{
					ActivePlayer.ObjectSprite.setPosition(460, 540);
					ActivePlayer.ObjectSprite.setRotation(180);//0
					break;
				}
				case 1:
				{
					ActivePlayer.ObjectSprite.setPosition(200, 370);
					ActivePlayer.ObjectSprite.setRotation(-90);//1
					break;
				}
				case 2:
				{
					ActivePlayer.ObjectSprite.setPosition(600, 220);
					ActivePlayer.ObjectSprite.setRotation(0);//2
					break;
				}
				case 3:
				{
					ActivePlayer.ObjectSprite.setPosition(960, 370);
					ActivePlayer.ObjectSprite.setRotation(90);//3
				}
			}
			window.clear();
			window.draw(GameBkg.ObjectSprite);
			window.draw(ActivePlayer.ObjectSprite);
			for (int i = 0; i < TouchedCards.size(); ++i)
			{
				if (PlayerList[localPlayer]->getHand()->BackToHand(TouchedCards[i]))
				{
					TouchedCards[i] = TouchedCards[TouchedCards.size() - 1];
					TouchedCards.pop_back();
				}
			}
			if (CardsToDraw.size() == 0)
				for (int i = 0; i < CardsToThrow.size(); ++i)
				{
					if (i == 0)
					{
						if (PlayerList[CurrentPlayer]->getHand()->ThrowAnimation(CardsToThrow[i],-1))
						{
							Throw(CardsToThrow[i]);
							int temp = CardsToThrow[i];
							std::ranges::for_each(CardsToThrow, [&temp](int& x) {if (x > temp)x -= 1; });
							CardsToThrow.erase(CardsToThrow.begin() + i);
						}
					}
					else
						PlayerList[CurrentPlayer]->getHand()->ThrowAnimation(CardsToThrow[i], CardsToThrow[i - 1]);

				}
			for (int i = 0; i < CardsToDraw.size(); ++i)
			{

				if (i == 0)
				{
					if (PlayerList[CurrentPlayer]->getHand()->DrawAnimation(CardsToDraw[i]))
					{
						CardsToDraw[i] = CardsToDraw[CardsToDraw.size() - 1];
						CardsToDraw.pop_back();
					}
				}
				else
					PlayerList[CurrentPlayer]->getHand()->DrawAnimation(CardsToDraw[i], CardsToDraw[i - 1]);


			}
			window.draw(EndButton.ObjectSprite);
			window.draw(CColor.ObjectSprite);


			Deck->DrawTopDeck(window);
			Wyrzucone->DrawTopOFPille(window);
			PlayerList[1]->getHand()->DrawHandOnScreen(window);
			PlayerList[2]->getHand()->DrawHandOnScreen(window);
			PlayerList[3]->getHand()->DrawHandOnScreen(window);
			PlayerList[0]->getHand()->DrawHandOnScreen(window);
			if (GameStatus == 3 || GameStatus == 4)//zmiana koloru
			{
				if (!ColorPopUp.IsActive)ColorPopUp.ObjectSprite.setTextureRect(sf::IntRect(0, 0, 400, 400));
				window.draw(ColorPopUp.ObjectSprite);
			}



			window.display();
		}
		std::string etext = "Wygral gracz: " + PlayerList[CurrentPlayer]->GetName();
		Ending.text.setString(etext);
		std::jthread j2(&Game::ClearOldBoard, this);

		for (int i = 500; i >= 0; i--)
		{
			window.pollEvent(event);
			if (i % 100 == 0)
			{
				etext = "Koniec za " + std::to_string(i / 100) + " sekund";
				EndingTimer.text.setString(etext);
				window.clear();
				window.draw(Ending.text);
				window.draw(EndingTimer.text);
				window.display();
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		StopClock();

	}
	/// <summary>
	/// Counts timeperioid
	/// </summary>
	/// <param name="TimePerioid"></param>
	void CountMilisecondsFor(int TimePerioid)
	{
		
		std::this_thread::sleep_for(std::chrono::milliseconds(TimePerioid));
		PauseTimeElapsed = true;
	}
	/// <summary>
	/// Starts singleplayer game
	/// </summary>
	/// <param name="Name"></param>
	void BeginSingleplayerGame(std::string Name)
	{
		seed = RandomizeStartingSeed();
		ClearSeedCounter();
		ClearPlayers();
		PlayerList[0]->IsLocalPlayer();
		localPlayer = 0;
		PlayerList[0]->SetPC(false);
		PlayerList[0]->SetName(Name);
		StartGameLoop();
		ChangeScene(5);
	}
	/// <summary>
	/// Starts Clock Loop
	/// </summary>
	void BackgroundClock()
	{
		ClockThreadOpen = true;
		while (ClockThreadOpen)
		{
			if (TimerOn)
			{
				CountMilisecondsFor(ClockTimePerioid);
				TimerOn = false;
			}
			else std::this_thread::yield();
		}
	}
	/// <summary>
	/// Starts Timer for set time
	/// </summary>
	/// <param name="TimePerioid"></param>
	inline void  StartTimer(int TimePerioid)
	{
		PauseTimeElapsed = false;
		ClockTimePerioid = TimePerioid;
		TimerOn = true;
	}
	/// <summary>
	/// Stops entirely background clock
	/// </summary>
	inline void  StopClock()
	{
		ClockThreadOpen = false;
	}
private:
	bool Reversed = false;
	bool online = false;
	bool Event = false;
	bool AnswerRecived = false;
	bool IsLoaded = false;
	bool PauseTimeElapsed = true;
	bool TimerOn = false;
	bool ClockThreadOpen = false;
	int CurentHovered = -1;
	int CurrentColor = 0;
	int NewCurrentColor = -1;
	int CurrentCard = 0;
	int CurrentCombo = 1;
	int CurrentPlayer = 0;
	int GameStatus = -1;
	int CurrentSeedNumber = 0;
	int localPlayer = 0;
	int ClockTimePerioid = 0;
	std::string seed;
	std::string MoveCode;
	Connection connection;
	sf::Music music;
	std::vector<std::unique_ptr<Player>> PlayerList;
	std::vector<int>CardsToThrow;
	std::vector<int>CardsToDraw;
	std::unique_ptr<WyrzuconeKarty> Wyrzucone;
	std::unique_ptr<DostepneKarty> Deck;
	std::vector<std::unique_ptr<InteractableObject>> InteractableObjects;
	std::vector<std::unique_ptr<NotInteractableObject>> NonInteractableObjects;
	sf::RenderWindow window;
};
