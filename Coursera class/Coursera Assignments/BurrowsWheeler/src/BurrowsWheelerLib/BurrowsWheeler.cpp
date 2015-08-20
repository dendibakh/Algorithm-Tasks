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
    MoveToFront::encodedResult encodedStr = MoveToFront().encode(bwTransform.getTransformedStr());
    BurrowsWheeler::compressedResult compressed = HuffmanAlgorithm().getCompressedResult(encodedStr);
    
    std::vector<bool> originalStringRow = getBinaryRepresentation(bwTransform.getOriginalStringRow());
    compressed.insert(compressed.begin(), originalStringRow.begin(), originalStringRow.end());
    return compressed;
}

std::string BurrowsWheeler::decode(const compressedResult& compressedText)
{
    size_t OriginalStringRow = getValue(compressedText.begin(), compressedText.begin() + 8 * sizeof(size_t));
    BurrowsWheeler::compressedResult compressedArray = BurrowsWheeler::compressedResult(compressedText.begin() + 8 * sizeof(size_t), compressedText.end());
    
    std::string expanded = HuffmanAlgorithm().getExpandedResult(compressedArray);
    std::string decoded = MoveToFront().decode(expanded);
    BurrowsWheelerDecode bwDecode(OriginalStringRow, decoded);
    return bwDecode.getOriginalString();
}
