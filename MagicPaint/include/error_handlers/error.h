#pragma once
#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include <stdexcept>
#include <string>

using namespace std;

class SourceLocation {
public:
    SourceLocation(const string& file, const string& func, int line)
        : m_file(file)
        , m_func(func)
        , m_line(line)
    {}

    const string& file() const {
        return m_file;
    }

    const string& func() const {
        return m_func;
    }

    int line() const {
        return m_line;
    }

private:
    string m_file;
    string m_func;
    int m_line;
};


class Error : public runtime_error {
public:
    Error(const string& description, const SourceLocation& srcLoc)
        : runtime_error(
            description + "\nin '" + srcLoc.func() + "' at " + srcLoc.file() +
            ":" + to_string(srcLoc.line()))
        , m_description(description)
        , m_srcLoc(srcLoc)
    {}

    const string& description() const {
        return m_description;
    }
    const SourceLocation& sourceLocation() const {
        return m_srcLoc;
    }

private:
    string m_description;
    SourceLocation m_srcLoc;
};

class IntersectingConstraintsError : public Error {
public:
    IntersectingConstraintsError(
        const Edge& e1,
        const Edge& e2,
        const SourceLocation& srcLoc)
        : Error(
            constructErrorMessage(e1, e2),
            srcLoc)
        , m_e1(e1)
        , m_e2(e2)
    {}
    const Edge& e1() const {
        return m_e1;
    }
    const Edge& e2() const {
        return m_e2;
    }

private:
    Edge m_e1, m_e2;

    static string constructErrorMessage(const Edge& e1, const Edge& e2) {
        ostringstream messageStream;
        messageStream << "Intersecting constraint edges detected: ("
            << e1.to_string() << "intersects" << e2.to_string();
        return messageStream.str();
    }
};

#endif // ERROR_H_INCLUDED
