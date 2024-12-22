#pragma once
#include <iostream>
#include <string>

template <class T> 
class Message
{
    public:
    Message(std::string from, std::string to, T message);
    ~Message();

    std::string getTo() const;
    std::string getFrom() const;
    T getMessage() const;

    void setTo(std::string val);
    void setFrom(std::string val);
    void setMessage(T val);

    private:
    T _message;
    std::string _from;
    std::string _to;

};