//hashcodeimplementation.
//tested.
#include <iostream>
#include <string>

using namespace std;

//LinkedList involviing the bucket array implementation
template<typename V>
class MapNode
{
public:
    string key;
    V value;
    MapNode<V> * next;
    //constructor
    MapNode(string key, V value)
    {
        this -> key = key;
        this -> value = value;
        this -> next = NULL;
    }
    
    // recursive destructor
    ~MapNode()
    {
        delete next;
    }
};


template<typename V>
class ourMap
{
    MapNode<V>** bucket;
    int count;
    int numBuckets;
    
public:
    ourMap()
    {
        count = 0;
        numBuckets = 5;
        bucket = new MapNode<V>*[numBuckets];
        for(int i = 0; i < numBuckets; i++)
        {
            bucket[i] = NULL;
        }
    }
    
    ~ourMap()
    {
        for(int i = 0; i < numBuckets; i++)
        {
            delete bucket[i];
        }
        delete []bucket;
    }
    
private:
    
    //Hashcode function
    int getHashCode(string key)
    {
        int currentCoeff = 1;
        int hashCode = 0;
        for(int i = key.length() - 1; i >= 0; i--)
        {
            hashCode += key[i]*currentCoeff;
            currentCoeff *= 17; //prime number
            hashCode %= numBuckets;
            currentCoeff %= numBuckets;
        }
        return hashCode%numBuckets;
    }
    
    
    //rehash
    void rehash()
    {
        MapNode<V> ** temp = bucket;
        bucket = new MapNode<V>[2*numBuckets];
        for (int i = 0; i < 2*numBuckets; i++) {
            bucket[i] = NULL;
        }
        int oldBucketCount = numBuckets;
        numBuckets *= 2;
        count = 0;
        for (int i = 0; i < oldBucketCount; i++) {
            MapNode<V> * head = temp[i];
            while (head != NULL) {
                insertKey(head -> key, head -> value);
                head = head -> next;
            }
        }
        for (int i = 0; i < oldBucketCount; i++) {
            delete temp[i];
        }
        
        delete []temp;
    }
    
public:
    
    double getLoadFactor()
    {
        return (1.0*count)/numBuckets;
    }
    
    //return size
    int size()
    {
        return count;
    }
    
    //insertion.
    void insertKey(string key, V value)
    {
        int bucketIndex = getHashCode(key);
        MapNode<V> * head = bucket[bucketIndex];
        while(head != NULL)
        {
            if(head -> key == key)
            {
                head -> value = value;
                return;
            }
            head = head -> next;
        }
        head = bucket[bucketIndex];
        MapNode<V> * newNode = new MapNode<V>(key, value);
        newNode -> next = head;
        bucket[bucketIndex] = newNode;
        count++;
        double loadfactor = (1.0*count)/numBuckets;
        if(loadfactor > 0.7)
        {
            rehash();
        }
    }
    
    //delete the given key and return the value
    V deleteKey(string key)
    {
        int bucketIndex = getHashCode(key);
        MapNode<V> * head = bucket[bucketIndex];
        MapNode<V> * prev = NULL;
        while(head != NULL)
        {
            if(head -> key == key)
            {
                if(prev == NULL)
                {
                    bucket[bucketIndex] = head -> next;
                }
                else
                {
                    prev -> next = head -> next;
                }
                V value = head -> value;
                head -> next = NULL;
                delete head;
                count--;
                return value;
            }
            prev = head;
            head = head -> next;
        }
        return 0; // signifying that there is no key
    }
    
    //search
    V getValue(string key)
    {
        int bucketIndex = getHashCode(key);
        MapNode<V> * head = bucket[bucketIndex];
        
        while(head != NULL)
        {
            if(head -> key == key)
            {
                return head -> value;
            }
            head = head -> next;
        }
        return 0;
    }
    
};

int main()
{
    
    return 0;
}

