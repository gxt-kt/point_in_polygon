#include <iostream>
#include <cmath>
#include <vector>

// 射线法
// https://xoyozo.net/Blog/Details/is-the-point-inside-the-polygon
// 解决点是否在线段上
// https://blog.csdn.net/liangzhaoyang1/article/details/51088475
namespace gPointInPolygon {
template<class A>
class PointInPolygon {
 public:
  struct Point {
    A x;
    A y;
  };
  PointInPolygon() = default;
  ~PointInPolygon() = default;
  std::string IfInPolygon(Point point, std::vector<Point> poly) {
    A px = point.x, py = point.y;
    bool flag = false;
    for (size_t i = 0, l = poly.size(), j = l - 1; i < l; j = i, i++) {
      A sx = poly[i].x,
          sy = poly[i].y,
          tx = poly[j].x,
          ty = poly[j].y;
      // 点与多边形顶点重合
      if ((sx == px && sy == py) || (tx == px && ty == py)) {
        return "on";
      }
      // 判断线段两端点是否在射线两侧
       /*//gxt 原本代码算法有问题，当斜率为0有bug，换成自己的
      if ((sy < py && ty >= py) || (sy >= py && ty < py)) {
        // 线段上与射线 Y 坐标相同的点的 X 坐标
        A x = sx + (py - sy) * (tx - sx) / (ty - sy);
        // 点在多边形的边上
        if (x == px) {
          return "on";
        }
        */

      // 判断线段两端点是否在射线两侧,gxt自己的 begin
      if ((sy <= py && ty >= py) || (sy >= py && ty <= py)) {
      if((px - sx) * (ty - sy) == (tx - sx) * (py - sy)   //叉乘
          && std::min(sx , tx) <= px && px <= std::max(sx , tx)//保证Q点坐标在pi,pj之间
          && std::min(sy , ty) <= py && py <= std::max(sy , ty))
      {
        return "on";
      }
      A x = sx + (py - sy) * (tx - sx) / (ty - sy);
      // 判断线段两端点是否在射线两侧,gxt自己的 end


        // 射线穿过多边形的边界
        if (x > px) {
          flag = !flag;
        }
      }
    }
    // 射线穿过多边形边界的次数为奇数时点在多边形内
    return flag ? "in" : "out";
  }
  bool PointIsLeft(Point point, Point p1, Point p2) {
    return (bool) ((p1.x - point.x) * (p2.y - point.y) - (p2.x - point.x) * (p1.y - point.y));
  }
};
}

using namespace gPointInPolygon;

int main() {
  std::cout << "Hello, World!" << std::endl;
  PointInPolygon<float>::Point test_point{30.0f,50.0f};

  std::vector<PointInPolygon<float>::Point> poly_point = {{-1.0f, -2.0f},
                                                          {0.0f, 10.0f}, {100.0f, 10.0f}, {0.0f, 100.0f}
  };

  PointInPolygon<float> pointInPolygon;
  std::cout << pointInPolygon.IfInPolygon(test_point, poly_point);

  return 0;
}
