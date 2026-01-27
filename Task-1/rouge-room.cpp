#include <iostream>
#include <string>

class Room {
    private:
        int width;
        int height;
        int x = 0;
        int y = 0;
    public:
        Room(int w, int h)
            : width(w), height(h) {}

        int area() const {
            return height * width;
        }

        void display() const {
            std::cout << "Player at (" << x << ", " << y << ") in room with dimensions "
                      << height << "x" << width << " has area: " << area() << std::endl;
        }

        void move(int dx, int dy) {
            x += dx;
            y += dy;
        }

        void drawRoom() const {
            std::cout << "+";
            for (int i = 0; i < width; ++i) std::cout << "-";
            std::cout << "+" << std::endl;
            for (int i = 0; i < height; ++i) {
                if (i == y) {
                    std::cout << "|";
                    for (int j = 0; j < width; ++j) {
                        if (j == x) {
                            std::cout << "@"; // Player representation
                        } else {
                            std::cout << ".";
                        }
                    }
                    std::cout << "|" << std::endl;
                } else {
                    std::cout << "|";
                    for (int j = 0; j < width; ++j) {
                        std::cout << ".";
                    }
                    std::cout << "|" << std::endl;
                }
            }
            std::cout << "+";
            for (int i = 0; i < width; ++i) std::cout << "-";
            std::cout << "+" << std::endl;
        }
};

int main() {
    Room myRoom(10, 5);
    myRoom.drawRoom();

    myRoom.move(3, 2);
    myRoom.drawRoom();
}