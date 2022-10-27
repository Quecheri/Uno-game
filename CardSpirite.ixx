
export import InteractableObject;
export module CardSprite;
export class CardSprite : public InteractableObject
{
public:
	CardSprite() :InteractableObject()
	{
		SetSprite("images/Rescaled/Cards.png");
		SavedPosition.x = 0;
		SavedPosition.y = 0;
		IsVisible = false;
	}
	virtual void Active(bool Ac) { IsActive = Ac; };
	virtual bool isText() { return false; }

	virtual bool isButton() { return false; }
	
	//0/1/2/3/4/5/6/7/8/9/10=rev/11=block/12=color/13=+2/14=+4/15=rev;
	/// <summary>
	/// Sets WithOffset and Highoffset using CardNumber and CardColor
	/// </summary>
	/// <param name="CardNumber"></param>
	/// <param name="CardColor"></param>
	void LoadCurrentCard(int CardNumber, int CardColor)
	{
		WidthOffset = CardNumber * 80;

		if (CardColor > 3)HeightOffset = 3 * 120;
		else if (CardColor < 4)HeightOffset = CardColor * 120;
		LoadCardAwers();
	}
	/// <summary>
	/// Sets textureRect to card Averse
	/// </summary
	void LoadCardAwers()
	{
		ObjectSprite.setTextureRect(sf::IntRect(WidthOffset, HeightOffset, 80, 120));
	}
	/// <summary>
	/// Sets textureRect to card reverse
	/// </summary>
	void LoadCardReverse()
	{
		ObjectSprite.setTextureRect(sf::IntRect(1200, 0, 80, 120));
	}
	/// <summary>
	/// changes SavedPosition with param
	/// </summary>
	/// <param name="newPosition"></param>
	void SaveNewPosition(sf::Vector2i newPosition)
	{
		SavedPosition = newPosition;
	}
	/// <summary>
	/// changes SavedRotation with param
	/// </summary>
	/// <param name="newRotation"></param>
	void SaveNewRotation(float newRotation)
	{
		SavedRotation = newRotation;
	}
	/// <summary>
	/// returns SavedPosition
	/// </summary>
	/// <returns></returns>
	sf::Vector2i GetPreviousPosition()
	{
		return SavedPosition;
	}
	/// <summary>
	/// Resets position from SavedPosition
	/// </summary
	void ReSetPreviousPosition()
	{
		ObjectSprite.setPosition(SavedPosition.x, SavedPosition.y);
	}
	/// <summary>
	/// Resets rotation from SavedRotation
	/// </summary>
	void ReSetPreviousRotation()
	{
		ObjectSprite.setRotation(SavedRotation);
	}
	sf::Vector2i SavedPosition;
	float SavedRotation;
	int WidthOffset;
	int HeightOffset;
};
