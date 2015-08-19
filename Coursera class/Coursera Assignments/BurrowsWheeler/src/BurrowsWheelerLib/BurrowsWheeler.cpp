#include "BurrowsWheeler.h"
#include "BurrowsWheelerTransform.h"
#include "MoveToFront.h"
#include "utils.h"

BurrowsWheeler::BurrowsWheeler()
{

}

BurrowsWheeler::~BurrowsWheeler()
{

}

BurrowsWheeler::compressedResult BurrowsWheeler::encode(const std::string& text)
{
    BurrowsWheelerTransform bwTransform(text);
    MoveToFront moveToFront;
    MoveToFront::encodedResult encodedStr = moveToFront.encode(bwTransform.getTransformedStr());
    HuffmanAlgorithm huffman;
    BurrowsWheeler::compressedResult compressed = huffman.getCompressedResult(encodedStr);
    size_t OriginalStringRow = bwTransform.getOriginalStringRow();
    BurrowsWheeler::compressedResult stringRow;
    unsigned short bytes = sizeof(OriginalStringRow);
    for (size_t i = 0; i < bytes; ++i)
    {
        char* c = (char*)&OriginalStringRow + i;
        std::vector<bool> binRep = getBinaryRepresentation(*c);
        stringRow.insert(stringRow.end(), binRep.begin(), binRep.end());
    }
    compressed.insert(compressed.end(), stringRow.begin(), stringRow.end());
    return compressed;
}

std::string BurrowsWheeler::decode(const compressedResult& compressedText)
{
    size_t OriginalStringRow = 0u;
    unsigned short bytes = sizeof(OriginalStringRow);
    for (size_t i = 0; i < bytes; ++i)
    {
        char* c = (char*)&OriginalStringRow + i;
        *c = getSymbol(compressedText.begin() + 8 * i, compressedText.begin() + 8 * (i + 1));
    }
    BurrowsWheeler::compressedResult compressedArray = BurrowsWheeler::compressedResult(compressedText.begin() + 8 * (bytes), compressedText.end());
    HuffmanAlgorithm huffman;
    std::string expanded = huffman.getExpandedResult(compressedArray);
    MoveToFront moveToFront;
    std::string decoded = moveToFront.decode(expanded);
    BurrowsWheelerDecode bwDecode(OriginalStringRow, decoded);
    return bwDecode.getOriginalString();
}
