#pragma once
#include <string>
#include <vector>

class RwayTrie
{
   struct Node
   {
      int value;
      Node* nodes;
	  Node();
   };
   void insert(Node* node, const std::string& key, size_t index, int value);
   bool remove(Node* node, const std::string& key, size_t index);
   bool exist(Node* node, const std::string& key, size_t index);
   int getValue(Node* node, const std::string& key, size_t index);
   size_t height(Node* node);
   void clear(Node*& node);

   typedef std::vector<std::string> TrieRows;
   void getLeftTraversal(Node* node, TrieRows& rows, size_t level);
public:
   static const int radix = 256; // static_cast<int>(std::pow(2, 8 * sizeof(char))); // amount of possible values
   RwayTrie();
   ~RwayTrie();
   void insert(const std::string& key, int value);
   int getValue(const std::string& key);
   bool exist(const std::string& key);
   void remove(const std::string& key);
   std::string getLeftTraversal();
   size_t height();
   void clear();
private:
   Node* root;
};