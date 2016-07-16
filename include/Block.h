#ifndef BLOCK_H
#define BLOCK_H
#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <string>
#include <vector>
using namespace nana;
using namespace std;
class Block:  public button
{
    public:
        int id;
        string name;
        string getName();
        void setName(string s);
        string getFileName();
        bool isEmpty();
        Block();
        virtual ~Block();
    protected:

    private:
};

#endif // BLOCK_H