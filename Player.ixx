export import RekaGracza;
export module Player;


export class Player
{
public:
	Player(int id, bool pc) :PlayerId(id), PC(pc) {};
	Player(int id, bool pc, std::string name) :PlayerId(id), PC(pc), name(name) {};
	/// <summary>
	/// Returns player's hand
	/// </summary>
	/// <returns></returns>
	RekaGracza* getHand() { return &Hand; }
	/// <summary>
	/// Puts card on top of hand
	/// </summary>
	/// <param name="karta">unique_ptr<karta></param>
	void DrawOne(std::unique_ptr<Karta>karta) {
		Hand.PutOnTop(karta);
	}
	/// <summary>
	/// Zwraca -1, je¿eli nie znajdzie szukanej karty
	/// </summary>
	void ExpandVector()
	{
		int times = Hand.GetSize() - AiValueVector.size();
		for (int i = 0; i < times; i++)AiValueVector.push_back(0);
	}
	/// <summary>
	/// Calculates AI move. Each card must be evaluated
	/// </summary>
	/// <param name="CardIndex"></param>
	/// <param name="GameState"></param>
	/// <param name="TopCardNumber"></param>
	/// <param name="TopCardColor"></param>
	/// <param name="NextPlayer"></param>
	/// <param name="BeforePlayer"></param>
	void CalculateAiMove(int CardIndex, int GameState, int TopCardNumber, int TopCardColor, Player* NextPlayer, Player* BeforePlayer)
	{
		if (AiValueVector.size() < Hand.GetSize())ExpandVector();
		int value = 0;
		int MyCardColor = Hand.GetCardID(CardIndex) % 16;
		int MyCardNumber = (Hand.GetCardID(CardIndex) - MyCardColor) / 16;
		int SecondaryValueTable[7] = { 0 };
		int SecondaryColor;
		int SecondaryCard;
		//Ile Tej Samej Karty
		//Ile Teego samego koloru
		//Ile kart nastêpnik
		//Ile kart poprzednik
		//Ile kart +2
		//Ile kart +4
		//Ile kart block
		for (int i = 0; i < Hand.GetSize(); i++)
		{
			SecondaryColor = Hand.getCardColor(i);
			SecondaryCard = Hand.getCardNumber(i);
			if (MyCardColor == SecondaryColor)SecondaryValueTable[1]++;
			if (MyCardNumber == SecondaryCard)SecondaryValueTable[0]++;
			if (SecondaryCard == 10)SecondaryValueTable[6]++;
			else if (SecondaryCard == 12)SecondaryValueTable[4]++;
			else if (SecondaryCard == 13)SecondaryValueTable[5]++;
		}
		SecondaryValueTable[2] = NextPlayer->Hand.GetSize();
		SecondaryValueTable[3] = BeforePlayer->Hand.GetSize();

		//Faktyczne obliczenia


		//n kopii koloru  w rêce ->-10 + n*5
		//Mo¿na j¹ rzuciæ +1000
		//Nie mo¿na jej rzuciæ -1000
		//n kopi tej karty w rêce-> +5 - n*5
		//Normalna +20
		//Specjalna -20
		// Mam wiêcej niz jedno +2/+4->+5
		//+2 gdy nastêpny gracz ma x kart-> +25 -x*5
		//+4 gdy nastêpny gracz ma x kart-> +20 -x*5
		//Stop +10 (+20 gdy nie mam w rêce +2/4)
		//Reverse +10 (gdy poprzednik ma mniej niz 3 karty +0,/-5)
		//Gdy masz kolor change color -20
		//Event/ Odbicie karty poprzedniego gracza +100
		SecondaryColor = TopCardColor;
		SecondaryCard = TopCardNumber;
		if (GameState == 0)
		{
			if (MyCardColor == SecondaryColor || MyCardColor == 4 || MyCardNumber == SecondaryCard)//Czy mo¿na j¹ rzuciæ
			{
				value += 1000;//isEligable
				value += -10 + SecondaryValueTable[1] * 5;//Ile tego samego koloru
				value += -10 + SecondaryValueTable[1] * 5;//Ile tego samego koloru
				if (MyCardNumber < 9)value += 10;//czy normlana
				else value -= 10;//Gdy specjalna

				if (MyCardNumber == 12) { //gdy karta to +2 i mam ich kilka w rêce
					if (SecondaryValueTable[4] > 1)value += 5;
					value += +25 - SecondaryValueTable[2] * 5;

				}
				else if (MyCardNumber == 13) {//gdy karta to +4 i mam ich kilka w rêce
					if (SecondaryValueTable[5] > 1)value += 5;
					value += +20 - SecondaryValueTable[2] * 5;
				}
				else if (MyCardNumber == 10)//gdy karta to stop i mam ich kilka w rêce
				{
					value += 10;
					if (SecondaryValueTable[4] == 0 && SecondaryValueTable[5] == 0)value += 10;
					if (SecondaryValueTable[6] > 1)value += 5;

				}
				if (MyCardNumber == 11)
				{
					if (SecondaryValueTable[3] > 3) value += 10;
					else if (SecondaryValueTable[3] = 3)value += 5;
					else if (SecondaryValueTable[3] < 3)value -= 5;
				}
				if (MyCardNumber == 14)
				{
					if (SecondaryValueTable[1] > 1) value -= 30;

				}
			}
			else value = -1000;
		}
		else if (GameState == 1)
		{
			if (MyCardNumber == 12 && SecondaryCard == 12)value += 100;
			else if (MyCardNumber == 13 && SecondaryCard == 12)value += 100;
			else if (MyCardNumber == 13 && SecondaryCard == 13)value += 100;
			else if (MyCardNumber == 13 && SecondaryCard == 12 && MyCardColor == SecondaryCard)value += 100;
			else value = -1000;
		}
		else if (GameState == 2)
		{
			if (MyCardNumber == 10 && SecondaryCard == 10)value += 100;
			else value = -1000;
		}
		AiValueVector[CardIndex] = value;

	}
	/// <summary>
	/// Returns PC
	/// </summary>
	/// <returns></returns>
	bool IsPC() { return PC; }
	/// <summary>
	/// Sets PC
	/// </summary>
	/// <param name="pc"></param>
	void SetPC(bool pc) { PC = pc; }
	/// <summary>
	/// Sets LocalPlayer=true
	/// </summary>
	void IsLocalPlayer() { LocalPlayer = true; }
	/// <summary>
	/// returns LocalPlayer
	/// </summary>
	/// <returns></returns>
	bool GetLocalPlayer() { return LocalPlayer; }
	/// <summary>
	/// returns AI-chosen card id
	/// </summary>
	/// <returns></returns>
	int GetChosenCardId() {
		int maxV = -10000;
		int maxIndex = 0;
		for (int i = 0; i < Hand.GetSize(); i++)
		{
			if (AiValueVector[i] > maxV) { maxV = AiValueVector[i]; maxIndex = i; }
		}
		return maxIndex;
	}
	/// <summary>
	/// //Zwraca -1 je¿eli nic nie znajdzie. wersja dla pierwszej karty
	/// </summary>
	/// <param name="CardNumber"></param>
	/// <returns></returns>
	int SearchForMore(int CardNumber) {
		for (int i = 0; i < Hand.GetSize(); i++)
		{
			if (CardNumber == Hand.getCardNumber(i))return i;
		}
		return -1;
	}
	/// <summary>
/// //Zwraca -1 je¿eli nic nie znajdzie, wersja dla wszystkich kart poza pierwsz¹
/// </summary>
/// <param name="CardNumber"></param>
/// <returns></returns>
	void SearchForMore(std::vector<int>& CardsFound, int CardNumber) {
		for (int i = 0; i < Hand.GetSize(); i++)
		{
			if (CardNumber == Hand.getCardNumber(i))CardsFound.push_back(i);
		}
	}
	/// <summary>
	/// returns AI-chosen card value
	/// </summary>
	/// <returns></returns>
	int GetChosenCardValue() {
		int maxV = -10000;
		for (int i = 0; i < Hand.GetSize(); i++)
		{
			if (AiValueVector[i] > maxV) maxV = AiValueVector[i];
		}
		return maxV;
	}
	/// <summary>
	/// returns name
	/// </summary>
	/// <returns></returns>
	std::string GetName() { return name; }
	/// <summary>
	/// sets name
	/// </summary>
	/// <param name="Name"></param>
	void SetName(std::string Name) { name = Name; }
	/// <summary>
	/// returns hand size
	/// </summary>
	/// <returns></returns>
	int GetHandSize() { return Hand.GetSize(); }
	/// <summary>
	/// returns AI-choosen color
	/// </summary>
	/// <returns></returns>
	int GetFavouriteColor()
	{
		int colors[5] = { 0 };
		int maxC = -1;
		int maxCCount = 0;

		for (auto i = 0; i < Hand.GetSize(); i++)
		{
			colors[Hand.getCardColor(i)]++;
		}
		for (auto i = 0; i < 4; i++)
		{
			if (colors[i] > maxCCount) {
				maxCCount = colors[i]; maxC = i;
			}
		}
		if (maxC == -1)
		{
			int maxC = (rand() % 4);
		}
		return maxC;
	}

private:
	int PlayerId;
	bool LocalPlayer = false;
	bool PC;
	std::string name;
	RekaGracza Hand;
	std::vector<int>AiValueVector;
};
