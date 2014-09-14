
#include "SOrderProgramPrinter.h"
#include "../../../SFunctions.h"
string toHex(uint32_t hex, uint32_t pad){
    stringstream out;
    out<< std::showbase // show the 0x prefix
       << std::internal // fill between the prefix and the number
       << std::setfill('0'); // fill with 0s
    out << std::hex<< std::uppercase << std::setw(pad) << hex;
    return out.str();
}
string tabPad(string topad, uint32_t len){
    stringstream tab;
    tab<<"";

	for(; len - topad.size() > 1; len-=1)
        tab<<" ";
    return tab.str();
}
void printProgram(ofstream& out, PROGRAM& p){
    uint32_t line = 0;
    out<<"no instruction ="<<p.size()<<endl;
    out<<"line\topcode\t\t\targ\t"<<endl;
    for (line = 0 ; line < p.size(); ){
        uint32_t instruction = p.at(line);
        string name ="";
        bool haveArg = false;
        uint32_t noParams = 0;
        string param[5] = "";
        bool lineAddr[5] = {false};
        switch((instruction & 0xFFFF0000)){
            case inst::pushN:
            {
                name = "pushN";
                haveArg = true;
                break;
            }
			case inst::pushS0N:
            {
                name = "pushS0N";
                haveArg = true;
                break;
            }
            case inst::pushN_1:
            {
                name = "pushN_1";
                haveArg = true;
                noParams = 1;
                param[0] = "value";
                break;
            }
            case inst::popN:
            {
                name = "popN";
                haveArg = true;
                break;
            }
            case inst::cpN_FT2:
            {
                name = "cpN_FT2";
                haveArg = true;
                noParams = 2;
                param[0] = "Rel dest"; 
                param[1] = "Rel src"; 
                break;
            }
			case inst::jmpA_1:
            {
                name = "jmpA_1";
                haveArg = true;
                noParams = 1;
                param[0] = "PC"; 
				lineAddr[0] = true;
                break;
            }
 			case inst::cjmpA_1:
            {
                name = "cjmpA_1";
                haveArg = true;
                noParams = 1;
                param[0] = "PC";
				lineAddr[0] = true;
                break;
            }
 			case inst::addS01:
            {
                name = "addS01";
                break;
            }
 			case inst::minusS01:
            {
                name = "minusS01";
                break;
            }
 			case inst::addS01dS1:
            {
                name = "addS01dS1";
                break;
            }
 			case inst::minusS01dS1:
            {
                name = "minusS01dS1";
                break;
            }
 			case inst::sysCall:
            {
				haveArg = true;
                name = "sysCall";
				noParams = 1;
                param[0] = "Stack";

                break;
            }
			default:{
				name = "unknown";
						break;
			}

        }
        out<<toHex(line,6)<<"\t"<<toHex(instruction>>16,4)<<" ("<<name<<")";
        if(haveArg)
            out<<"\t"<<toHex(instruction & 0x0000FFFF,4);
        out<<endl;
        for(int i = 0 ; i < noParams; i++){

            out<<toHex(line+i+1,6)<<"\t\t  "<<"\t("<<param[i]<<")"<<tabPad(param[i], 14)<<toHex(p.at(line+i+1),lineAddr[i]? 6 :  10)<<endl;
        }
        
        
        line+= 1 + noParams;           
    }
    out<<endl;
}



