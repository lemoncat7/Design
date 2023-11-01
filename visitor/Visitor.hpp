/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-11-01 09:28:07
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-11-01 10:08:18
 */
#include <iostream>
#include <memory>
using namespace std;
// 继承重写
class ReaderAbstraction {
  std::string file_path_;
public:
  ReaderAbstraction(std::string file_path) : file_path_(file_path) {}
  virtual void ContentToTxt() = 0;
};
//PDF、PPT、Word
class PDFReader : public ReaderAbstraction {
public:
  PDFReader(std::string file_path) : ReaderAbstraction(file_path) {}
  void ContentToTxt() override { std::cout << "PDF to txt" << std::endl; }
};
class PPTReader : public ReaderAbstraction {
public:
  PPTReader(std::string file_path) : ReaderAbstraction(file_path) {}
  void ContentToTxt() override { std::cout << "PPT to txt" << std::endl; }
};
class WordReader : public ReaderAbstraction {
public:
  WordReader(std::string file_path) : ReaderAbstraction(file_path) {}
  void ContentToTxt() override { std::cout << "Word to txt" << std::endl; }
};
//工厂
class ReaderFactory {
public:
  static std::shared_ptr<ReaderAbstraction> CreateReader(const std::string &type, 
                                                         const std::string &file_path) {
    if (type == "PDF") {
      return std::make_shared<PDFReader>(file_path);
    } else if (type == "PPT") {
      return std::make_shared<PPTReader>(file_path);
    } else if (type == "Word") {
      return std::make_shared<WordReader>(file_path);
    }
    return nullptr;
  }
};

// 访问者模式
class Visitor ; 
class FileAbstraction {
  std::string file_path_;
public:
  FileAbstraction(const std::string &file_path) : file_path_(file_path) {}
  std::string& FilePath() { return file_path_; }
  virtual void Accept(Visitor &visitor) = 0;
};
class PDFFile : public FileAbstraction {
public:
  PDFFile(const std::string &file_path) : FileAbstraction(file_path) {}
  void Accept(Visitor &visitor) override;
};
class PPTFile : public FileAbstraction {
public:
  PPTFile(const std::string &file_path) : FileAbstraction(file_path) {}
  void Accept(Visitor &visitor) override;
};
class WordFile : public FileAbstraction {
public:
  WordFile(const std::string &file_path) : FileAbstraction(file_path) {}
  void Accept(Visitor &visitor) override;
};
class Visitor {
public:
  virtual void VisitPDFFile(PDFFile &file) {};
  virtual void VisitPPTFile(PPTFile &file) {};
  virtual void VisitWordFile(WordFile &file) {};
};
//阅读
class ReaderVisitor : public Visitor {
public:
  void VisitPDFFile(PDFFile &file) override;
  void VisitPPTFile(PPTFile &file) override;
  void VisitWordFile(WordFile &file) override;
};
//压缩
class CompressorVisitor : public Visitor {
public:
  void VisitPDFFile(PDFFile &file) override;
  void VisitPPTFile(PPTFile &file) override;
  void VisitWordFile(WordFile &file) override;
};