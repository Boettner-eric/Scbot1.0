#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>
#include <string>
#include <stdio.h>



using namespace std;
using namespace std::chrono;  // for later function (play timer ~1 min each set of 7 letters)
using std::chrono::system_clock;
using namespace std::this_thread;

bool is_word(string tmp); // checks against the dictionary
void get(string str, string tmp); // linear check function = works for < 7 char
string randl(string str); // random check function works for all charactors and can set time


int main()
{
    string str, tmp[15000], tlp = "";
    ifstream answers, words, import;
    ofstream results, testing;
    int score[1500], l=0, x=0, points[27] = {0,1,2,2,2,1,4,2,4,1,8,5,1,2,1,1,2,10,1,1,1,1,4,4,8,4,10};
    char p;
    cout << "isword() - find() \nMode? (f / n) ";
    cin >> p;
    if (p == 'F' or p == 'f')
    {
        cout << "\nEnter Word : ";
        cin >> str;
        if (is_word(str) == 0) {
            cout << "False";
        }
        else
        {
            cout << "True";
        }
        cout << "\nEnd \n";
    }
    else if (p == 'N' or p == 'n')
    {
        results.open("results.txt");
        results << "";
        results.close();

        do {
            cout << "word generator\n\nenter any (1 - 10) letters * longer sequences take exponential time : ";
            cin >> str;
            system("clear");
        } while(str.length() > 12);

        std::clock_t start; double duration;
        start = std::clock();
        get(str, "");

        cout << " \n\n ** PROCESS COMPLETE **\n s  - word";
        answers.open("results.txt");
        l=0;
        while (!answers.eof())
        {
            score[l] = 0;
            getline(answers, tmp[l]);
            for(x=0;x<tmp[l].size();x++)
            {
                tlp = tmp[l];
                score[l] += points[(int) tlp[x] -96]; // translates ASCII values to ints to add to the score
            }
            l++;
        }
        answers.close();

        for (int i=0; i<l; i++)
        {
            for (int x=0; x<l-1; x++)
            {
                if(score[x]>score[x+1])
                {
                    int temp=score[x+1];
                    string tmmp=tmp[x+1];
                    score[x+1]=score[x];
                    tmp[x+1]= tmp[x];
                    score[x]=temp;
                    tmp[x]=tmmp;
                }
            }
        }

        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

// add in checks for duplicate answers here

        for(x=l;x>0;x--)
        {
          if (score[x] != 0) {
            cout << "\n " << left << setw(2) << score[x] << " - "<< tmp[x];
          }

        }

        cout << "\n\n " <<  l-1 << " results : " << setprecision(2) << duration << " seconds\n";
        cout << "   best word : "<< tmp[l-1] <<"\n\n";
        testing.open("debug.txt", ios::app);
        testing << left << setw(4) << str.length() << " : " << setw(8) << str << " : " << setw(5) << l << " : ";
        testing << left << setw(8) << setprecision(2) << duration << " : best word : " << tmp[l-1] << "\n";
        testing.close();
    }
    return 0;
}

void get(string str, string tmp)
{
    ofstream answer;
    for( int i = 0; i < str.length(); i++ )
        get(string(str).erase(i,1), tmp + str[i]); // recursive

    if (tmp.size() > 2)
    {
        if (is_word(tmp) == true)
        {
            cout << "." << flush;
            answer.open("results.txt", ios::app);
            answer << "\n" << tmp;
            answer.close();
        }
    }
}

bool is_word(string tmp) //checks against the dictionary
{
    bool yn = false;
    string * dictionary, ty = "";
    int l=0;
    char first;
    dictionary = new string [17501]; // ( 17,500 words in text file )
    ifstream words; // ( words : file for dictionary )

    int x;
    first = tmp[0];

    for (x=97;x<123;x++) // 97-123 = alphas
    if (int(first) == char(x))
    {
        ty = "dict/dict_";
        ty += char(x);
        ty += ".txt";
        words.open(ty); //opens dictionary file for first letter
        break;
    }
    while(!words.eof())
    {
        getline(words, dictionary[l]);
        if (dictionary[l] == tmp  && tmp != "" && tmp.length() != 1)
        {
            yn = true;
            break;
        }
    }
    words.close();
    delete [] dictionary; // does this save me memory? - I am still new to pointers
    return yn;
}
