export import <string>;
export import InteractableObject;
export module MenuButton;

export class MenuButton :public InteractableObject
{
public:
	MenuButton(std::string TextureLocation, int pos, int id) :InteractableObject(pos, id) {

		if (!SetSprite(TextureLocation))return;//je¿eli nie wczyta
		position = DecodePosition(pos);
		ObjectSprite.setPosition(position);

	};

	virtual void Active(bool Ac)
	{
		IsActive = Ac;
	}

	virtual bool isButton() { return true; }

	virtual bool isText() { return false; }


};