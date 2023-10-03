#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <ctime>
#include <sstream>
#include <fstream>

namespace Helper
{
    //we are making so that any type of input would be converted to string format
    //so template is used for that process
    template <class T>
    std::string ToString(const T &);

    struct DateTime
    {
        DateTime()
        {
            time_t ms;
            //places the system time into variable ms by passing the address of ms
            time(&ms);

            struct tm *info = localtime(&ms);

            D = info->tm_mday;          //day
            m = info->tm_mon + 1;       //month
            y = 1900 + info->tm_year;   // year
            M = info->tm_min;           //minutes
            H = info->tm_hour;          //hour
            S = info->tm_sec;           //seconds
        }

        DateTime(int D, int m, int y, int M, int H, int S): D(D), m(m), y(y), M(M), H(H), S(S) {}
        DateTime(int D, int m, int y): D(D), m(m), y(y), H(0), M(0), S(0) {}

        DateTime Now() const
        {
            return DateTime();
        }

        int D, m, y, H, M, S;

        std::string GetDateString() const
        {
            return std::string (D < 10 ?  "0" : "") + ToString(D) +
                   std::string (m < 10 ? ".0" : ".") + ToString(m) + "." + ToString(y);
            //returns Date in DD.mm.yyyy format
        }

        std::string GetTimeString(const std::string &sep = ":") const
        {
            return std::string (H < 10 ? "0" : "") + ToString(H) + sep +
                   std::string (M < 10 ? "0" : "") + ToString(M) + sep +
                   std::string (S < 10 ? "0" : "") + ToString(S);
            //returns Time in HH:MM:SS format
        }

        std::string GetDateTimeString (const std::string &sep = ":") const
        {
            return GetDateString() + "" + GetTimeString(sep);
        }

    };
    //converts different types to string
    template <class T>
    std::string ToString(const T &e)
    {
        std::ostringstream s;
        s << e;
        return s.str();
    }

    //writes to the log
    void WriteAppLog(const std::string &s)
    {
        std::ofstream file("AppLog.txt", std::ios::app);
        file << "[" << Helper::DateTime().GetDateTimeString() << "]" <<
        "\n" << s << std::endl << "\n";

        file.close();
    }
}
#endif // HELPER_H

