#include "Message.h"

template <class T>
Message<T>::Message(std::string from, std::string to, T message) : _from(from), _to(to), _message(message) {}

template <class T>
Message<T>::~Message(){}

template <class T>
std::string Message<T>::getTo() const { return _to; }
template <class T>
std::string Message<T>::getFrom() const { return _from; }
template <class T>
T Message<T>::getMessage() const { return _message; }

template <class T>
void Message<T>::setTo (std::string val) { _to = val; }
template <class T>
void Message<T>::setFrom (std::string val) { _from = val; }
template <class T>
void Message<T>::setMessage (T val) { _message = val; }
