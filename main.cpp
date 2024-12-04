#include <iostream>
#include <vector>
#include <list>
#include <string>

class MyDictionary {
private:
    static const int TABLE_SIZE = 10;
    std::vector<std::list<std::pair<std::string, std::string>>> table;

    int hashFunction(const std::string& key) const {
        int hash = 0;
        for (char ch : key) {
            hash += ch;
        }
        return hash % TABLE_SIZE;
    }

public:
    MyDictionary() : table(TABLE_SIZE) {}

    void insert(const std::string& key, const std::string& value) {
        int index = hashFunction(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
    }

    std::string search(const std::string& key) const {
        int index = hashFunction(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return "Not found";
    }

    void remove(const std::string& key) {
        int index = hashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                return;
            }
        }
        std::cout << "Key \"" << key << "\" not found in the dictionary." << std::endl;
    }
};

int main() {
    MyDictionary dict;

    dict.insert("apple", "fruit");
    dict.insert("banana", "fruit");
    dict.insert("carrot", "vegetable");
    dict.insert("date", "fruit");

    std::cout << dict.search("banana") << std::endl;
    std::cout << dict.search("carrot") << std::endl;
    std::cout << dict.search("date") << std::endl;

    dict.insert("carrot", "root vegetable");
    std::cout << dict.search("carrot") << std::endl;

    dict.remove("apple");
    std::cout << dict.search("apple") << std::endl;

    dict.remove("orange");

    std::cout << dict.search("orange") << std::endl;

    dict.insert("eggplant", "vegetable");
    dict.insert("fig", "fruit");
    dict.insert("grape", "fruit");

    std::cout << dict.search("grape") << std::endl;

    return 0;
}
