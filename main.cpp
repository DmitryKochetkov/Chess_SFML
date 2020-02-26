#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class ChessHandler {
    private:

    bool WhiteToMove = true;

    int posititon[8][8] = {
        5, 4, 3, 2, 1, 3, 4, 5,
        6, 6, 6, 6, 6, 6, 6, 6,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        -6, -6, -6, -6, -6, -6, -6, -6, 
        -5, -4, -3, -2, -1, -3, -4, -5
    };

    // const std::string errors[3] = {
    //     "Success",
    //     "Check",
    //     ""
    // };
    public:

    int getCell(int i, int j) { return posititon[i][j]; }

    // std::string getError(int error_code) {return errors[error_code];}

    // bool move(char* str_move) {
    //     try {
    //         str_move[0]
    //     }
    //     catch 
    // }

    bool move(std::pair<int, int> start, std::pair<int, int> end) {
        //if (CheckToWhite && WhiteToMove && unsafe_move) { return false; }
        return false;
    }
};

int size = 56;
int border = 28;
ChessHandler game;
Sprite board[32];

void loadPosition() {
    int k = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            int piece_id = game.getCell(i, j);
            if (piece_id != 0) {
                int x = abs(piece_id) - 1;
                int y = piece_id > 0 ? 1 : 0;
                board[k].setTextureRect(IntRect(size*x, size*y, size, size));
                board[k].setPosition(size*j + border, size*i + border);
                k++;
            }
        }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "ChessSFML", sf::Style::Titlebar | sf::Style::Close);;
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(Vector2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2));

    Texture t_board_bg;
    t_board_bg.loadFromFile("board.png");

    Texture t_pieces; //TODO: move
    t_pieces.loadFromFile("pieces_resized.png");

    Sprite board_bg(t_board_bg);

    for (int i = 0; i < 32; i++) board[i].setTexture(t_pieces);
    loadPosition();

    float dx = 0, dy = 0;
    bool isMove = false;

    int moved_piece = 0;

    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //drag and drop
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.key.code == Mouse::Left)
                    for (int i = 0; i < 32; i++) {
                        if (board[i].getGlobalBounds().contains(pos.x, pos.y)) {
                            isMove = true; moved_piece = i;
                            dx = pos.x - board[i].getPosition().x;
                            dy = pos.y - board[i].getPosition().y;
                        }
                    }

            if (event.type == Event::MouseButtonReleased)
                if (event.key.code == Mouse::Left)
                {
                    isMove = false;
                    Vector2f p = board[moved_piece].getPosition() + Vector2f(size/2 - border, size/2 - border);
                    Vector2f newPosition = Vector2f(size*int(p.x/size) + border, size*int(p.y/size) + border);
                    board[moved_piece].setPosition(newPosition);
                    std::cout << "Moved piece is " << moved_piece << std::endl;
                    
                    //TODO: update board data
                }

            if (isMove) {
                board[moved_piece].setPosition(pos.x - dx, pos.y - dy);
                
                
            }
            
        }

        window.clear();
        window.draw(board_bg);
        for (int i = 0; i < 32; i++) window.draw(board[i]);
        window.display();
    }

    return 0;
}