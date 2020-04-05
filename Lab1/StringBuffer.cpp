#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "StringBuffer.h"

#define defaultN 30

StringBuffer::StringBuffer() //costruttore generico
{
    this->dimension = defaultN;
    this->used = 0;
    this->buffer = new char[defaultN + 1];
    this->buffer[20] = '\0';
}

StringBuffer::~StringBuffer(void) //distruttore
{
    delete[] this->buffer;
    this->dimension = 0;
    this->used = 0;
}

StringBuffer::StringBuffer(const char* str) //costruttore da stringa
{
    this->dimension = strlen(str) + 1;
    this->used = this->dimension;
    this->buffer = new char[this->dimension + 1];
    memcpy(this->buffer, str, this->dimension);
    this->buffer[this->dimension] = '\0';
}

StringBuffer::StringBuffer(const StringBuffer& sb) //costruttore di copia
{
    this->dimension = sb.dimension;
    this->used = sb.used;
    this->buffer = new char[this->dimension + 1];
    memcpy(this->buffer, sb.buffer, this->dimension);
    this->buffer[this->dimension] = '\0';
}

StringBuffer& StringBuffer::operator= (const StringBuffer& sb)
{
    this->dimension = sb.dimension;
    this->used = sb.used;
    delete[] this->buffer;
    this->buffer = new char[this->dimension];
    memcpy(this->buffer, sb.buffer, this->dimension);
}

size_t StringBuffer::size()//getter
{
    return this->used;
}

size_t StringBuffer::capacity()//getter
{
    return this->dimension;
}

void StringBuffer::clear()
{
    this->used = 0;
}

void StringBuffer::insert(const char* str, size_t pos)
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

void StringBuffer::insert (const StringBuffer& sb , size_t pos ) {
    int i;

    if (pos + (int) strlen(sb.buffer) < this->dimension)
    {
        if (pos <= (int) this->used)
        {
            for (i = 0; i < strlen(sb.buffer); i++)
                this->buffer[pos + i] = sb.buffer[i];
        }
        else
        {
            for (i = 0; this->used + i == pos; i++)
                this->buffer[used + i] = 32;
            for (i = 0; i < strlen(sb.buffer); i++)
                this->buffer[pos + i] = sb.buffer[i];
        }
    }
    else
    {
        char* temp = new char[this->dimension + strlen(sb.buffer)];
        memcpy(temp, this->buffer, this->dimension);
        delete[] this->buffer;
        this->buffer = temp;
        delete[] temp;
        for (i = 0; i < strlen(sb.buffer); i++)
            this->buffer[pos + i] = sb.buffer[i];
    }
}

char* StringBuffer::getBuffer()
{
    return this->buffer;
}

void StringBuffer::append (const char* str ) {
    if(this->dimension + strlen(str) <= this->dimension) {
        for(int i=0;i<strlen(str);i++)
            this->buffer[this->used + i] = str[i];
        this->used += strlen(str);
    }
    else {
        char* temp = new char[this->dimension + strlen(str)];
        memcpy(temp, this->buffer, this->dimension);
        delete[] this->buffer;
        this->buffer = temp;
        delete[] temp;
        for(int i=0;i<strlen(str);i++)
            this->buffer[this->used + i] = str[i];
        this->dimension += strlen(str);
        this->used += strlen(str);
    }
    return;
}

void StringBuffer::append (const StringBuffer& sb ) {
    if(this->dimension + strlen(sb.buffer) <= this->dimension) {
        for(int i=0;i<strlen(sb.buffer);i++)
            this->buffer[this->used + i] = sb.buffer[i];
        this->used += sb.used;
    }
    else {
        char* temp = new char[this->dimension + strlen(sb.buffer)];
        memcpy(temp, this->buffer, this->dimension);
        delete[] this->buffer;
        this->buffer = temp;
        delete[] temp;
        for(int i=0;i<strlen(sb.buffer);i++)
            this->buffer[this->used + i] = sb.buffer[i];
        this->used += sb.used;
        this->dimension += sb.dimension;
    }
    return;
}

const char* StringBuffer::c_str () {
    char * temp = new char[this->dimension + 1];
    strcpy(temp,this->buffer);
    temp[this->dimension] = '\0';
    return temp;
}

void StringBuffer::set (const char* str ) {
    if(strlen(str) <= this->dimension) {
        strcpy(this->buffer,str);
        this->used += strlen(str);
    }
    else {
        delete[] this->buffer;
        this->buffer = new char[strlen(str)];
        strcpy(this->buffer,str);
        this->used = strlen(str);
        this->dimension = strlen(str);
    }
    return;
}

void StringBuffer::set (const StringBuffer& s ) {
    if(this->dimension <= strlen(s.buffer)) {
        for(int i=0;i<strlen(s.buffer);i++)
            this->buffer[this->used + i] = s.buffer[i];
        this->used = s.used;
    }
    else {
        char* temp = new char[strlen(s.buffer)];
        memcpy(temp, this->buffer, this->dimension);
        delete[] this->buffer;
        this->buffer = temp;
        delete[] temp;
        for(int i=0;i<strlen(s.buffer);i++)
            this->buffer[this->used + i] = s.buffer[i];
        this->used += s.used;
        this->dimension += s.dimension;
    }
    return;
}
