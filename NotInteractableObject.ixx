export import GuiObject;
export module NotInteractableObject;
export class NotInteractableObject : public GUIObject
{
public:
	NotInteractableObject(int pos, int id) :GUIObject(pos, id) {}
	NotInteractableObject(std::string TextureLocation, int pos, int id) :GUIObject(pos, id) {
		if (!SetSprite(TextureLocation))return;//je¿eli nie wczyta
		position = DecodePosition(pos);
		ObjectSprite.setPosition(position);
	}

};
