export import Karta;
export module KartaSpecjalna;
export class KartaSpecjalna : public Karta
{
private:

public:
	KartaSpecjalna(int id) {
		ID = id;
		ThisCardSprite = std::make_unique<CardSprite>();
		SetCardSprite(id);
	}
	virtual void SetCardSprite(int id)
	{
		ThisCardSprite->LoadCurrentCard(getNumber(), getColor());
	}
	/// <summary>
	/// Returns number in text
	/// </summary>
	/// <returns>string</returns>
	std::string getNumberInText() {
		int Number = (ID - (ID % 16)) / 16;
		switch (Number)
		{
		case 10:	return "Stop";
		case 11:	return "Reverse";
		case 12:	return "Draw 2";
		case 13:	return "Draw 4";
		default:	return "Change Color";
		}
	}
	virtual int getNumber() {
		int offset = ID % 16;
		return (ID - offset) / 16;
	}
	/// <summary>
/// Returns color in text
/// </summary>
/// <returns>string</returns>
	std::string getColorInText() {
		int color = ID % 16;
		switch (color)
		{
		case 0:	return "Red";
		case 1:	return "Green";
		case 2:	return "Blue";
		case 3:	return "Yellow";
		default:return "Black";
		}
	}
	virtual int getID()
	{
		return ID;
	}
	virtual int getColor() {
		return  ID % 16;
	}

	virtual void show()
	{
		std::cout << getColorInText() << ": " << getNumberInText() << std::endl;
	}
	virtual bool isNormal()
	{
		return false;
	}
	virtual int GameStatus()
	{
		//Reverse daje 0
		//1 draw
		//2 block
		int number = getNumber();
		if (number == 12 || number == 13)return 1;
		else if (number == 10)return 2;
		else return 0;
	}

};