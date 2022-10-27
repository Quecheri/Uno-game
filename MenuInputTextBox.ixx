
export import InteractableObject;
export module MenuInputTextBox;

export class MenuInputTextBox : public InteractableObject
{
public:
	MenuInputTextBox(std::string TextureLocation, int pos, int id, std::string TextPlaceholder) :Btext(TextPlaceholder),
		InteractableObject(pos, id)
	{
		if (!SetSprite(TextureLocation))return;//je¿eli nie wczyta
		position = DecodePosition(pos);
		ObjectSprite.setPosition(position);
		if (!font.loadFromFile("Fonts/arial.ttf"))return;
		text.setString(TextPlaceholder);
		Inicjalize();
	};
	MenuInputTextBox(std::string TextureLocation, int pos, int id, std::string TextPlaceholder, int OffsetX, int OffsetY) :Btext(TextPlaceholder),
		InteractableObject(pos, id)
	{
		if (!SetSprite(TextureLocation))return;//je¿eli nie wczyta
		position = DecodePosition(pos);
		ObjectSprite.setPosition(position);
		if (!font.loadFromFile("Fonts/arial.ttf"))return;
		text.setString(TextPlaceholder);
		Btext = TextPlaceholder;
		position.x += OffsetX;
		position.y += OffsetY;
		Inicjalize();
	};
	virtual void Active(bool Ac)
	{
		if (Ac == true)
		{
			IsActive = true;
			if (text.getString() == Btext)
				text.setString("");
		}
		else
		{
			IsActive = false;
			if (text.getString() == "")
				text.setString(Btext);
		}
	}
	/// <summary>
	/// Inicjalize Text in text box
	/// </summary>
	void Inicjalize()
	{
		text.setFont(font);
		text.setFillColor(sf::Color(192, 192, 192));
		text.setStyle(sf::Text::Italic);
		text.setCharacterSize(20);
		text.setPosition(position);
	}
	virtual bool isButton() { return false; }
	virtual bool isText() { return true; }
private:
	sf::Font font;
	std::string Btext;

};