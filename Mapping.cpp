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
1. SURNAME Othername: Kanhye Ashley Nikheel
2. Student ID: 2015052
3. Programme: BSc (Hons) Computer Science L1, Group B
4. Module: Computer Programming, ICT 1017Y
5. Date: 01 June 2021
6. This is the code to create the mappings and save them to their respective files.
7. All the mappings are stored in lowercase words and all the punctuations are removed from the sentences.
8. The number of mapping words created was 36323.
*/

class Sentences {

    private:

        string sentence;        //string variable to store one sentence
        int numWords;           //integer variable to store the number of words in one sentence
        vector<string> words;

    public:
        Sentences(){};          //constructor
        void setSentence(string s){sentence = s;};

        int getNumWords()       //method to return the number of words in a sentence
        {
            int numChars = sentence.length();
            vector<string> setOfWords;
            string currentWord;
            for(int i=0;i<numChars;i++){
                if(sentence[i] == ' ' && !currentWord.empty()){
                    setOfWords.push_back(currentWord);
                    currentWord.clear();
                }
            else{
                currentWord += sentence[i];
                }
            }

            return (setOfWords.size() + 1);
        }

        vector<string> getWords()   //method to return all the words in a sentence (as a vector)
        {
            int numChars = sentence.length();
            string currentWord;
            words.clear();

            for(int i=0;i<numChars;i++)
            {
                if(sentence[i] == ' ' || sentence[i] == '.' || sentence[i] == '!' || sentence[i] == '?'|| sentence[i]==','|| sentence[i] == '-' ||sentence[i]=='"' )
                {
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
        ~Sentences(){};  //destructor
};

string convert_string_to_lowercase(string s);   //prototype of function to convert string in lowercase characters



//this main will be for creating mapping with corresponding frequencies
int main(){
    cout<<"mapping right now please wait"<<endl;
    string sentence;                                    // a dummy sentence used to input all sentences to their corresponding vector
    int E_sentences_count,km_sentences_count;           //to count the number of sentences in the data set
    vector<string> vector_of_english_sentences;         //to store all the English sentences in the data set
    vector<string> vector_of_km_sentences;              //to store all the KM sentences in the data set

//opening of the file to input all English sentences in vector : vector_of_english_sentences
    ifstream english_f;
    english_f.open("1000_English_B_040521.txt");
    while(!english_f.eof())
    {
        getline(english_f,sentence);
        sentence=convert_string_to_lowercase(sentence);
        vector_of_english_sentences.push_back(sentence);
    }
    english_f.close();

//opening of the file to input all KM sentences in vector : vector_of_km_sentences
    ifstream km_f;
    km_f.open("1000_KM_B_040521.txt");
    while(!km_f.eof())
    {
        getline(km_f,sentence);
        sentence=convert_string_to_lowercase(sentence);
        vector_of_km_sentences.push_back(sentence);
    }
    km_f.close();


//creating the vector of object to store all English sentences in it
    E_sentences_count = vector_of_english_sentences.size();  // to get the number of English sentences in all the dataset
    vector<Sentences> E_sentences(E_sentences_count);       //declaration of vectors of object for English sentences

//creating the vector of object to store all KM sentences in it
    km_sentences_count = vector_of_km_sentences.size();       // to get the number of KM sentences in all the dataset
    vector<Sentences> km_sentences (km_sentences_count);     //declaration of vectors of object for KM sentences


//transferring data from vector :vector_of_english_sentences  to object vector :E_sentences
    for(int i =0 ; i< E_sentences_count;i++)
    {
        E_sentences[i].setSentence(vector_of_english_sentences[i]);   //using set method to transfer each sentence from vector to object vector
    }

//transferring data from vector : vector_of_km_sentences to object vector : km_sentences
    for(int i=0;i<km_sentences_count;i++)
    {
        km_sentences[i].setSentence(vector_of_km_sentences[i]);       //using set method to transfer each sentence from vector to object vector
    }


//the mappings will be stored in 3 individual vectors
//the method .getWords() will be used to get a vector containing the words in each sentences

vector<string> E_words ;    //this will contain the return vector of the .getWords() function for English vector of objects
vector<string> km_words;    //this will contain the return vector of the .getWords() function for km vector of objects

vector<string> map_eng;     //this vector will store mapping of each English word
vector<string> map_km;      //this vector will store mapping of each KM word
vector<int> map_frequency;  //this vector will store the number of times the words have been mapped
bool found = false;         //this will check if the word mapping has been found



//begin of mapping each English word to KM word
//since we have the same number of sentences of English and km , we can use a single and same index
    for(int index =0 ; index < E_sentences_count ; index++)
    {
        E_words = E_sentences[index].getWords();    //take each english sentence and get vector of its words
        km_words = km_sentences[index].getWords();  //take each km sentence and get vector of its words

        //mapping loop
        for(int i =0 ;i< E_words.size() ;i++)  //each English word
        {
            for( int j=0 ;j< km_words.size() ;j++) //each km word
            {
                for(int k=0; k< map_eng.size() ; k++) //going to each position in the mapping vector, the size of all the three map vectors will be the same , so I used only one vectors.size index
                {
                    if(E_words[i] == map_eng[k] && km_words[j] == map_km[k])  //checking if the mapping match for each individual word
                    {
                        map_frequency[k]++; //if it is matched , increment its respective frequency by one
                        found =true;
                    }
                }
                if(found == false)  //means there is no existing match then we need to push back a new mapping set in the mapping vectors
                {
                    map_eng.push_back(E_words[i]);
                    map_km.push_back(km_words[j]);
                    map_frequency.push_back(1);
                }
                found = false;  //reset found for next loop
            }
        }
    }

//opening file for storing the mapping vectors in their respective file.txt
    ofstream f_all_mapping;
    ofstream f_eng_mapping;
    ofstream f_km_mapping;
    ofstream f_frequency_mapping;
    f_eng_mapping.open("mapping for english.txt");
    f_km_mapping.open("mapping for km.txt");
    f_frequency_mapping.open("mapping for frequency.txt");
    f_all_mapping.open("mapping for all.txt");   //this file will only store the English , KM  and their frequency next to each other for illustration

//writing in their respective files
    for(int i=0;i< map_eng.size() ;i++) //i used only one index as all the three vectors will be the same size
    {
        f_eng_mapping<< map_eng[i] <<endl;
        f_km_mapping<<  map_km[i]  <<endl;
        f_frequency_mapping<<  map_frequency[i]  <<endl;
        f_all_mapping<<  map_eng[i] <<"      "<<map_km[i]<<"      "<<map_frequency[i]<<endl;
    }

    f_eng_mapping.close();
    f_km_mapping.close();
    f_all_mapping.close();
    f_frequency_mapping.close();

    cout<<"finished storing mapping please check file in folder"<<endl;

return 0;
}



string convert_string_to_lowercase(string s)    //this function converts a sentence and convert all the words into lowercase
{
    transform(s.begin(),s.end(),s.begin(),::tolower);
    return s;
}

