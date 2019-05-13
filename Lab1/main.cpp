// Lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include <string.h>

#define defaultN 30

class StringBuffer
{
private:
    int dimension;
    int	used;
    char* buffer;

public:
    StringBuffer() //costruttore generico
    {
        this->dimension = defaultN;
        this->used = 0;
        this->buffer = new char[defaultN + 1];
        this->buffer[20] = '\0';
    }

    ~StringBuffer(void) //distruttore
    {
        delete[] this->buffer;
        this->dimension = 0;
        this->used = 0;
    }

    StringBuffer(const char* str) //costruttore da stringa
    {
        this->dimension = strlen(str) + 1;
        this->used = this->dimension;
        this->buffer = new char[this->dimension + 1];
        memcpy(this->buffer, str, this->dimension);
        this->buffer[this->dimension] = '\0';
    }

    StringBuffer(const StringBuffer& sb) //costruttore di copia
    {
        this->dimension = sb.dimension;
        this->used = sb.used;
        this->buffer = new char[this->dimension + 1];
        memcpy(this->buffer, sb.buffer, this->dimension);
        this->buffer[this->dimension] = '\0';
    }

    StringBuffer& operator= (const StringBuffer& sb)//operatore =
    {
        this->dimension = sb.dimension;
        this->used = sb.used;
        delete[] this->buffer;
        this->buffer = new char[this->dimension];
        memcpy(this->buffer, sb.buffer, this->dimension);
    }

    size_t size()//getter
    {
        return this->used;
    }

    size_t capacity()//getter
    {
        return this->dimension;
    }

    void clear()
    {
        this->used = 0;
    }

    void insert(const char* str, size_t pos)
    {
        int i;

        if (pos + (int) strlen(str) < this->dimension)
        {
            if (pos <= (int) this->used)
            {
                for (i = 0; i < strlen(str); i++)
                    this->buffer[pos + i] = str[i];
            }
            else
            {
                for (i = 0; this->used + i == pos; i++)
                    this->buffer[used + i] = 32;
                for (i = 0; i < strlen(str); i++)
                    this->buffer[pos + i] = str[i];
            }
        }
        else
        {
            char* temp = new char[this->dimension + strlen(str)];
            memcpy(temp, this->buffer, this->dimension);
            delete[] this->buffer;
            this->buffer = temp;
            delete[] temp;
            for (i = 0; i < strlen(str); i++)
                this->buffer[pos + i] = str[i];
        }
    }

    char* getBuffer()
    {
        return this->buffer;
    }

};

int main()
{
    std::cout << "Hello World!\n";

    StringBuffer buf1 = StringBuffer("ciaomichiamomatteo");
    //buf1.insert("provaaa", 5);
    printf("%s", buf1.getBuffer());




    return(0);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
