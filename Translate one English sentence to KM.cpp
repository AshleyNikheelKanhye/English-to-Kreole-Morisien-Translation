#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

/*
1.  SURNAME Othername: Kanhye Ashley Nikheel
2. Student ID: 2015052
3. Programme: BSc (Hons) Computer Science L1, Group B
4. Module: Computer Programming, ICT 1017Y
5. Date: 01 June 2021
6. This is the code to translate an input English sentence into Kreole Morisien.
7. The input sentence is broken into lower case words and stored in a vector to check each English word corresponding KM word.
*/

//this part of program assumes that mapping of the English words to Km words have already been done
//this main will translate an input English sentence and will convert it to Km using the mapping dataset ( the mapping files .txt)
//the main will fetch the text files which stores the mapping and will place them in appropriate vectors
//then it will use multiple for loops to look the KM word for an English word with the highest frequency
//the highest frequency mapped word will then be pushed back to a vector which will be the translated sentence

string convert_string_to_lowercase(string s)    //this function converts a sentence and convert all the words into lowercase
{
    transform(s.begin(),s.end(),s.begin(),::tolower);
    return s;
}



vector<string> getWords(string sentence)  //function of type vector (same as the method in the class sentence)
{
    vector<string>words;
    string currentWord;
    words.clear();

    for(int i=0 ; i<sentence.length() ; i++)
    {
        if(sentence[i] == ' ' || sentence[i] == '.' || sentence[i] == '!' || sentence[i] == '?'|| sentence[i]==','|| sentence[i] == '-' ||sentence[i]=='"' ){
            if(currentWord !="")
            {
                words.push_back(currentWord);
            }
            currentWord.clear();
        }
        else
        {
            currentWord += sentence[i];
        }
    }

    return words;
}


int main()
{
    bool again =true;
    int number;
    int choice;
    vector<string>  INPUT_sentenceWords;   //vector to store the words of the input sentence
    vector<string> translatedWords;  //vector to store the words of the translated sentence

    string inputsentence,dummysentence;

    //creating vector to store the data from the file mapping
        vector<string>eng_map;
        vector<string>km_map;
        vector<int>frequency_map;

    //opening the files of mapping
        ifstream eng_f;
        ifstream km_f;
        ifstream frequency_f;
        eng_f.open("mapping for english.txt");
        km_f.open("mapping for km.txt");
        frequency_f.open("mapping for frequency.txt");

    //Transferring data from the text files to vector respectively
        while(!eng_f.eof())
        {
            getline(eng_f,dummysentence);
            eng_map.push_back(dummysentence);
        }
        eng_f.close();

        while(!km_f.eof())
        {
            getline(km_f,dummysentence);
            km_map.push_back(dummysentence);
        }
        km_f.close();

        while(!frequency_f.eof())
        {
            frequency_f>>number;
            frequency_map.push_back(number);
        }
        frequency_f.close();



    //begin of searching words per words in the vectors of mapping
    //the algorithm will select the words with the most hits(i.e. frequency number) and for that english word
    //the km word will be pushed back in the vector translated word
    //we can use the same vector size for looping as all the mappings are the same size
    //A while loop will keep running until the user does not want to translate more sentences

    cout<<"welcome to translation of English to KM , press enter to continue "<<endl;
while (again ==true)
    {
        cin.ignore();
        cout<<"enter the English sentence you want to translate to Kreole Morisien "<<endl;
        getline(cin,inputsentence);
        if (inputsentence.find(".") == -1)
        {
            inputsentence= inputsentence+".";  //to make sure that every string ends with a dot
        }

        inputsentence=convert_string_to_lowercase(inputsentence);   //convert the input string to all lower case to enhance mapping
        INPUT_sentenceWords=getWords(inputsentence);   //breaking the input English sentence into words in a vector using the function getWords

            int max_Hz_counter = 0;
            for(int i=0 ;i< INPUT_sentenceWords.size() ;i++)  //each english input word
            {
                for(int j=0 ;j< eng_map.size() ;j++)       //each english mapped word
                {
                    if( INPUT_sentenceWords[i] == eng_map[j])
                    {
                        if(frequency_map[j] > max_Hz_counter)  //checking if it this is the highest frequency of this word
                        {
                            max_Hz_counter=frequency_map[j];
                            dummysentence=km_map[j];
                        }
                    }
                }
                if(max_Hz_counter==0)
                {
                    translatedWords.push_back( INPUT_sentenceWords[i]);    //that means that there is no such word in the mapping list
                }
                else{ translatedWords.push_back(dummysentence);}    //that means that the word is found and pushed back in the vector
                max_Hz_counter=0;   //reset counter
            }

            //displaying the translated words
                cout<<"the translated word is  : ";
                for(int i=0;i< translatedWords.size();i++)
                {
                    cout<<translatedWords[i]<<" ";
                }

                translatedWords.clear();

        cout<<endl;
        cout<<endl;
        cout<<"Do you want to translated other English sentences into KM ? "<<endl;
        cout<<" Yes : 1  ,  No : 0 "<<endl;
        cin>>choice;

        while(choice != 1 & choice !=0)
        {
            cout<<"enter only 1 or 0 ..... Yes : 1  ,  No : 0 "<<endl;
            cin>>choice;
        }

        if (choice == 0)
        {
            again = false;
        }


    }

return 0;
}
