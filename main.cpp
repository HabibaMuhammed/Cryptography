
#include <iostream>
#include <vector>
#include <string>
#include "algorithm_menue.h"
//#include "algorithm_menue.cpp"

using namespace std;
vector<string> algorthim{
    {"Ceaser"},
    {"Monoalphabetic"},
    {"Play fair"},
    {"Hill Algorithm"},
    {"Repeated key"},
      {"Auto key"},
      {"Railfence"},
       {"Coloumnar"},
       {"DES"},
       {"AES"},
       {"RSA"},
        {"MD5"},
        {"QUIT"}
};
int main()
{

    int logout = 1;
    int choice = 1;

    cout << "                                                    WELCOME !!                        " << endl;
    cout << "                                            IN OUR Cryptgraphy System              " << endl;
    puts("                                 *******************************************************");
    cout << "Choose your needed algorithm FROM THIS LIST" << endl;
    puts("*******************************************************"); // 55
    while (choice != 0)
    {
        for (int i = 0; i < algorthim.size(); i++)
        {
            if (i == 12)
            {
                cout << 0 << "-> " << algorthim[i] << endl;
                break;
            }
            cout << i + 1 << "-> " << algorthim[i] << endl;
        }
        puts("*******************************************************");
        cout << "Please enter your choice" << endl;
        bool aux = true;
        cin.exceptions(std::istream::failbit);
        do {
            try {

                cin >> choice;
                aux = true;
            }
            catch (std::ios_base::failure& fail) {
                aux = false;
                cout << "PLEASE INSERT A VALID OPTION." << endl;
                cin.clear();
                std::string tmp;
                getline(cin, tmp);
            }
        } while (aux == false);
        switch (choice)
        {
        case 1:
        {
            CeaserAlgo();
            break;
        }
        case 2:
        {
            MonoalphabticAlgo();
            break;
        }
        case 3:
        {
            PlayfairAlgo();
            break;
        }
        case 4:
        {
            HillAlgo();
            break;
        }
        case 5:
        {
            RepeatedkeyAlgo();
            break;
        }
        case 6:
        {
            AutokeyAlgo();
            break;
        }
        case 7:
        {
            RailFenceAlgo();
            break;
        }
        case 8:
        {
            ColumnarAlgo();
            break;
        }
        case 9:
        {   Des_Algo();
        break;
        }
        case 10:
        {
            AESAlgo();
            break;
        }
        case 11:
        {
            RSAAlgo();
            break;
        }
        case 12:
        {
            MD5Algo();
            break;
        }
        }

        return 0;
    }
}