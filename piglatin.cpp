/*
 * File:   piglatin.cpp
 * Author: Percy George Brown
 *
 * Created on 19 April 2020, 14:31
 */

#include <iostream>

using namespace std;

const int MAX = 43;

//forward declaration of functions

char* convertToPL(char* word);
int Check(char letter);
int Check_y(char alpha);
bool Check_Upper(char c);

/*
*The main method accepts 5 words of maximum length 43 as inputs
*And converts them to Pig Latin
*/

int main()
{
   // creation of 5 character strings, each length MAX
   char word[5][MAX];
   int i;				// loop counter

   cout << "Input 5 words: ";
   for (i = 0; i < 5; i++)
       cin >> word[i];

   cout << "\nPig Latin version of the 5 words:\n";
   for (i = 0; i < 3; i++)
   {
      convertToPL(word[i]);
      cout << word[i] << ' ';
   }
   /* Note that the above outputs illustrate that the original
   string itself has been converted.  The outputs below illustrate
   that a pointer to this string is also being returned from the
   function.*/

   cout << convertToPL(word[3]) << ' '
        << convertToPL(word[4]) << '\n';

   return 0;
}

// Write your definition of the convertToPL function here

char* convertToPL(char* word){
    bool capital = Check_Upper(word[0]);            //check whether a word begins with a capital letter

    /*
    *only words that begin with capital letter will have their latin form's first letter capitalized
    *for easier work, just convert all to small letters
    */

    for(int i = 0; i < sizeof(word)/sizeof(word[0]); i++){
        word[i] = tolower(word[i]);
    }

    /*
    *Since the word's capacity may not have been exhausted, we need to know the next available space
    *This code below finds the next free space after the last element in the array
    *And stores its index
    */

    int last;
    for(int i = 0; i < MAX; i++){
        if(word[i]==' ' || word[i] == '\0'){       //if the next element is empty
            last = i;
            break;
        }
    }

    /*
    *The few lines below check if the word starts with a vowel
    *Does not consider "y" as a verb when it starts the word
    *The word is maintained with "way" added
    */

    if(Check(word[0]) == 1){
        string extra = "way";     //additional characters to add
        word[last] = extra[0];
        word[last+1] = extra[1];
        word[last+2]= extra[2];
        word[last+3] = '\0';     //move the next free space
    }

    /*
    *If the letter does not begin woth a vowel, it begins with a consonant obviously
    *Checks for a vowel or a "y" after the first letter
    *A new array is created of the same capacity to aid in the conversion to latin
    *Performs necessary transformation to latin form
    *Copies the latin from back to the original array to be returned
    */

    else{
        int start = 0;
        char NEWARRAY[MAX];                  //new array of same capacity
        int pos;

        //Checking if the word contains vowel or a y and storing its index

        for(int i = 0; i < last; i++){
            if((Check(word[i]) == 1) || (Check_y(word[i])==1)){
                pos = i;
                break;
            }
        }

        // Copy the letters from the vowel or "y" found to the end of the word into the new array

        for(int k = pos; k < last; k++)
            NEWARRAY[start++] = word[k];

        // Similarly, copy from the begining of the word to the last letter before the vowel or "y" into new array

        for(int x = 0; x < pos; x++)
            NEWARRAY[start++] = word[x];

        /*
        *Note the variable last. Since no new character has been added yet, the empty space index for the old array would be same as the new array
        *Now add "ay" to the characters in the new array
        */

        for( int d = last; d < MAX; d++){
            string add = "ay";      //what to add
            NEWARRAY[last] = add[0];
            NEWARRAY[last+1] = add[1];
            NEWARRAY[last+2] = '\0';       //move the next free space backwards
            break;
        }

        /*
        *The conversion into latin form was made in the new array
        *It is time to copy them back to the old array
        *The original from of the word is overwritten in the new array
        */

        for(int p = 0; p < MAX; p++)
            word[p] = NEWARRAY[p];                    //transfer everything from new array to old array
    }

    //if the word began with a capital letter, convert the first letter of the latin form to a capital letter

    if(capital)
        word[0] = toupper(word[0]);

    return word;          //return latin form in old array
}

/*
*This function checks whether or not a character is a vowel
*Assume that the word has been converted into small letters
*Returns 1 when true, and 0 otherwise
*/

int Check(char letter){
    if((letter=='a')||(letter=='e')||(letter=='i')||(letter=='o')||(letter=='u'))
        return 1;
    else{
        return 0;
    }
}

/*
*For words that do not begin woth vowels, this function checks whether they contain "y" and treats it as a verb
*Returns 1 when true and 0 otherwise
*/

int Check_y(char alpha){
    if((alpha == 'y'))
        return 1;
    else{
        return 0;
    }
}

/*
*This function checks whether or not a character is capital
*Returns true when true, and false otherwise
*/

bool Check_Upper(char c){
    if(isupper(c))
        return true;
    else{
        return false;
    }
}


