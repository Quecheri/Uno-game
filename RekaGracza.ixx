
export import ZestaweKart;
export module RekaGracza;


export class RekaGracza :public ZestawKart
{
public:

	std::unique_ptr<Karta> getCard(int location)
	{
		return move(Collection[location]);
	}
	/// <summary>
	/// Returns card number
	/// </summary>
	/// <param name="n"></param>
	/// <returns></returns>
	int getCardNumber(int n)
	{
		return Collection[n]->getNumber();
	}
	/// <summary>
	/// Returns card color
	/// </summary>
	/// <param name="n"></param>
	/// <returns></returns>
	int getCardColor(int n)
	{
		return Collection[n]->getColor();
	}
	/// <summary>
/// Returns card id
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
	int GetCardID(int n)
	{
		return Collection[n]->getID();
	}
	/// <summary>
/// Returns hand size
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
	int GetSize() { return Collection.size(); }
	/// <summary>
/// deletes empty space after throw
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
	void EfficientRemove(int n) {
		Collection.erase(Collection.begin() + n);
	}
	/// <summary>
	/// cllears whole hand
	/// </summary>
	void ClearHand() {
		Collection.erase(Collection.begin(), Collection.end());
	}
	/// <summary>
	/// returns tapped card position in hand
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	int FindTouchedCard(sf::Vector2i pos)
	{
		for (int i = Collection.size() - 1; i >= 0; --i)
		{
			if (pos.x - Collection[i]->ThisCardSprite->SavedPosition.x <= 80 && pos.x - Collection[i]->ThisCardSprite->SavedPosition.x >= 0)
			{
				if (pos.y - Collection[i]->ThisCardSprite->SavedPosition.y <= 120 && pos.y - Collection[i]->ThisCardSprite->SavedPosition.y >= 0)
				{

					Collection[i]->ThisCardSprite->ObjectSprite.setOrigin(pos.x - Collection[i]->ThisCardSprite->SavedPosition.x, pos.y - Collection[i]->ThisCardSprite->SavedPosition.y);
					return i;
				}

				else if (pos.y - Collection[i]->ThisCardSprite->SavedPosition.y > 120)
					return -1;
			}
			else if (pos.x - Collection[i]->ThisCardSprite->SavedPosition.x > 80)
				return -1;
		}
		return -1;

	}
	/// <summary>
	/// Stick card to mouse and sets orgin to middle
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="tCard"></param>
	void RepositionOnMouse(sf::Vector2i& pos, int tCard)
	{
		if (tCard >= 0)Collection[tCard]->ThisCardSprite->ObjectSprite.setPosition(pos.x, pos.y);
	}
	/// <summary>
	/// sets hand position as well as cards spacing and orientation
	/// </summary>
	/// <param name="RelativePosition"></param>
	/// <param name="CardsToLoad"></param>
	void PositionHand(int RelativePosition, int CardsToLoad)
	{
		if (CardsToLoad > Collection.size())CardsToLoad = Collection.size();
		int CardVolume = 0;
		int CardSpacing = 0;
		int freeSpace = 0;

		if (RelativePosition == 0)//Local player
		{
			CardVolume = CardsToLoad * 80;
			CardSpacing = 80;
			freeSpace = ((900 - CardVolume) / 2) + 150;
			if (CardVolume > 900)
			{
				freeSpace = 150;
				CardSpacing = ((900 - 80) / CardsToLoad);
			}
			//space=900
			for (int i = 0; i < CardsToLoad; i++)
			{

				Collection[i]->ThisCardSprite->ObjectSprite.setPosition(freeSpace + (i * CardSpacing), 600);
				Collection[i]->ThisCardSprite->SaveNewPosition(sf::Vector2i(freeSpace + (i * CardSpacing), 600));
				Collection[i]->ThisCardSprite->ObjectSprite.setRotation(0);
				Collection[i]->ThisCardSprite->SaveNewRotation(0);
				Collection[i]->ThisCardSprite->LoadCardAwers();
				Collection[i]->ThisCardSprite->IsVisible = true;
			}

		}
		else if (RelativePosition == 1)//GIT
		{
			//space=500
			CardVolume = CardsToLoad * 80;
			CardSpacing = 80;
			freeSpace = ((500 - CardVolume) / 2) + 150;
			if (CardVolume > 500)
			{
				freeSpace = 150;
				CardSpacing = (500 - 80) / CardsToLoad;
			}
			for (int i = 0; i < CardsToLoad; i++)
			{
				Collection[i]->ThisCardSprite->ObjectSprite.setPosition(150, freeSpace + (i * CardSpacing));
				Collection[i]->ThisCardSprite->SaveNewPosition(sf::Vector2i(150, freeSpace + (i * CardSpacing)));
				Collection[i]->ThisCardSprite->ObjectSprite.setRotation(90);
				Collection[i]->ThisCardSprite->SaveNewRotation(90);
				Collection[i]->ThisCardSprite->LoadCardReverse();
				//Collection[i]->ThisCardSprite->LoadCardAwers();
				Collection[i]->ThisCardSprite->IsVisible = true;
			}
		}
		else if (RelativePosition == 2)//GIT
		{
			//space=900
			CardVolume = CardsToLoad * 80;
			CardSpacing = 80;
			freeSpace = ((900 - CardVolume) / 2) + 150;
			if (CardVolume > 900)
			{
				freeSpace = 150;
				CardSpacing = (900 - 80) / CardsToLoad;
			}
			for (int i = CardsToLoad - 1; i > -1; --i)
			{
				Collection[i]->ThisCardSprite->ObjectSprite.setPosition(freeSpace + (i * CardSpacing), 50);
				Collection[i]->ThisCardSprite->SaveNewPosition(sf::Vector2i(freeSpace + (i * CardSpacing), 50));
				Collection[i]->ThisCardSprite->ObjectSprite.setRotation(0);
				Collection[i]->ThisCardSprite->SaveNewRotation(0);
				Collection[i]->ThisCardSprite->LoadCardReverse();
				//Collection[i]->ThisCardSprite->LoadCardAwers();
				Collection[i]->ThisCardSprite->IsVisible = true;
			}
		}
		else if (RelativePosition == 3)//Local player
		{
			//space=500
			CardVolume = CardsToLoad * 80;
			CardSpacing = 80;
			freeSpace = ((500 - CardVolume) / 2) + 150;
			if (CardVolume > 500)
			{

				freeSpace = 150;
				CardSpacing = (500 - 80) / CardsToLoad;
			}
			for (int i = 0; i < CardsToLoad; i++)
			{
				Collection[i]->ThisCardSprite->ObjectSprite.setPosition(1150, freeSpace + (i * CardSpacing));
				Collection[i]->ThisCardSprite->SaveNewPosition(sf::Vector2i(1150, freeSpace + (i * CardSpacing)));
				Collection[i]->ThisCardSprite->ObjectSprite.setRotation(90);
				Collection[i]->ThisCardSprite->SaveNewRotation(90);
				Collection[i]->ThisCardSprite->LoadCardReverse();
				//Collection[i]->ThisCardSprite->LoadCardAwers();
				Collection[i]->ThisCardSprite->IsVisible = true;
			}
		}

	}
	/// <summary>
	/// Returns card to hand ANIMATION
	/// </summary>
	/// <param name="CardID"></param>
	/// <returns></returns>
	bool BackToHand(int CardID)
	{
		float xDistance = Collection[CardID]->ThisCardSprite->ObjectSprite.getPosition().x - Collection[CardID]->ThisCardSprite->SavedPosition.x;
		float yDistance = Collection[CardID]->ThisCardSprite->ObjectSprite.getPosition().y - Collection[CardID]->ThisCardSprite->SavedPosition.y;
		float StraightDistance = std::sqrt(xDistance * xDistance + yDistance * yDistance);
		if (StraightDistance > LockPositionDistance)
		{
			xDistance /= -AnimationSlowdown;
			yDistance /= -AnimationSlowdown;

			if (std::abs(xDistance) < 1)
			{
				xDistance *= MinimalSpeedOnCloseUp;
				yDistance *= MinimalSpeedOnCloseUp;

			}
			else if (std::abs(yDistance) < 1)
			{
				xDistance *= MinimalSpeedOnCloseUp;
				yDistance *= MinimalSpeedOnCloseUp;
			}


			Collection[CardID]->ThisCardSprite->ObjectSprite.move(xDistance, yDistance);
			return false;
		}
		else
		{
			Collection[CardID]->ThisCardSprite->ObjectSprite.setOrigin(0, 0);
			Collection[CardID]->ThisCardSprite->ReSetPreviousPosition();
			return true;
		}

	}
	/// <summary>
	/// Animate Throw
	/// </summary>
	/// <param name="CardInHandPosition"></param>
	/// <param name="CardBefore"></param>
	/// <returns></returns>
	bool ThrowAnimation(int CardInHandPosition, int CardBefore = -1)
	{
		float Sd = 100;
		if (CardBefore > -1)
		{
			float xDistanceToPreviousCard = Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.getPosition().x - Collection[CardBefore]->ThisCardSprite->ObjectSprite.getPosition().x;
			float yDistanceToPreviousCard = Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.getPosition().y - Collection[CardBefore]->ThisCardSprite->ObjectSprite.getPosition().y;
			Sd = std::sqrt(std::pow(xDistanceToPreviousCard, 2) + std::pow(yDistanceToPreviousCard, 2));
		}
		else if (Sd > 20)
		{
			if (Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.getTextureRect().left == 1200)
				Collection[CardInHandPosition]->ThisCardSprite->LoadCardAwers();

			float xDistance = Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.getPosition().x - 450;
			float yDistance = Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.getPosition().y - 300;
			float StraightDistance = std::sqrt(xDistance * xDistance + yDistance * yDistance);
			if (StraightDistance > LockPositionDistance)
			{
				xDistance /= -AnimationSlowdown;
				yDistance /= -AnimationSlowdown;

				if (std::abs(xDistance) < 1)
				{
					xDistance *= MinimalSpeedOnCloseUp;
					yDistance *= MinimalSpeedOnCloseUp;

				}
				else if (std::abs(yDistance) < 1)
				{
					xDistance *=MinimalSpeedOnCloseUp;
					yDistance *=MinimalSpeedOnCloseUp;
				}
				Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.move(xDistance, yDistance);
				if (Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.getRotation() > 90)
					Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.rotate(-RotationSpeed);
				else if (Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.getRotation() > 0)
					Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.rotate(-RotationSpeed);
				else if (Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.getRotation() < 0)
					Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.rotate(RotationSpeed);
				return false;
			}
			else
			{
				Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.setPosition(450, 300);
				Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.setRotation(0);
				return true;
			}

		}
	}
	/// <summary>
	/// ANIMATE draw
	/// </summary>
	/// <param name="CardInHandPosition"></param>
	/// <param name="CardBefore"></param>
	/// <returns></returns>
	bool DrawAnimation(int CardInHandPosition, int CardBefore = -1)
	{

		float Sd = 100;
		if (CardBefore > -1)
		{
			float xDistanceToPreviousCard = Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.getPosition().x - Collection[CardBefore]->ThisCardSprite->ObjectSprite.getPosition().x;
			float yDistanceToPreviousCard = Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.getPosition().y - Collection[CardBefore]->ThisCardSprite->ObjectSprite.getPosition().y;
			Sd = std::sqrt(std::pow(xDistanceToPreviousCard, 2) + std::pow(yDistanceToPreviousCard, 2));
		}
		else if (Sd > 20)
		{
			float xDistance = Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.getPosition().x - Collection[CardInHandPosition]->ThisCardSprite->SavedPosition.x;
			float yDistance = Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.getPosition().y - Collection[CardInHandPosition]->ThisCardSprite->SavedPosition.y;
			float StraightDistance = std::sqrt(std::pow(xDistance, 2) + std::pow(yDistance, 2));
			if (StraightDistance > LockPositionDistance)
			{
				xDistance /= -AnimationSlowdown;
				yDistance /= -AnimationSlowdown;

				if (std::abs(xDistance) < 1)
				{
					xDistance *= MinimalSpeedOnCloseUp;
					yDistance *= MinimalSpeedOnCloseUp;

				}
				else if (std::abs(yDistance) < 1)
				{
					xDistance *= MinimalSpeedOnCloseUp;
					yDistance *= MinimalSpeedOnCloseUp;
				}
				Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.move(xDistance, yDistance);
				if (Collection[CardInHandPosition]->ThisCardSprite->SavedRotation > Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.getRotation())
					Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.rotate(RotationSpeed);
				else if (Collection[CardInHandPosition]->ThisCardSprite->SavedRotation < Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.getRotation())
					Collection[CardInHandPosition]->ThisCardSprite->ObjectSprite.rotate(-RotationSpeed);
				return false;
			}
			else
			{
				Collection[CardInHandPosition]->ThisCardSprite->ReSetPreviousRotation();
				Collection[CardInHandPosition]->ThisCardSprite->ReSetPreviousPosition();
				return true;
			}
		}
	}
	/// <summary>
	/// Draw hands
	/// </summary>
	/// <param name="window"></param>
	void DrawHandOnScreen(sf::RenderWindow& window)
	{
		for (auto& el : Collection)
			if (el->ThisCardSprite->IsVisible)
				window.draw((el->ThisCardSprite->ObjectSprite));
	}
	private:
		float AnimationSlowdown = 10;
		float MinimalSpeedOnCloseUp = 3;
		float LockPositionDistance = 50;
		float RotationSpeed = 2.5;
};