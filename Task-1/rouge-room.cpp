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
            if (x + dx < 0 || x + dx >= width || y + dy < 0 || y + dy >= height) {
                std::cout << "Move out of bounds!" << std::endl;
                return;
            }
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
    char input;
    bool running = true;

    while (running) {
        myRoom.drawRoom();
        std::cout << "Move (w/a/s/d) or q to quit: ";
        std::cin >> input;

        switch (input) {
            case 'w': myRoom.move(0, -1); break;
            case 's': myRoom.move(0, 1); break;
            case 'a': myRoom.move(-1, 0); break;
            case 'd': myRoom.move(1, 0); break;
            case 'q': running = false; break;
            default: break;
        }
    }
    return 0;
}