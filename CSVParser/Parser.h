#ifndef CSV_CSVPARSER_H
#define CSV_CSVPARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <tuple>
#include <sstream>

#include "ParserExceptions.h"
#include "printTuple.h"
namespace csv
{
    template<typename ... Args>
    class Parser
    {
    private:
        std::ifstream &m_input;
        int m_idx;
        char m_columnDelim;
        char m_lineDelim;
        char m_fieldDelim;

        enum class ParsingState
        {
            READ_FIELD,
            READ_SCREENED_FIELD,
            HANDLE_ANOTHER_SCREENING,
        };

    public:
        class Iterator
        {
        private:
            Parser<Args...> &m_parser;
            std::string m_str;
            std::vector<std::string> m_parsedLine;
            std::vector<int> m_pos;
            int m_idxLine;
            int m_idxColumn = 0;
            bool m_isLast = false;

            void parseLine();

            std::tuple<Args...>vectorIntoTuple()
            {
                m_idxColumn = 0;
                std::tuple<Args...>tup;
                forEach(tup, std::index_sequence_for<Args...>(), m_parsedLine, m_idxColumn, m_idxLine);
                if (m_idxColumn != m_parsedLine.size())
                {
                    throw ParserException("Error: tuple size != line elements", m_idxLine, m_idxColumn);
                }
                return tup;
            }

            template<std::size_t ... I>
            void forEach(std::tuple<Args...> &t, std::index_sequence<I...>, std::vector<std::string> parsedLine, int &currIndex, int &lineNumber)
            {
                ((makeTuple(std::get<I>(t), parsedLine[I], currIndex, lineNumber)), ...);
            }

        public:
            Iterator(Parser &p, int index) : m_parser(p)
            {
                m_idxLine = index;

                int i = 0;
                while (i < m_idxLine && std::getline(m_parser.m_input, m_str, m_parser.m_lineDelim))
                {
                    ++i;
                }
                if (!std::getline(m_parser.m_input, m_str, m_parser.m_lineDelim))
                {
                    throw std::runtime_error("Error: all file was skipped");
                }
            }

            explicit Iterator(Parser &parse, bool isLast) : m_parser(parse)
            {
                m_idxLine = 0;
                m_isLast = isLast;
            }

            Iterator operator++()
            {
                m_idxLine++;
                if (!std::getline(m_parser.m_input, m_str, m_parser.m_lineDelim))
                {
                    m_isLast = true;
                }
                return *this;
            }

            bool operator==(Iterator other)
            {
                return this->m_isLast == other.m_isLast;
            }

            bool operator!=(Iterator other)
            {
                return this->m_isLast != other.m_isLast;
            }

            std::tuple<Args...> operator*() // ленивое чтение: итератор лезет в файл и парсит оттуда строку только когда его попросили
            {
                this->parseLine();
                return this->vectorIntoTuple();
            }
        };

        void setDelimiters(char columnDelim, char lineDelim, char fieldDelim)
        {
            m_columnDelim = columnDelim;
            m_lineDelim = lineDelim;
            m_fieldDelim = fieldDelim;
        }

        Iterator begin()
        {
            return Iterator(*this, m_idx);
        }

        Iterator end()
        {
            return Iterator(*this, true);
        }

        Parser(std::ifstream &file, int index = 0,
               char columnDel = ',',
               char lineDel = '\n',
               char fieldDel = '"')
               : m_input(file)
        {
            if (index < 0) throw std::runtime_error("Error: invalid line number");
            m_idx = index;
            m_columnDelim = columnDel;
            m_lineDelim = lineDel;
            m_fieldDelim = fieldDel;
        }

        template<typename T>
        static void makeTuple(T& t, std::string &str, int &currIndex, int &lineNumber)
        {
            std::istringstream stream(str);
            if ((stream >> t).fail() || !(stream >> std::ws).eof())
            {
                throw ParserException("Error: incorrect field", lineNumber, currIndex);
            };
            currIndex++;
        }

        static void makeTuple(std::string &t, std::string &str, int &currIndex, int &lineNumber)
        {
            t = str;
            currIndex++;
        }
    };

    template<typename... Args>
    void Parser<Args...>::Iterator::parseLine()
    {
        ParsingState state = ParsingState::READ_FIELD;
        m_parsedLine.clear();
        m_parsedLine.emplace_back("");
        m_pos.clear();
        char columnDel = m_parser.m_columnDelim;
        char fieldDel = m_parser.m_fieldDelim;
        size_t indexColumn = 0;
        size_t curPos = 0;
        for (char c : m_str)
        {
            switch (state)
            {
                case ParsingState::READ_FIELD:
                    if (c == columnDel)
                    {
                        m_parsedLine.emplace_back("");
                        m_pos.push_back(curPos);
                        indexColumn++;
                    }
                    else if (c == fieldDel)
                    {
                        state = ParsingState::READ_SCREENED_FIELD;
                    }
                    else {
                        m_parsedLine[indexColumn].push_back(c);
                    }
                    break;
                case ParsingState::READ_SCREENED_FIELD:
                    if (c == fieldDel)
                    {
                        state = ParsingState::HANDLE_ANOTHER_SCREENING;
                    }
                    else {
                        m_parsedLine[indexColumn].push_back(c);
                    }
                    break;
                case ParsingState::HANDLE_ANOTHER_SCREENING:
                    if (c == columnDel)
                    {
                        m_parsedLine.emplace_back("");
                        m_pos.push_back(curPos);
                        indexColumn++;
                        state = ParsingState::READ_FIELD;
                    }
                    else if (c == fieldDel)
                    {
                        m_parsedLine[indexColumn].push_back(fieldDel);
                        state = ParsingState::READ_SCREENED_FIELD;
                    }
                    else
                    {
                        state = ParsingState::READ_FIELD;
                    }
                    break;
                default:
                    break;
            }
            curPos++;
        }
        if (state != ParsingState::READ_FIELD)
        {
            throw ParserException("Error: wrong field", m_idxLine, m_pos.size());
        }

        if (m_pos.size() + 1 != sizeof...(Args))
        {
            throw ParserException("Error: tuple size != line elements", m_idxLine, 0);
        }
    }
}
#endif //CSV_CSVPARSER_H
