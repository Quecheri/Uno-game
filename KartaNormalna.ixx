export import Karta;
export module KartaNormalna;

export class KartaNormalna : public Karta
{
private:

public:
	KartaNormalna(int id)
	{
		ID = id;
		ThisCardSprite = std::make_unique<CardSprite>();
		SetCardSprite(id);
	}

	virtual void SetCardSprite(int id)
	{
		ThisCardSprite->LoadCurrentCard(getNumber(), getColor());
	}
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
	virtual int getNumber() {
		int offset = ID % 16;
		return (ID - offset) / 16;
	}
	virtual int getColor() {
		return  ID % 16;
	}
	virtual void show()
	{
		std::cout << getColorInText() << ": " << getNumber() << std::endl;
	}
	virtual bool isNormal()
	{
		return true;
	}
	virtual int GameStatus()
	{
		return 0;
	}
};
