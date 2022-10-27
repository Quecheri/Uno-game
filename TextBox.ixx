
export import NotInteractableObject;
export module TextBox;

export class TextBox : public NotInteractableObject
{
public:
	TextBox(std::string BasicText, int pos, int Id) :NotInteractableObject(pos, Id)
	{
		if (!font.loadFromFile("Fonts/arial.ttf"))return;
		text.setString(BasicText);
		position = DecodePosition(pos);
		Inicjalize();
	};
	TextBox(std::string BasicText, int pos, int Id, std::string FontPath) :NotInteractableObject(pos, Id)
	{
		if (!font.loadFromFile(FontPath))return;
		text.setString(BasicText);
		position = DecodePosition(pos);
		Inicjalize();
	};
	TextBox(std::string BasicText, int pos, int Id, int OffsetX, int OffsetY) :NotInteractableObject(pos, Id)
	{
		if (!font.loadFromFile("Fonts/arial.ttf"))return;
		text.setString(BasicText);
		position = DecodePosition(pos);
		position.x += OffsetX;
		position.y += OffsetY;
		Inicjalize();

	};
	/// <summary>
	/// Inicjalize fonts
	/// </summary>
	void Inicjalize()
	{
		text.setFont(font);
		text.setFillColor(sf::Color::Red);
		text.setPosition(position);
	}
private:

	sf::Font font;

};