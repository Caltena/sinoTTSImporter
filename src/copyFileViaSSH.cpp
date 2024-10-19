#include "copyFileViaSSH.h"

/**
 *
 *
 */

/**
 * @brief 
 *
 * @param 
 * @return 
 */
copyFileViaSSH::copyFileViaSSH()
{
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */
copyFileViaSSH::~copyFileViaSSH()
{
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */
copyFileViaSSH::copyFileViaSSH(const std::string &localFilePath, 
                               const std::string &remoteUser,
                               const std::string &remoteHost, 
                               const std::string &remoteFilePath)
{
    // Construct the scp command and Execute the command
    std::string command = "scp " + localFilePath + " " + remoteUser + "@" + remoteHost + ":" + remoteFilePath;
    int result = system(command.c_str());
    // Check the result
    if (result == 0)
        std::cout << "File copied successfully." << std::endl;
    else
        std::cerr << "Error copying file. Exit code: " << result << std::endl;
}