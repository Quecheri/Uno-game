export module GuiObject;
export import <SFML/Graphics.hpp>;


export class GUIObject
{
public:
	GUIObject() {}
	GUIObject(int pos, int id) :ID(id), IndexPosition(pos) {}
	/// <summary>
	/// Sets visibility of an object
	/// </summary>
	/// <param name="newVisibility"></param>
	void Visibility(bool newVisibility)
	{
		IsVisible = newVisibility;
	}
	/// <summary>
	/// returns object ID
	/// </summary>
	/// <returns></returns>
	const int GetID()
	{
		return ID;
	}
	/// <summary>
	/// Sets Sprite from location
	/// </summary>
	/// <param name="TextureLocation"></param>
	/// <returns></returns>
	bool SetSprite(std::string TextureLocation)
	{
		if (!ObjectTexture.loadFromFile(TextureLocation))
		{
			return false;//jeœli nie wczyta
		}
		ObjectTexture.setSmooth(true);
		ObjectSprite.setTexture(ObjectTexture);
		return true;
	};
	/// <summary>
	/// Decode positoin from int into (x,y) coordinates
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	sf::Vector2f DecodePosition(int pos)
	{
		switch (pos)
		{
		case 0:return sf::Vector2f(450, 100);
		case 1:return sf::Vector2f(450, 190);
		case 2:return sf::Vector2f(450, 280);
		case 3:return sf::Vector2f(450, 370);
		case 4:return sf::Vector2f(450, 460);
		case 5:return sf::Vector2f(450, 550);
		case 6:return sf::Vector2f(350, 270);
		case 7:return sf::Vector2f(690, 270);
		case 9:return sf::Vector2f(490, 500);//btn
		case 10:return sf::Vector2f(400, 200);//Color btn
		case 11:return sf::Vector2f(530, 300);//Color btn
		case 12:return sf::Vector2f(100, 100);//
		case 13:return sf::Vector2f(450, 20);//
		case 100:return sf::Vector2f(0, 0);//Color bckground
		default:return sf::Vector2f(0, 0);
		}
	}
	sf::Text text;
	sf::Sprite ObjectSprite;
	bool IsVisible = false;
	int IndexPosition;
protected:
	int ID;

	sf::Vector2f position;
	sf::Texture ObjectTexture;

};