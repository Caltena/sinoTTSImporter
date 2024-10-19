#ifndef COPYFILEVIASSH_H
#define COPYFILEVIASSH_H
#include <iostream>
#include <cstdlib> // for system()
#include <string>
#pragma once

class copyFileViaSSH
{
public:
    copyFileViaSSH();
    ~copyFileViaSSH();
    copyFileViaSSH(const std::string &localFilePath, const std::string &remoteUser,
                   const std::string &remoteHost, const std::string &remoteFilePath);

private:
};

#endif