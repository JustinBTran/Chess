#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "AI.h"


bool white = true;
bool black = false;

sf::Color ResetTileColor(int y, int x) {
    if ((y + x) % 2 == 0) {
        return sf::Color::White;
    }
    else {
        return  sf::Color(0x80, 0x80, 0x80);
    }
}

void SetSpriteTextures(GameState gameState,sf::Sprite sprites[8][8], int boardSize, sf::Texture textures[12] ) {
    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            Piece* piece = gameState.board[row][col];
            if (piece != nullptr) {
                if (piece->id == 0) {
                    if (piece->color == true) {
                        sprites[row][col].setTexture(textures[6]);
                    }
                    else {
                        sprites[row][col].setTexture(textures[0]);
                    }
                }
                else if (piece->id == 1) {
                    if (piece->color == true) {
                        sprites[row][col].setTexture(textures[7]);
                    }
                    else {
                        sprites[row][col].setTexture(textures[1]);
                    }
                }
                else if (piece->id == 2) {
                    if (piece->color == true) {
                        sprites[row][col].setTexture(textures[8]);
                    }
                    else {
                        sprites[row][col].setTexture(textures[2]);
                    }
                }
                else if (piece->id == 3) {
                    if (piece->color == true) {
                        sprites[row][col].setTexture(textures[9]);
                    }
                    else {
                        sprites[row][col].setTexture(textures[3]);
                    }
                }
                else if (piece->id == 4) {
                    if (piece->color == true) {
                        sprites[row][col].setTexture(textures[10]);
                    }
                    else {
                        sprites[row][col].setTexture(textures[4]);
                    }
                }
                else if (piece->id == 5) {
                    if (piece->color == true) {
                        sprites[row][col].setTexture(textures[11]);
                    }
                    else {
                        sprites[row][col].setTexture(textures[5]);
                    }
                }
            }
            else {

            }
        }
    }
}

void Win(sf::RenderWindow& window, bool player, bool stalemate) {
    float gridSize = 180.f;
    sf::Text text;
    sf::Font font;
    font.loadFromFile("Dosis-Light.ttf");
    text.setFont(font); 
    text.setString("Hello world");

    // set the character size
    text.setCharacterSize(150); // in pixels, not points!
    text.setPosition(gridSize*2.5, gridSize*4);

    // set the color
    text.setFillColor(sf::Color::Magenta);
    if (stalemate) {
        text.setString("DRAW");
    }
    else if (player == white) {
        text.setString("White Win!!!");
    }
    else {
        text.setString("Black Win!!!");
    }
    window.draw(text);
}

