#include <iostream>
#include <fstream>
#include <dirent.h>
#include <experimental/filesystem>
#include <string>
namespace fs = std::experimental::filesystem;
std::experimental::string str;
DIR *directory;           // creating pointer of type dirent
struct dirent *x;         // pointer represent directory stream
bool result = false;

void createfolder(std::string path)
{
    fs::create_directories(path);
}

bool searchingfile(std::string pathtofile, std::string nameoffile)
{
    const char *path = pathtofile.c_str(); // conversion from string to c string for the function opendir
    std::string filename = nameoffile; // declaring string variable
    if ((directory = opendir(path)) != NULL) // check if directory  open
    {
        while ((x = readdir(directory)) != NULL)
        {
            {
                if (filename == x->d_name)
                {
                    result = true; // if file found then  assign  result to true.
                }
            }
        }
        closedir(directory); // close directory....
    }
    return result;
}

std::string listfilesinpwd(std::string pathtofile)
{
    const char *path = pathtofile.c_str(); // conversion from string to c string for the function opendir
    if ((directory = opendir(path)) != NULL) // check if directory  open
    {
        while ((x = readdir(directory)) != NULL)
        {
            {
                str = str + x->d_name + " \n";
            }
        }
        closedir(directory); // close directory....
    }
    return str;
}

void copytolocation(std::string path , std::string targetlocation)
{
    fs::copy(path, targetlocation, fs::copy_options::overwrite_existing);
}

void deletefile(std::string path)
{
    fs::remove_all(path);
}