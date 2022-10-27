export import ZestaweKart;
export module DostepneKarty;

export class DostepneKarty :public ZestawKart
{
public:
	DostepneKarty()
	{
	}
	/// <summary>
	/// Draws on screen top 2 cards
	/// </summary>
	/// <param name="window"></param>
	void DrawTopDeck(sf::RenderWindow& window)
	{
		if (Collection.size() > 0)window.draw(Collection[Collection.size() - 1]->ThisCardSprite->ObjectSprite);
		if (Collection.size() > 1)window.draw(Collection[Collection.size() - 2]->ThisCardSprite->ObjectSprite);
	}
	/// <summary>
	/// Sets Deck position and deck rotation
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void SetDeckPosition(int x, int y)
	{
		for (auto& el : Collection)
		{
			el->ThisCardSprite->ObjectSprite.setPosition(x, y);
			el->ThisCardSprite->LoadCardReverse();
			el->ThisCardSprite->ObjectSprite.setRotation(0);
		}

	}
	/// <summary>
	/// Function restores deck to known state
	/// </summary>
	void RestartDeck()
	{

		int PositionTable[241]{ -1 };
		for (int i = 0; i < 241; i++) 
			PositionTable[i] = -1;
		
		std::vector<std::unique_ptr<Karta>> TemporaryCardTable;

		for (int j = 0; j < Collection.size(); j++)
		{
			int offset = 0;
			while (true)
			{
				if (PositionTable[Collection[j]->getID()+(offset*4)] == -1)
				{
					PositionTable[Collection[j]->getID()+(offset*4)] = j;
					break;
				}
				else
					offset++;
			}
		}

		for (int i = 0; i < 241; i++)
			if(PositionTable[i]!=-1)TemporaryCardTable.push_back(move(Collection[PositionTable[i]]));
		Collection.clear();

		for (int z = 0; z < TemporaryCardTable.size(); z++)
			Collection.push_back(move(TemporaryCardTable[z]));
	}
	/// <summary>
	/// Genereate whole deck wihout shuffling
	/// </summary>
	void GenerateDeck()
	{

		//Karty normalne 
		// 0
		getCollection()->push_back(std::make_unique<KartaNormalna>(0));
		getCollection()->push_back(std::make_unique<KartaNormalna>(1));
		getCollection()->push_back(std::make_unique<KartaNormalna>(2));
		getCollection()->push_back(std::make_unique<KartaNormalna>(3));
		for (int i = 1; i < 10; i++)
		{
			for (int j = 0; j < 2; j++)
			{ //1-9
				getCollection()->push_back(std::make_unique<KartaNormalna>(i * 16 + 0));
				getCollection()->push_back(std::make_unique<KartaNormalna>(i * 16 + 1));
				getCollection()->push_back(std::make_unique<KartaNormalna>(i * 16 + 2));
				getCollection()->push_back(std::make_unique<KartaNormalna>(i * 16 + 3));
			}

		}
		//Karty funkcjonalne

		for (int j = 10; j < 13; j++)
		{
			//Stop/Reverse/+2
			getCollection()->push_back(std::make_unique<KartaSpecjalna>(j * 16 + 0));
			getCollection()->push_back(std::make_unique<KartaSpecjalna>(j * 16 + 1));
			getCollection()->push_back(std::make_unique<KartaSpecjalna>(j * 16 + 2));
			getCollection()->push_back(std::make_unique<KartaSpecjalna>(j * 16 + 3));

			getCollection()->push_back(std::make_unique<KartaSpecjalna>(j * 16 + 0));
			getCollection()->push_back(std::make_unique<KartaSpecjalna>(j * 16 + 1));
			getCollection()->push_back(std::make_unique<KartaSpecjalna>(j * 16 + 2));
			getCollection()->push_back(std::make_unique<KartaSpecjalna>(j * 16 + 3));
		}
		for (int j = 13; j < 15; j++)
		{
			//+4/Color
			getCollection()->push_back(std::make_unique<KartaSpecjalna>(j * 16 + 4));
			getCollection()->push_back(std::make_unique<KartaSpecjalna>(j * 16 + 4));
			getCollection()->push_back(std::make_unique<KartaSpecjalna>(j * 16 + 4));
			getCollection()->push_back(std::make_unique<KartaSpecjalna>(j * 16 + 4));

		}
	}
	/// <summary>
	/// Draws Top card from deck
	/// </summary>
	/// <returns></returns>
	std::unique_ptr<Karta> DrawFromDeck()
	{
		std::unique_ptr<Karta> temp = move(Collection[Collection.size() - 1]);
		Collection.pop_back();
		return move(temp);
	}
	/// <summary>
	/// Shuffles shufflenumber times deck
	/// </summary>
	/// <param name="SourcePile"></param>
	/// <param name="shufflenumber"></param>
	void Reshuffle(std::vector<std::unique_ptr<Karta>>* SourcePile, int shufflenumber)
	{
		for (int i = 0; i < SourcePile->size() - 1; i++)
		{
			Collection.push_back(move(SourcePile->at(i)));
		}
		PerfectShuffle(shufflenumber);
	}
	/// <summary>
	/// Returns cards from player
	/// </summary>
	/// <param name="SourcePile"></param>
	void ReturnCards(std::vector<std::unique_ptr<Karta>>* SourcePile)
	{
		for (int i = 0; i < SourcePile->size(); i++)
		{
			Collection.push_back(move(SourcePile->at(i)));
		}
	}
};