
export import ZestaweKart;
export module WyrzuconeKarty;


export class WyrzuconeKarty :public ZestawKart
{
private:

public:
	/// <summary>
	/// Prints Rop card OBSOLETE
	/// </summary>
	void printTrueTopCard()
	{
		Collection.back()->show();
	}
	/// <summary>
	/// Draws top od the pille
	/// </summary>
	/// <param name="window"></param>
	void DrawTopOFPille(sf::RenderWindow& window)
	{
		if (Collection.size() > 1)window.draw(Collection[Collection.size() - 2]->ThisCardSprite->ObjectSprite);
		window.draw(Collection[Collection.size() - 1]->ThisCardSprite->ObjectSprite);
	}
	/// <summary>
	/// sets pille position on screen as well as rotation
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void SetPillePosition(int x, int y)
	{
		if (Collection.size() > 1)
		{
			Collection[Collection.size() - 2]->ThisCardSprite->ObjectSprite.setOrigin(0, 0);
			Collection[Collection.size() - 2]->ThisCardSprite->ObjectSprite.setRotation(0);
			Collection[Collection.size() - 2]->ThisCardSprite->ObjectSprite.setPosition(x, y);
			Collection[Collection.size() - 2]->ThisCardSprite->LoadCardAwers();
		}
		Collection[Collection.size() - 1]->ThisCardSprite->ObjectSprite.setOrigin(0, 0);
		Collection[Collection.size() - 1]->ThisCardSprite->ObjectSprite.setRotation(0);
		Collection[Collection.size() - 1]->ThisCardSprite->ObjectSprite.setPosition(x, y);
		Collection[Collection.size() - 1]->ThisCardSprite->LoadCardAwers();
	}
	/// <summary>
	/// Clears whole pille but last card
	/// </summary>
	void ClearPilleAfterReshuffle() { Collection.erase(Collection.begin(), Collection.end() - 1); };
	/// <summary>
	/// Clear whole pille
	/// </summary>
	void ClearWholePille() { Collection.erase(Collection.begin(), Collection.end()); };

};