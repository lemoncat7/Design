/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-11-01 09:32:35
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-11-01 10:03:43
 */
#include "Visitor.hpp"

int main() {
  ReaderVisitor reader;
  CompressorVisitor compressor;
  PDFFile pdf("a.pdf");
  pdf.Accept(reader);
  pdf.Accept(compressor);
  PPTFile ppt("a.ppt");
  ppt.Accept(reader);
  ppt.Accept(compressor);
  WordFile word("a.doc");
  word.Accept(reader);
  word.Accept(compressor);
  return 0;
}