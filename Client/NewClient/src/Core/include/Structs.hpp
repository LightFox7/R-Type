#pragma once

namespace mystructs {
    template<typename T>
    class vector2d {
        public:
            vector2d(T x = 0, T y = 0) : x(x), y(y) {}
            ~vector2d() = default;
            vector2d operator+(vector2d &vec) {
                vector2d res;
                res.x = x + vec.x;
                res.y = y + vec.y;
                return (res);
            };
            vector2d operator-(vector2d &vec) {
                vector2d res;
                res.x = x - vec.x;
                res.y = y - vec.y;
                return (res);
            };
            friend bool operator==(vector2d const &vec1, vector2d const &vec2) {
                if (vec1.x == vec2.x && vec1.y == vec2.y)
                    return (true);
                return (false);
            }
            friend bool operator!=(vector2d const &vec1, vector2d const &vec2) {
                if (vec1.x != vec2.x || vec1.y != vec2.y)
                    return (true);
                return (false);
            }

            T x;
            T y;
    };
};
