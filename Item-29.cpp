/**
 * \brief Item 29: Strive for exception safe code.
 * Three levels:
 * 1. Basic Guarantee: In case of exception, program state is VALID.
 * 2. Strong Guarantee: In case of exception, program state is UNCHANGED.
 * 3. No throw Guarantee: In case of exception, nothing is thrown.
*/
#include <iostream>
using namespace std;


/**
 * \brief The following function offers no throw Guarantee.
 * \todo Timeout needs to be added to offer basic or strong guarantee.
*/
std::string runCmd(const std::string cmdStr, int &exitStatus){
    std::string outputStr;
    try{
        FILE *pipeStream = popen(cmdStr.c_str(), "r");
        if(pipeStream == nullptr || ferror(pipeStream)){
            outputStr = "Failed to open command's pipe stream.";
            perror(outputStr.c_str());
            return outputStr;
        }
        else{
            // Copy the output of the command execution from the pipeStream.
            char buffer[1024];
            while(fgets(buffer, sizeof(buffer), pipeStream) != nullptr) {
                outputStr += buffer;
            }        
            
            // Handle exit response
            if(feof(pipeStream)){
                int status = pclose(pipeStream);
                if(WIFEXITED(status)){
                    exitStatus = WEXITSTATUS(status);
                    return outputStr;
                }
                else{
                    outputStr = "Process did not exit normally.";
                    perror(outputStr.c_str());
                    return outputStr;
                }
            }
            else{
                outputStr = "Did not reach end of command pipe's stream. Something went wrong.";
                perror(outputStr.c_str());
                return outputStr;
            }
            
        }
    }
    catch(const exception e){
        outputStr = "Caught exception. Something went wrong.";
        perror(outputStr.c_str());
        return outputStr;
    }
}

int main(){
    int exitStatus;
    std::string cmdOutputStr = runCmd("lxs -alh", exitStatus);
    cout << cmdOutputStr << "\t" << exitStatus << endl;
    return 0;
}