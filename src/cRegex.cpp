#include <regex>
#include <iostream>
#include <string>

int main(){

  std::cout << std::endl;

  std::string emailText = "A text with  DE0123456789 an email address: rainer@grimm-j<DE0923956789>aud.de."
                          "A text with  DE0123456689 an email address: rainer@grimm-j<DE8123956789>aud.de." 
                          "A text with  DE0123456589 an email address: rainer@grimm-j<DE7123956789>aud.de.";
  std::string regExprStr(R"([A-Z]{2}[A-Z0-9]{9}[0-9])");
  std::regex rgx(regExprStr);

  std::smatch smatch;

 while (std::regex_search(emailText, smatch, rgx)){
    std::cout << "ISIN: " << smatch[0] << std::endl;          // (6)
    emailText = smatch.suffix() ;
  }
  std::cout << std::endl;
}