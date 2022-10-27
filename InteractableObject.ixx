
export import GuiObject;
export module InteractableObject;

export class InteractableObject : public GUIObject
{
public:
	/// <summary>
/// Returns true if object is active
/// </summary>
/// <returns>IsActive</returns>
	virtual void Active(bool Ac) = 0;
	/// <summary>
/// Returns true if object is a text
/// </summary>
/// <returns></returns>
	virtual bool isText() = 0;
	/// <summary>
/// Returns true if object is a button
/// </summary>
/// <returns></returns>
	virtual bool isButton() = 0;
	InteractableObject() {}
	InteractableObject(int pos, int id) :GUIObject(pos, id) {}
	/// <summary>
	/// Checks whitch button was pressed
	/// </summary>
	/// <param name="sign"></param>
	void EneteredFromKeyBoard(char sign)
	{
		if (sign == 8)
			deleteChar();
		else
			addChar(sign);
	}
	/// <summary>
	/// Adds char to active textbox
	/// </summary>
	/// <param name="sign"></param>
	void addChar(char sign)//Do Poprawy
	{
		std::string SText = text.getString();
		if (SText.size() < 15)
		{
			SText += sign;
			text.setString(SText);
		}

	}
	/// <summary>
	/// Deletes char from active text box
	/// </summary>
	void deleteChar()//Do PoprawyF
	{
		std::string SText = text.getString();
		if (SText.size() > 0)
		{
			SText = SText.substr(0, SText.size() - 1);
			text.setString(SText);
		}
	}

	bool IsActive = false;

};
