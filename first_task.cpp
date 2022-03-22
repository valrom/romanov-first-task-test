#include <cmath>

// Романов В.А.

// Задача 1.
// Есть два манипулятора. Их инструменты находятся в точках О1 и О2 в декартовой системе координат (X, Y).
// У каждого манипулятора есть свой радиус эффективного действия R1 и R2.
//
// Есть точка P1 - точка. Определите, каким манипулятором лучше дойти до точки P1

// Хоть и во второй задаче радиус не учитывается, то в это задаче ничего не сказано.
// Поэтому предполагаю что лучший из двух манипуляторов с наименьшим расстоянием до окружности области действия


// Двумерный вектор
struct Point {
    int x, y;

    Point( int x, int y) : x(x), y(y) {}


    // Расстояние между двумя точками
    static float distance( Point first, Point second ) {
        return sqrt( (first.x - second.x) * (first.x - second.x) +
                     (first.y - second.y) * (first.y - second.y ) );
    }
};





class Manipulator {
private:
    // Координаты центра
    Point _point;
    // Радиус эффективного действия
    uint _r;
public:
    explicit  Manipulator( Point point = Point(0, 0), uint r = 1) : _point(point), _r( r ) {}

    // гетер, а сеттер в данном контексте не нужен
    Point point() { return _point; }

    // расстояние от точки до манипулятора с учетом радиуса действия
    //  output : -r < 0 => Точка внутри радиуса действия
    // output : > r => Точка снаружи радиуса действия
    float req_distance( Point point ) {
        return Point::distance( _point, point) - _r;
    }


    // Определение какой манипулятор лучше подходит для точки
    // output: false => Подходит первый
    // output: true => Подходит второй
    static bool cmp_with_r(Manipulator first, Manipulator second, Point point) {
        if ( first.req_distance(point) > second.req_distance(point)) {
            return true;
        } else {
            return false;
        }
    }
};

// микро unit тесты
void assert( bool eq ) {
    if (!eq) {
        throw std::exception();
    }
}




int main() {
    // проверка distance
    assert( Point::distance(Point(0, 0), Point(3 ,4 )) == 5.0f);

    // проверка Manipulator::req_distance

    auto first = Manipulator(Point(0, 0), 5);
    auto second = Manipulator(Point(0, 0), 4);

    assert(first.req_distance(Point(3 , 4)) == 0.0f);
    assert(second.req_distance(Point(10, 0)) == 6.0f);

    // проверка Manipulator::cmp_with_r

    assert(!Manipulator::cmp_with_r(first, second, Point(10, 0))); // false
    assert(Manipulator::cmp_with_r(first, Manipulator(Point(2, 2), 4), Point(4, 4))); // true

}