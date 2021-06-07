/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-07 19:29:09
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-07 19:35:34
 */
/*
 举个围棋的例子，围棋的棋盘共有361格，即可放361个棋子。现在要实现一个围棋程序，该怎么办呢？首先要考虑的是棋子棋盘的实现，可以定义一个棋子的类，成员变量包括棋子的颜色、形状、位置等信息，另外再定义一个棋盘的类，成员变量中有个容器，用于存放棋子的对象。下面给出代码表示：

        棋子的定义，当然棋子的属性除了颜色和位置，还有其他的，这里略去。这两个属性足以说明问题。
*/
#include <string>
#include <iostream>
#include <vector>
using namespace std;

/*

//棋子颜色  
enum PieceColor {BLACK, WHITE};  
//棋子位置  
struct PiecePos  
{  
    int x;  
    int y;  
    PiecePos(int a, int b): x(a), y(b) {}  
};  
//棋子定义  
class Piece  
{  
protected:  
    PieceColor m_color; //颜色  
    PiecePos m_pos;     //位置  
public:  
    Piece(PieceColor color, PiecePos pos): m_color(color), m_pos(pos) {}  
    ~Piece() {}  
    virtual void Draw() {}  
};  
class BlackPiece: public Piece  
{  
public:  
    BlackPiece(PieceColor color, PiecePos pos): Piece(color, pos) {}  
    ~BlackPiece() {}  
    void Draw() { cout<<"绘制一颗黑棋"<<endl;}  
};  
class WhitePiece: public Piece  
{  
public:  
    WhitePiece(PieceColor color, PiecePos pos): Piece(color, pos) {}  
    ~WhitePiece() {}  
    void Draw() { cout<<"绘制一颗白棋"<<endl;}  
};  
 
//棋盘的定义：
class PieceBoard  
{  
private:  
    vector<Piece*> m_vecPiece; //棋盘上已有的棋子  
    string m_blackName; //黑方名称  
    string m_whiteName; //白方名称  
public:  
    PieceBoard(string black, string white): m_blackName(black), m_whiteName(white){}  
    ~PieceBoard() { Clear(); }  
    void SetPiece(PieceColor color, PiecePos pos) //一步棋，在棋盘上放一颗棋子  
    {  
        Piece * piece = NULL;  
        if(color == BLACK) //黑方下的  
        {     
            piece = new BlackPiece(color, pos); //获取一颗黑棋  
            cout<<m_blackName<<"在位置("<<pos.x<<','<<pos.y<<")";  
            piece->Draw(); //在棋盘上绘制出棋子  
        }  
        else  
        {     
            piece = new WhitePiece(color, pos);  
            cout<<m_whiteName<<"在位置("<<pos.x<<','<<pos.y<<")";  
            piece->Draw();  
        }  
        m_vecPiece.push_back(piece);  //加入容器中  
    }  
    void Clear() //释放内存  
    {  
        int size = m_vecPiece.size();  
        for(int i = 0; i < size; i++)  
            delete m_vecPiece[i];  
    }  
};  */

// xiang yuan moshi 
// 棋子颜色  
enum PieceColor {BLACK, WHITE};  
//棋子位置  
struct PiecePos  
{  
    int x;  
    int y;  
    PiecePos(int a, int b): x(a), y(b) {}  
};  
//棋子定义  
class Piece  
{  
protected:  
    PieceColor m_color; //颜色  
public:  
    Piece(PieceColor color): m_color(color) {}  
    ~Piece() {}  
    virtual void Draw() {}  
};  
class BlackPiece: public Piece  
{  
public:  
    BlackPiece(PieceColor color): Piece(color) {}  
    ~BlackPiece() {}  
    void Draw() { cout<<"绘制一颗黑棋\n"; }  
};  
class WhitePiece: public Piece  
{  
public:  
    WhitePiece(PieceColor color): Piece(color) {}  
    ~WhitePiece() {}  
    void Draw() { cout<<"绘制一颗白棋\n";}  
};  
 
//相应棋盘的定义为：
class PieceBoard  
{  
private:  
    vector<PiecePos> m_vecPos; //存放棋子的位置  
    Piece *m_blackPiece;       //黑棋棋子   
    Piece *m_whitePiece;       //白棋棋子  
    string m_blackName;  
    string m_whiteName;  
public:  
    PieceBoard(string black, string white): m_blackName(black), m_whiteName(white)  
    {  
        m_blackPiece = NULL;  
        m_whitePiece = NULL;  
    }  
    ~PieceBoard() { delete m_blackPiece; delete m_whitePiece;}  
    void SetPiece(PieceColor color, PiecePos pos)  
    {  
        if(color == BLACK)  
        {  
            if(m_blackPiece == NULL)  //只有一颗黑棋  
                m_blackPiece = new BlackPiece(color);     
            cout<<m_blackName<<"在位置("<<pos.x<<','<<pos.y<<")";  
            m_blackPiece->Draw();  
        }  
        else  
        {  
            if(m_whitePiece == NULL)  
                m_whitePiece = new WhitePiece(color);  
            cout<<m_whiteName<<"在位置("<<pos.x<<','<<pos.y<<")";  
            m_whitePiece->Draw();  
        }  
        m_vecPos.push_back(pos);  
    }  
}; 

int main()
{
    PieceBoard pieceBoard("A","B");  
    pieceBoard.SetPiece(BLACK, PiecePos(4, 4));  
    pieceBoard.SetPiece(WHITE, PiecePos(4, 16));  
    pieceBoard.SetPiece(BLACK, PiecePos(16, 4));  
    pieceBoard.SetPiece(WHITE, PiecePos(16, 16));  
    return 0;
}