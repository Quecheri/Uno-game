export import <vector>;
export import <string>;

export import KartaNormalna;
export import KartaSpecjalna;
export module ZestaweKart;

export class ZestawKart
{
public:
	/// <summary>
	/// Returns Collection
	/// </summary>
	/// <returns></returns>
	std::vector<std::unique_ptr<Karta>>* getCollection() { return &Collection; }
	/// <summary>
	///  puts card on top of collection
	/// </summary>
	/// <param name="karta"></param>
	void PutOnTop(std::unique_ptr<Karta>& karta)
	{
		Collection.push_back(move(karta));
	}
	/// <summary>
	/// returns true if size=0
	/// </summary>
	/// <returns></returns>
	bool isEmpty() {
		if (Collection.size() == 0)return true;
		else return false;
	}
	/// <summary>
	/// Shuffles Deck ShuffleNumber times
	/// </summary>
	/// <param name="ShuffleNumber"></param>
	void PerfectShuffle(int ShuffleNumber)
	{
		std::vector<std::unique_ptr<Karta>> TempCollection;
		//n razy dla zadanego stopnia potasowania
		for (int i = 0; i < ShuffleNumber; i++)
		{
			shuffle(Collection, TempCollection);
			shuffle(TempCollection, Collection);
		}
	}
	/// <summary>
	/// Shuffle using seed
	/// </summary>
	/// <param name="seed"></param>
	void RandomizeStartingPostions(std::string& seed)
	{
		std::vector<std::unique_ptr<Karta>> TempCollection;
		//n razy dla zadanego stopnia potasowania
		ShuffleFromSeed(Collection, TempCollection, seed);
		ShuffleFromSeed(TempCollection, Collection, seed);
		ShuffleFromSeed(Collection, TempCollection, seed);
		ShuffleFromSeed(TempCollection, Collection, seed);

	}
private:
	/// <summary>
	/// for half of capacity Push first and middle card to new vector 
	/// 
	/// </summary>
	/// <param name="first"></param>
	/// <param name="second"></param>
	void shuffle(std::vector<std::unique_ptr<Karta>>& first, std::vector<std::unique_ptr<Karta>>& second)
	{
		for (int i = 0; i < first.size() / 2; i++)
		{
			second.push_back(move(first[i]));
			second.push_back(move(first[(first.size() / 2) + i]));
		}
		first.clear();
	}
	/// <summary>
/// Shuffles based on seed
/// </summary>
/// <param name="first"></param>
/// <param name="second"></param>
	void ShuffleFromSeed(std::vector<std::unique_ptr<Karta>>& first, std::vector<std::unique_ptr<Karta>>& second, std::string& seed)
	{
		int GeneratedNum = 0;
		int Seedlength = seed.length();
		int firstSize = first.size();
		if (seed[Seedlength - 1] == '$')
		{
			seed = seed.substr(0, seed.size() - 1);
			Seedlength--;
		}
		if (Seedlength == 1)seed += "1";
		int i = 0;
		while (firstSize > 0)
		{
			if (i == Seedlength-1)i = 0;
			GeneratedNum=(seed[i]-'0')*(seed[i+1] - '0');
			if (firstSize <= GeneratedNum)GeneratedNum = firstSize-1;
			second.push_back(move(first[GeneratedNum]));
			if(GeneratedNum!=firstSize-1)
				first[GeneratedNum] = move(first[firstSize - 1]);
			first.pop_back();
			i++;
			firstSize = first.size();
		}
		first.clear();
	}
protected:
	std::vector<std::unique_ptr<Karta>> Collection;
};

