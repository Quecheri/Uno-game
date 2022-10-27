export import <memory>;
export import <iostream>;
export import CardSprite;
export module Karta;

export class Karta
{

public:
	/// <summary>
	/// Writes to std::out Card number and color
	/// </summary>
	virtual void show() = 0;
	/// <summary>
	/// retutns true if card isn't special
	/// </summary>
	/// <returns>isNormal</returns>
	virtual bool isNormal() = 0;
	/// <summary>
/// retutns gamestatus
/// </summary>
/// <returns>GameStatus</returns>
	virtual int GameStatus() = 0;
	/// <summary>
	/// Returns card number
	/// </summary>
	/// <returns></returns>
	virtual int getNumber() = 0;
	/// <summary>
	/// Returns card id
	/// </summary>
	/// <returns></returns>
	virtual int getID() = 0;
	/// <summary>
	/// Returns card color
	/// </summary>
	/// <returns></returns>
	virtual int getColor() = 0;
	/// <summary>
	/// Sets Sprite
	/// </summary>
	/// <param name="id"></param>
	virtual void SetCardSprite(int id) = 0;
	std::unique_ptr<CardSprite> ThisCardSprite;
protected:

	int ID;

};

