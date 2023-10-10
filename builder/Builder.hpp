/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-10 11:09:27
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-10 11:46:26
 */
#include <iostream>

#define DEFAULT_ROOF "default roof"
#define DEFAULT_WALL "default wall"
#define DEFAULT_FLOOR "default floor"

class House {
private:
  std::string roof_;
  std::string wall_;
  std::string floor_;
  House() {}
  void setRoof(std::string roof) { roof_ = roof;}
  void setWall(std::string wall) { wall_ = wall;}
  void setFloor(std::string floor) { floor_ = floor;}
public:
  void print()  {
    std::cout << "roof : " << roof_ << std::endl;
    std::cout << "wall : " << wall_ << std::endl;
    std::cout << "floor : " << floor_ << std::endl;
  }
  class Builder {
  private:
    std::string roof_;
    std::string wall_;
    std::string floor_;
  public:
    Builder() {}
    ~Builder() {}
    void setRoof(std::string roof) { roof_ = roof; }
    void setWall(std::string wall) { wall_ = wall; }
    void setFloor(std::string floor) { floor_ = floor; }
    House* build() {
      if (roof_.empty()) {
        roof_ = DEFAULT_ROOF;
      }
      if (wall_.empty()) {
        wall_ = DEFAULT_WALL;
      }
      if (floor_.empty()) {
        floor_ = DEFAULT_FLOOR;
      }
      House *house_ = new House();
      house_->setRoof(roof_);
      house_->setWall(wall_);
      house_->setFloor(floor_);
      return house_;
    }
  };
};