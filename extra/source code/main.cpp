#include <iostream>
#include "../public/keyvalues.h"
#include <thread>
#include <map>

class MapaddMaker
{
public:
	MapaddMaker()
	{
		MainKv = new keyvalues();
	}

	void Init()
	{
		InitMapadd();
	}

private:
	void InitMapadd()
	{
		DisplayKeyvalueData(MainKv);
	}

	keyvalues* AddSubkey(keyvalues* m_bPrev)
	{
		std::cout << "Name: ";
		std::cin >> std::ws;
		std::string name;
		std::getline(std::cin, name);
		keyvalues* kv = new keyvalues(name);
		m_bPrev->AddKeyvalues(kv);
		return kv;
	}

	keyvalues* AddKvPair(keyvalues* m_bPrev)
	{
		std::cout << "Name: ";
		std::cin >> std::ws;
		std::string name;
		std::getline(std::cin, name);
		std::cout << "Value: ";
		std::string value;
		std::cin >> std::ws;
		std::getline(std::cin, value);
		keyvalues* kv = new keyvalues(name, value);
		m_bPrev->AddKeyvalues(kv);
		return kv;
	}

	void DisplayKeyvalueData(keyvalues* kv)
	{
		system("cls");
		if (kv != MainKv)
		{
			int i = 0;
			std::cout << "Current Keyvalue Name: " << kv->GetName() << '\n';

			if (!kv->IsSubkey())
				std::cout << "Current Keyvalue Value: " << kv->GetString() << '\n';

			std::cout << "Is Subkey: " << (kv->IsSubkey() ? "true" : "false") << '\n';
			std::cout << "Keyvalues:\n";

			std::map<int, keyvalues*> KVMAP;
			FOR_EACH_KEYVALUE(kv, kvs)
			{
				std::cout << i << ": " << kvs->GetName() << (!kvs->IsSubkey() ? " With Value " : "") << (!kvs->IsSubkey() ? kvs->GetString() : "") << (kvs->IsSubkey() ? " Is A Subkey" : " Is A Keyvalue Pair") << '\n';
				KVMAP[i] = kvs;
				i++;
			}
			std::cout << '\n';
			std::cout << "Options:\n";

			int adsbk = INT_MAX, adkv = INT_MAX, PrevSub, StName, StVle = INT_MAX, CLEARKV = INT_MAX, DT, QUIT
				;
			if (kv->IsSubkey())
			{
				std::cout << i << ": Add Subkey\n";
				adsbk = i;
				i++;
				std::cout << i << ": Add Keyvalue Pair\n";
				adkv = i;
				i++;
			}

			std::cout << i << ": Set Name\n";
			StName = i;

			if (!kv->IsSubkey())
			{
				i++;
				std::cout << i << ": Set Value\n";
				StVle = i;
			}

			if (kv->IsSubkey() && !kv->IsEmpty())
			{
				i++;
				std::cout << i << ": Clear Keyvalue Content Inside This\n";
				CLEARKV = i;
			}

			i++;
			std::cout << i << ": Delete This\n";
			DT = i;

			i++;
			std::cout << i << ": Go Back To Previous Subkey\n";
			PrevSub = i;

			i++;
			std::cout << i << ": Quit\n";
			QUIT = i;

			int Input;
			std::cin >> Input;

			if (Input == INT_MAX)
				exit(1);

			if (KVMAP.find(Input) != KVMAP.end())
			{
				DisplayKeyvalueData(KVMAP[Input]);
			}
			else if (Input == adsbk)
			{
				keyvalues* add = AddSubkey(kv);
				DisplayKeyvalueData(add);
			}
			else if (Input == adkv)
			{
				keyvalues* add = AddKvPair(kv);
				DisplayKeyvalueData(kv);
			}
			else if (Input == DT)
			{
				std::cout << "Are You Sure: Y = yes\n";
				std::string c;
				std::cin >> c;

				if (c == "Y" || c == "y")
				{
					keyvalues* kv2 = kv->m_bPrev;
					kv->DeleteThis();
					DisplayKeyvalueData(kv2);
				}
				else
				{
					DisplayKeyvalueData(kv);
				}
			}
			else if (Input == CLEARKV)
			{
				std::cout << "Are You Sure You Want To Clear All Keyvalue Content Inside This: Y = yes N = no\n";
				std::string c;
				std::cin >> c;

				if (c == "Y" || c == "y")
				{
					std::string name = kv->GetName(), val = kv->GetString();
					bool IsSub = kv->IsSubkey();
					kv->DeleteThis();

					kv = new keyvalues(name, val);
					kv->SetIsSubkey(IsSub);
					DisplayKeyvalueData(kv);
				}
				else if (c == "N" || c == "n")
				{
					DisplayKeyvalueData(kv);
				}
				else
				{
					std::cout << "Error Expected Y or N But Got " << c << '\n';
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					DisplayKeyvalueData(kv);
				}
			}
			else if (Input == PrevSub)
			{
				if (!kv->m_bPrev || kv == MainKv)
				{
					std::cerr << "Error Couldnt Find Previous Subkey\n";
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					DisplayKeyvalueData(kv);
				}

				DisplayKeyvalueData(kv->m_bPrev);
			}
			else if (Input == StName)
			{
				std::cout << "Name: ";
				std::string name;
				std::cin >> std::ws;
				std::getline(std::cin, name);
				kv->SetName(name);
				DisplayKeyvalueData(kv);
			}
			else if (Input == StVle)
			{
				std::cout << "Value: ";
				std::string Value;
				std::cin >> std::ws;
				std::getline(std::cin, Value);
				kv->SetString(Value);
				DisplayKeyvalueData(kv);
			}
			else if (Input == QUIT)
			{
				std::cout << "Are You Sure: \n0: yes\n1: no\n";
				int qas;
				std::cin >> qas;
				if (qas == 0)
				{
					exit(0);
				}
				else if (qas == 1)
				{
					DisplayKeyvalueData(kv);
				}
				else
				{
					DisplayKeyvalueData(kv);
				}
			}
		}
		else
		{
			int i = 0;
			std::map<int, keyvalues*> KVMAP;
			std::cout << "Currently In Main Keyvalues\n";
			std::cout << "Keyvalues:\n";

			FOR_EACH_KEYVALUE(kv, kvs)
			{
				std::cout << i << ": " << kvs->GetName() << (!kvs->IsSubkey() ? " With Value " : "")  << (!kvs->IsSubkey() ? kvs->GetString() : "") << (kvs->IsSubkey() ? " Is A Subkey" : " Is A Keyvalue Pair") << '\n';
				KVMAP[i] = kvs;
				i++;
			}
			std::cout << "\nOptions:\n";

			int SAQ, SAQ1, CLEARKV = INT_MAX, adsbk, adkv, OF, QUIT, DKT = INT_MAX;
			std::cout << i << ": Add Subkey\n";
			adsbk = i;
			i++;
			std::cout << i << ": Add Keyvalue Pair\n";
			adkv = i;
			i++;
			std::cout << i << ": Open File\n";
			OF = i;
			i++;

			if (!MainKv->IsEmpty())
			{
				std::cout << i << ": Clear All Keyvalue\n";
				CLEARKV = i;
				i++;
			}

			std::cout << i << ": Save To File\n";
			SAQ = i;
			i++;
			std::cout << i << ": Save And Quit\n";
			SAQ1 = i;
			i++;

			if (!MainKv->IsEmpty())
			{
				std::cout << i << ": Display Keyvalue Tree\n";
				DKT = i;
				i++;
			}
			std::cout << i << ": Quit\n";
			QUIT = i;

			int Input;
			std::cin >> Input;
			if (Input == INT_MAX)
				exit(1);

			if (KVMAP.find(Input) != KVMAP.end())
			{
				DisplayKeyvalueData(KVMAP[Input]);
			}
			else if (Input == adsbk)
			{
				keyvalues* add = AddSubkey(kv);
				DisplayKeyvalueData(add);
			}
			else if (Input == adkv)
			{
				keyvalues* add = AddKvPair(kv);
				DisplayKeyvalueData(MainKv);
			}
			else if (Input == QUIT)
			{
				std::cout << "Are You Sure: \n0: yes\n1: no\n";
				int qas;
				std::cin >> qas;
				if (qas == 0)
				{
					exit(0);
				}
				else if (qas == 1)
				{
					DisplayKeyvalueData(MainKv);
				}
				else
				{
					DisplayKeyvalueData(MainKv);
				}
			}
			else if (Input == DKT)
			{
				std::string kvtree = MainKv->WriteToString();
				std::cout << kvtree;
				std::cout << "Any Key Then Enter: return";
				std::string input;
				std::cin >> input;
				DisplayKeyvalueData(MainKv);
			}
			else if (Input == OF)
			{
				std::cout << "Do You Want To Save\n";
				std::cout << "0: yes\n";
				std::cout << "1: no\n";
				std::cout << "2: return\n";

				int qas;
				std::cin >> qas;
				if (qas == 0)
				{
					std::cout << "Save To: ";
					std::string name;
					std::cin >> std::ws;
					std::getline(std::cin, name);
					MainKv->WriteToFile(name);
					MainKv->DeleteThis();
					MainKv = new keyvalues();
					bool IsFile = true;
					while (IsFile)
					{
						system("cls");
						std::cout << "0: Restart Keyvalue Maker\n";
						std::cout << "Open File: ";
						std::string fname;
						std::cin >> std::ws;
						std::getline(std::cin, fname);
						if (fname == "0")
						{
							DisplayKeyvalueData(MainKv);
						}
						else
						{
							std::ifstream file(fname);
							if (!file.is_open())
							{
								std::cout << "Error Opening File: " << fname << '\n';
								std::this_thread::sleep_for(std::chrono::milliseconds(1000));
								continue;
							}
							else
							{
								MainKv->OpenFile(fname);
								DisplayKeyvalueData(MainKv);
							}
						}
					}
				}
				else if (qas == 1)
				{
					bool IsFile = true;
					while (IsFile)
					{
						system("cls");
						std::cout << "0: Restart Keyvalue Maker\n";
						std::cout << "Open File: ";
						std::string fname;
						std::cin >> std::ws;
						std::getline(std::cin, fname);
						if (fname == "0")
						{
							DisplayKeyvalueData(MainKv);
						}
						else
						{
							std::ifstream file(fname);
							if (!file.is_open())
							{
								std::cout << "Error Opening File: " << fname << '\n';
								std::this_thread::sleep_for(std::chrono::milliseconds(1000));
								continue;
							}
							else
							{
								MainKv->OpenFile(fname);
								DisplayKeyvalueData(MainKv);
							}
						}
					}
				}
				else if (qas == 2)
				{
					DisplayKeyvalueData(MainKv);
				}
				else
				{
					DisplayKeyvalueData(MainKv);
				}
			}
			else if (Input == CLEARKV)
			{
				std::cout << "Are You Sure You Want To Clear All Keyvalue Data: Y = yes N = no\n";
				std::string c;
				std::cin >> c;

				if (c == "Y" || c == "y")
				{
					MainKv->DeleteThis();
					MainKv = new keyvalues();
					DisplayKeyvalueData(MainKv);
				}
				else if (c == "N" || c == "n")
				{
					DisplayKeyvalueData(MainKv);
				}
				else
				{
					std::cout << "Error Expected Y or N But Got " << c << '\n';
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					DisplayKeyvalueData(MainKv);
				}
			}
			else if (Input == SAQ)
			{
				std::cout << "0: Return\n";
				std::cout << "Save To File: ";
				std::string Value;
				std::cin >> std::ws;
				std::getline(std::cin, Value);
				if (Value == "0")
					DisplayKeyvalueData(MainKv);
				else
				{
					kv->WriteToFile(Value);
					std::cout << "Saved To File: " << Value << '\n';
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					DisplayKeyvalueData(MainKv);
				}
			}
			else if (Input == SAQ1)
			{
				std::cout << "0: Return\n";
				std::cout << "Save To File: ";
				std::string Value;
				std::cin >> std::ws;
				std::getline(std::cin, Value);
				if (Value == "0")
					DisplayKeyvalueData(MainKv);
				else
				{
					kv->WriteToFile(Value);
					std::cout << "Thanks For Using Keyvalue Maker\n";
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					exit(0);
				}
			}
			else
			{
				DisplayKeyvalueData(MainKv);
			}
		}
	}

private:
	keyvalues*MainKv;
};

int main()
{
	MapaddMaker mapadd;
	mapadd.Init();
}