int main()
{
   
    //Init backend
    GameState gameState = GameState();
    Rook* whiteRookA = new Rook(white);
    Rook* whiteRookB = new Rook(white);
    Rook* blackRookA = new Rook(black);
    Rook* blackRookB = new Rook(black);
    Pawn* whitePawnA = new Pawn(white);
    Pawn* whitePawnB = new Pawn(white);
    Pawn* whitePawnC = new Pawn(white);
    Pawn* whitePawnD = new Pawn(white);
    Pawn* whitePawnE = new Pawn(white);
    Pawn* whitePawnG = new Pawn(white);
    Pawn* whitePawnF = new Pawn(white);
    Pawn* whitePawnH = new Pawn(white);
    Pawn* blackPawnA = new Pawn(black);
    Pawn* blackPawnB = new Pawn(black);
    Pawn* blackPawnC = new Pawn(black);
    Pawn* blackPawnD = new Pawn(black);
    Pawn* blackPawnE = new Pawn(black);
    Pawn* blackPawnF = new Pawn(black);
    Pawn* blackPawnG = new Pawn(black);
    Pawn* blackPawnH = new Pawn(black);
    Knight* whiteKnightA = new Knight(white);
    Knight* whiteKnightB = new Knight(white);
    Knight* blackKnightA = new Knight(black);
    Knight* blackKnightB = new Knight(black);
    Bishop* whiteBishopA = new Bishop(white);
    Bishop* whiteBishopB = new Bishop(white);
    Bishop* blackBishopA = new Bishop(black);
    Bishop* blackBishopB = new Bishop(black);
    Queen* whiteQueen = new Queen(white);
    Queen* blackQueen = new Queen(black);
    King* whiteKing = new King(white);
    King* blackKing = new King(black);

    /*Piece* board[8][8] = { {blackRookA,nullptr,nullptr,nullptr,blackKing,nullptr,nullptr,nullptr},
                        {blackPawnA,whitePawnB,blackPawnC,blackPawnD,blackPawnE,blackPawnF,nullptr,nullptr},
                        {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
                        {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
                        {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr ,nullptr,nullptr},
                        {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
                        {whitePawnA,nullptr,whitePawnC,whitePawnD,whitePawnE,whitePawnF,whitePawnG,whitePawnH},
                        {whiteRookA,whiteKnightA,whiteBishopA,whiteQueen,whiteKing,whiteBishopB,whiteKnightB,whiteRookB},
    };
    */

    Piece* board[8][8] = { {blackRookA,blackKnightA,blackBishopA,blackQueen,blackKing,blackBishopB,blackKnightB,blackRookB},
                        {blackPawnA,blackPawnB,blackPawnC,blackPawnD,blackPawnE,blackPawnF,blackPawnG,blackPawnH},
                        {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
                        {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
                        {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr ,nullptr,nullptr},
                        {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
                        {whitePawnA,whitePawnB,whitePawnC,whitePawnD,whitePawnE,whitePawnF,whitePawnG,whitePawnH},
                        {whiteRookA,whiteKnightA,whiteBishopA,whiteQueen,whiteKing,whiteBishopB,whiteKnightB,whiteRookB},
    };
    gameState.SetBoard(board);
    gameState.SetBlackKingPos(0, 4);
    gameState.SetWhiteKingPos(7, 4);
    //bool game = true;



    float gridSize = 180.f;
    const sf::Color Gray(0x80, 0x80, 0x80);
    float spriteSize = 0.37f;
    const int boardSize = 8;
    sf::Vector2i mousePosScreen = sf::Mouse::getPosition();
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;

    //Init window
    sf::RenderWindow window(sf::VideoMode(gridSize * 8, gridSize * 8), "Chess", sf::Style::Titlebar | sf::Style::Close);

    //Init textures
    sf::Texture b_pawn;
    b_pawn.loadFromFile("images/b-pawn.png");
    sf::Texture b_rook;
    b_rook.loadFromFile("images/b-rook.png");
    sf::Texture b_knight;
    b_knight.loadFromFile("images/b-knight.png");
    sf::Texture b_bishop;
    b_bishop.loadFromFile("images/b-bishop.png");
    sf::Texture b_queen;
    b_queen.loadFromFile("images/b-queen.png");
    sf::Texture b_king;
    b_king.loadFromFile("images/b-king.png");
    sf::Texture w_pawn;
    w_pawn.loadFromFile("images/w-pawn.png");
    sf::Texture w_rook;
    w_rook.loadFromFile("images/w-rook.png");
    sf::Texture w_knight;
    w_knight.loadFromFile("images/w-knight.png");
    sf::Texture w_bishop;
    w_bishop.loadFromFile("images/w-bishop.png");
    sf::Texture w_queen;
    w_queen.loadFromFile("images/w-queen.png");
    sf::Texture w_king;
    w_king.loadFromFile("images/w-king.png");
    sf::Texture dot;
    dot.loadFromFile("images/green-dot");

    sf::Texture textures[12] = { b_pawn,b_rook,b_knight,b_bishop,b_queen,b_king,w_pawn, w_rook, w_knight,w_bishop,w_queen,w_king };

    //Init sprites
    sf::Sprite sprites[boardSize][boardSize];

    for (int y = 0; y < boardSize; y++) {
        for (int x = 0; x < boardSize; x++) {
            sprites[y][x].scale(spriteSize, spriteSize);
            sprites[y][x].setPosition(gridSize * x, gridSize * y);
        }
    }

    sf::RectangleShape tileMap[boardSize][boardSize];
    for (int x = 0; x < boardSize; x++) {
        for (int y = 0; y < boardSize; y++) {
            tileMap[x][y].setSize(sf::Vector2f(gridSize, gridSize));
            if ((y + x) % 2 == 0) {
                tileMap[x][y].setFillColor(sf::Color::White);

            }
            else {
                tileMap[x][y].setFillColor(Gray);
            }
            tileMap[x][y].setOutlineThickness(2.4);
            tileMap[x][y].setOutlineColor(sf::Color::Black);
            tileMap[x][y].setPosition(x * gridSize, y * gridSize);
        }
    }

    sf::RectangleShape tileSelector(sf::Vector2f(gridSize, gridSize));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(3.f);
    tileSelector.setOutlineColor(sf::Color::Green);

    bool game = true;
    bool player = white; //for now player can only play as white
    
    sf::Color playerColor = sf::Color::White;
    sf::Vector2i select(-1, -1);
    bool didMove = false;
    //variables for AIMove
    array<int, 3> data;
    int y_newAI;
    int x_newAI;
    int y_oldAI;
    int x_oldAI;
    sf::Vector2i oppOld(-1,-1);
    sf::Vector2i oppNew(-1, -1);
    bool rescan = false;
    
    gameState.ScanBoard(player);
    TranspositionTable table = TranspositionTable();
    table.initTable();
    unsigned int kobristKey = table.getKobristKey(gameState);
    array<int, 2> blackPiece;
    array<int, 2> whitePiece;

    while (window.isOpen()) {
        //Update mouse positions
        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(window);
        //window.setView(view);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        if (mousePosView.x >= 0.f)
            mousePosGrid.x = mousePosView.x / gridSize;
        if (mousePosView.y >= 0.f)
            mousePosGrid.y = mousePosView.y / gridSize;
        window.setView(window.getDefaultView());

        //Update game elemenents
        tileSelector.setPosition(mousePosGrid.x * gridSize, mousePosGrid.y * gridSize);


        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == sf::Event::Closed)
                window.close();
            if (evnt.type == sf::Event::MouseButtonPressed) {
                if (oppOld.x != -1) { //recolor incase it got overwritten
                    tileMap[oppOld.x][oppOld.y].setFillColor(sf::Color::Red);
                    tileMap[oppNew.x][oppNew.y].setFillColor(sf::Color::Red);
                }
                if (select.x != -1) { // check if a piece is already selected
                    vector<array<int, 2>>moves = gameState.board[select.y][select.x]->moves;
                    if (std::find(moves.begin(), moves.end(), std::array<int, 2>{ (int)mousePosGrid.y, (int)mousePosGrid.x }) != moves.end()) {
                        //printf("move");
                        kobristKey = table.updateKobristKey(gameState, kobristKey, select.y, select.x, mousePosGrid.y, mousePosGrid.x);
                        gameState.whiteMove(gameState, select.y, select.x, mousePosGrid.y, mousePosGrid.x);
                        didMove = true;
                        rescan = true;
                        //recolor red tiles
                        if (oppOld.x != -1) {
                            tileMap[oppOld.x][oppOld.y].setFillColor(ResetTileColor(oppOld.y,oppOld.x));
                            tileMap[oppNew.x][oppNew.y].setFillColor(ResetTileColor(oppNew.y, oppNew.x));
                        }

                    }
                    tileMap[select.x][select.y].setFillColor(ResetTileColor(select.y, select.x));
                    for (array<int, 2> move : moves) {
                        tileMap[move[1]][move[0]].setFillColor(ResetTileColor(move[1], move[0]));
                    }
                    select.x = -1;
                    select.y = -1;

                }
              

                if (gameState.board[mousePosGrid.y][mousePosGrid.x] != nullptr && gameState.board[mousePosGrid.y][mousePosGrid.x]->color == player && didMove == false) {
                    select.x = mousePosGrid.x;
                    select.y = mousePosGrid.y;
                    //sprites[select.y][select.x].setColor(sf::Color::Green);
                    tileMap[select.x][select.y].setFillColor(sf::Color::Green); // selected piece has a green tile
                    //show where the piece can move
                    for (array<int, 2> move : gameState.board[select.y][select.x]->getMoves(gameState, select.y, select.x)) {
                        //sprites[move[0]][move[1]].setTexture(dot);
                        tileMap[move[1]][move[0]].setFillColor(sf::Color::Blue);
                        

                    }
                }


            }
        }

        //clear before rendering
        window.clear();
        //draw board
        for (int x = 0; x < boardSize; x++) {
            for (int y = 0; y < boardSize; y++) {
                window.draw(tileMap[x][y]);
                //window.draw(sprites[x][y]);
            }
        }
        //Update sprites for changes in position
        SetSpriteTextures(gameState,sprites,boardSize,textures);

        //draw sprites
        for (int x = 0; x < boardSize; x++) {
            for (int y = 0; y < boardSize; y++) {
                Piece* piece = gameState.board[x][y];
                if (piece != nullptr) {
                    window.draw(sprites[x][y]);
                }
            }
        }
        //Check for win/loss
        if (rescan) {
            kobristKey = table.updateKobristEnpassant(gameState.board, kobristKey, player);
            gameState.ScanBoard(player);
            rescan = false;
            if (gameState.blackMoveableUnits.size() == 0 && gameState.whiteMoveableUnits.size() == 0) {
                Win(window, white, true);
                game = false;
            }
            else if (gameState.blackMoveableUnits.size() == 1 && gameState.whiteMoveableUnits.size() == 1){
                blackPiece = gameState.blackMoveableUnits[0];
                whitePiece = gameState.whiteMoveableUnits[0];
                if (gameState.board[blackPiece[0]][blackPiece[1]]->id == 5 && gameState.board[whitePiece[0]][whitePiece[1]]->id == 5) {

                }

            }
            else if (gameState.blackMoveableUnits.size() == 0) {
                Win(window, white, false);
                game = false;
            }
            else if (gameState.whiteMoveableUnits.size() == 0) {
                Win(window, black, false);
                game = false;
            }
        }

        window.draw(tileSelector);
        //render
        window.display();
        if (game == false) {
            //loop until player closes the game
            while (true) {
                sf::Event end;
                while (window.pollEvent(end))
                {
                    if (end.type == sf::Event::Closed) {
                        window.close();
                    }
                    else
                        if (end.type == sf::Event::KeyPressed)
                            window.close();
                        else if (end.type == sf::Event::MouseButtonPressed) {
                            window.close();
                        }

                }
            }
            break;
        }

        if (didMove) {
            int depth = 4;
            kobristKey = table.updateKobristEnpassant(gameState.board, kobristKey, !player);
            gameState.ScanBoard(!player);
            if ((gameState.whiteMoveableUnits.size() + gameState.blackMoveableUnits.size()) < 12) {
                data = minimax(gameState, depth, -9999, 9999, !player, kobristKey, table);
            }
            else {
                data = minimax(gameState, depth, -9999, 9999, !player, kobristKey, table);
            }
            if (data[1] != -1) {
                y_newAI = data[1] / 10;
                x_newAI = data[1] % 10;
                y_oldAI = data[2] / 10;
                x_oldAI = data[2] % 10;
                kobristKey = table.updateKobristKey(gameState, kobristKey, y_oldAI, x_oldAI, y_newAI, x_newAI);

                AIMove(gameState, y_oldAI, x_oldAI, y_newAI, x_newAI);
                didMove = false;
                oppNew.x = x_newAI;
                oppNew.y = y_newAI;
                oppOld.y = y_oldAI;
                oppOld.x = x_oldAI;
                tileMap[oppOld.x][oppOld.y].setFillColor(sf::Color::Red);
                tileMap[oppNew.x][oppNew.y].setFillColor(sf::Color::Red);
                
            }
            rescan = true;
        }
       

    }



    return 0;
}