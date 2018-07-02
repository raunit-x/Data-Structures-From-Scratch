#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class TrieNode
{
public:
    
    char data;
    TrieNode ** children;
    bool isTerminal;
    
    //Constructor
    TrieNode(char data)
    {
        this -> data = data;
        isTerminal = false;
        children = new TrieNode*[26];
        for(int i = 0; i < 26; i++)
        {
            children[i] = NULL;
        }
    }
};


class Trie
{
    TrieNode * root;
    int count;
public:
    
    Trie()
    {
        count = 0;
        root = new TrieNode('/0');
    }
    
private:
    void insertWordHelper(TrieNode * node, string word)
    {
        if(word.size() == 0)
        {
            root -> isTerminal = true;
            return;
        }
        
        int index = word[0] - 'a';
        TrieNode * child;
        if(root -> children[index] != NULL)
        {
            child = root -> children[index];
        }
        else
        {
            child = new TrieNode(word[0]);
            root -> children[index] = child;
        }
        
        insertWordHelper(child ,word.substr(1));
    }
public:
   void insertWord( string word)
    {
        if(!search(root, word))
            count++;
        insertWordHelper(root, word);
    }
    
    bool search(TrieNode * root,string word)
    {
        // base case
        if(word.size() == 1)
        {
            int index = word[0] - 'a';
            if(root -> children[index] != NULL &&  root -> children[index] ->isTerminal)
            {
                return true;
            }
            else return false;
        }
        
        int index = word[0] - 'a';
        if(root -> children[index] != NULL)
        {
            return search(root -> children[index], word.substr(1));
        }
        else return false;
    }
    
    void removeWord(TrieNode * root, string word)
    {
        if(word.length() == 0)
            return;
        if(word.length() == 1)
        {
            int index = word[0] - 'a';
            if(root -> children[index] -> isTerminal)
            {
                root -> children[index] -> isTerminal = false;
            }
        }
        int index = word[0] - 'a';
        TrieNode * child;
        if(root -> children[index])
            child = root -> children[index];
        else return;
        removeWord(child, word.substr(1));
        
        
        if(child -> isTerminal == false)
        {
            for (int i = 0 ; i < 26; i++)
            {
                if(child -> children[i] != NULL)
                    return;
                else continue;
            }
        }
        delete child;
        root -> children[index] = NULL;
    }
    void removeWord(string word)
    {
        if(search(root, word))
            count--;
        removeWord(root, word);
    }
    
    int countWords()
    {
        return count;
    }
   
    
   
    
};


void autoComplete(vector<string> input, string pattern)
{
    for(int i = 0; i < input.size(); i++)
    {
        int k = 0;
        while(input.at(i)[k] == pattern[k])
        {
            k++;
        }
        if(k >= pattern.size())
        {
            cout << input.at(i) << endl;
        }
        else continue;
    }
        
}
int main()
{
    vector<string> vect;
    vect.push_back("abc");
    vect.push_back("abcd");
    vect.push_back("abcderd");
    vect.push_back("abdc");
    string word = "abc";
    autoComplete(vect, word);
    return 0;
}
