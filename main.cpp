#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

// transaction data
struct TransactionData {
    double amount;
    string senderKey;
    string receiverKey;
    time_t timestamp;
}

class Block
{
    private:
    int index;
    size_t blockHash;
    size_t previousHash;
    size_t generateHash();

    public:
    // Constructor
    Block(int idx, TransactionData d, size_t prevHash);

    // Get Original Hash
    size_t getHash();

    // Get Previous Hash
    size_t getPreviousHash();

    // Transaction Data
    TransactionData data;

    // Validate Hash
    bool isHashValid();
};

//Constructor with params
Block::Block(int idx, TransactionData d, size_t prevHash)
{
    index = idx;
    data = d;
    previousHash = prevHash;
    blockHash = generateHash();
}

//private function
size_t Block::generateHash()
{
    hash<string> hash1;
    hash<size_t> hash2;
    hash<size_t> finalHash;
    string toHash = to_string(data.amount) + data.receiverKey + data.senderKey + to_string(data.timestamp);

    return finalHash(hash1(toHash) + hash2(previousHash));
};

// Public function
size_t Block::getHash()
{
    return blockHash;
}

bool Block::isHashValid()
{
    return generateHash() == blockHash;
}

// Blockchain Class
class Blockchain
{
    private:
        Block createGenesisBlock();

    public:
        // Public chain
        vector<Block> chain;

        // Constructor
        Blockchain();

        // Public Function
        void addBlock(TransactionData data);
        bool isChainValid();

        // Contrived Example For Demon only
        Block *getLastestBlock();
};

// blockchain Constructor

Blockchain::Blockchain()
{
    Block genesis = createGenesisBlock();
    chain.push_back(genisis);
}

Block Blockchain::createGenesisBlock()
{
    time_t current;
    d.amount = 0;
    d.receiverKey = "None";
    d.senderKey = "None";
    d.timestamp = time(&current);

    hash<int> hash1;
    Block genesis(0, d, hash1(0));
    return genesis;
}

// Only for Demo!!!
Block *Blockchain::getLastestBlock()
{
    return &chain.back();
}

void Blockchain::addBlock(TransactionData d)
{
    int index = (int)chain.size() - 1;
    Block newBlock(index, d, getLastestBlock()->getHash());
}

bool Blockchain::isChainValid()
{
    vector<Block>::iterator it;
    int chainLen = (int)chain.size();

    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        if (!currentBlock.isHashValid())
        {
            ///invalid
            return false;
        }
        if(chainLen > 1)
        {
            Block previousBlock = *(it - 1);
            if (currentBlock.getPreviousHash() != previousBlock.getHash())
            {
                return false;
            }
        }
    }
}

int main()
{
    //start Blockchain
    Blockchain AwesomCoin;

    //data for first added block
    TransactionData data1;
    time_t data1Time;
    data1.amount = 1.5;
    data1.receiverKey = "joe";
    data1.senderKey = "Sally";
    data1.timestamp = time(&data1Time);

    AwesomCoin.addBlock(data1);

    cout << "Is chain valid?" << endl
         << AwesomCoin.isChainValid() << endl;

     //hacking
    Block *hackBlock = AwesomeCoin.getLatestBlock();
    hackBlock->data.amount = 10000;
    hackBlock->data.receiverKey = "sem";
    cout << "Now, Is chain still valid?" << endl;
    cout << AwesomCoin.isChainValid() << endl;
}