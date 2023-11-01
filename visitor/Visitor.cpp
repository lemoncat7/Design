/*
 * @Description:
 * @version:
 * @Author: 莫邪
 * @Date: 2023-11-01 09:51:08
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-11-01 10:13:26
 */
#include "Visitor.hpp"

void PDFFile::Accept(Visitor &visitor) {
  visitor.VisitPDFFile(*this);
}
void PPTFile::Accept(Visitor &visitor) {
  visitor.VisitPPTFile(*this);
}
void WordFile::Accept(Visitor &visitor) {
  visitor.VisitWordFile(*this);
}

// 阅读
void ReaderVisitor::VisitPDFFile(PDFFile &file) {
  std::cout << file.FilePath() << "阅读PDF文件" << std::endl;
}
void ReaderVisitor::VisitPPTFile(PPTFile &file) {
  std::cout << file.FilePath() << "阅读PPT文件" << std::endl;
}
void ReaderVisitor::VisitWordFile(WordFile &file) {
  std::cout << file.FilePath() << "阅读Word文件" << std::endl;
}
// 压缩

void CompressorVisitor::VisitPDFFile(PDFFile &file) {
  std::cout << file.FilePath() << "压缩PDF文件" << std::endl;
}
void CompressorVisitor::VisitPPTFile(PPTFile &file) {
  std::cout << file.FilePath() << "压缩PPT文件" << std::endl;
}
void CompressorVisitor::VisitWordFile(WordFile &file) {
  std::cout << file.FilePath() << "压缩Word文件" << std::endl;
}