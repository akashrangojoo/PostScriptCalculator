/******************************************
 * PROGRAM     :  PROG7.CC "Calculator"
 * AUTHOR      :  AKASH Z1717009
 * SUBMISSION  :  10/21/2015
 * ******************************************/

#include "prog7.h"



/*************************************************
 *  FUNCTION  :  main
 *  INPUTS    :  none
 *  USAGE     :  This is the main method that initializes
 *               the stack and calls the process_token by
 *               passing the token.
 * ***********************************************/

int main() {
   stack<double>  S;
   string token;
   ifstream infile;
//   infile.open(FILE_INPUT.c_str());
   infile.open("PROG7.d2");
   while(true){
      infile>>token;
      if(infile.fail()) break; 
//      cout<<token<<endl;    
      process_token(token,S);
   }
 //  infile.close();
}

/*************************************************
 *  FUNCTION  :  process_token
 *  INPUTS    :  const string& token, stack<double> &s
 *  USAGE     :  This function checks char by char in the token
 and if its a valid number, it converts it into
 double and performs operations accordingly
 ***********************************************/

void process_token(const string& token, stack<double> &s) {

   unsigned length = token.length();
   bool errorFlag;
   bool floatPointFlag; 
   bool unarySignFlag; //checks unary sign
   bool digitFlag;//checks if digit
   bool operFlag=false; // checks if a valid operator
   bool equalFlag= false;// checks if a equal to sign
   bool cancelFlag= false; // checks if "C" is entered
   for(unsigned i=0;i<length;i++) {
   topagain: // go to 
      floatPointFlag = floatPoint(token);
      unarySignFlag= (token[i]=='-'||token[i]=='+')&&(isdigit(token[i+1])||token[i+1]=='.');
      digitFlag= isdigit(token[i]);
      operFlag = isValidOperator(token[i])&& !isdigit(token[i+1]) && token[i+1]!='.';
      equalFlag = token[i]=='=';
      cancelFlag = token[i]== 'c'||token[i]=='C';
      char c = token[i];
      if(c=='!'||c==','||c=='['||c==']'||c=='#'||c=='$'||c=='%'||c=='^'||c==':'||c==';'||c=='?'||c=='&'||c=='_')
      {
         cout<<"error : character '"<<c<<"' is invalid"<<endl;
         for(unsigned u=0;u<s.size();u++) s.pop();
         errorFlag=true;
      }
      if(cancelFlag){
         for(unsigned i=0;i<s.size();i++) s.pop();
      }
      unsigned k=i;
      if((unarySignFlag||digitFlag)&& !floatPointFlag){
         if(unarySignFlag){
            i++;
            while(isdigit(token[i])){
               if(isdigit(token[i+1])) i++;
               else { double temp=getNumber(k,token,i); s.push(temp);break;}
            }
         }
         else if(digitFlag){

            while(isdigit(token[i])){
               if(isdigit(token[i+1])) i++;
               else { double temp=getNumber(k,token,i); s.push(temp);break;}
            }
         }
      }
      int pointcount=0;
      if(unarySignFlag||floatPointFlag){
         if(unarySignFlag){
            i++; 
            while((isdigit(token[i])||token[i]=='.')&& pointcount<2){
               if(pointcount>=2) {cout<<"error : number "<<token.substr(k,i)<<" is invalid"<<endl; errorFlag=true;break;}
               if(token[i]=='.') pointcount++;
               if(isdigit(token[i+1])||token[i+1]=='.') {  i++;}
               else { /*cout<<" i "<<i*/;double temp=getNumber(k,token,i); s.push(temp);break;}
            }
         }
         else if(floatPointFlag){
            //cout<<"Just F"<<endl;
            while(isdigit(token[i])||token[i]=='.'){
               ///cout<<"Just F"<<endl;
               if(pointcount>=2) {cout<<"error : number "<<token.substr(k,i)<<" is invalid"<<endl; errorFlag=true;break;}
               if(token[i]=='.') pointcount++;
               if(isdigit(token[i+1])||token[i+1]=='.') {/*cout<<"after threee"<<endl;*/ i++;}
               else { double temp=getNumber(k,token,i); s.push(temp);break;}
            }
         }
      }

      if(i<token.length()&& !operFlag && !equalFlag){i++;floatPointFlag=false;  goto topagain;}


      if(operFlag && s.size()<2) {cout<<"error : stack is empty"<<endl; errorFlag =true;}
      if(errorFlag) break;
      if(operFlag && s.size()>=2){

         double x=s.top();
         s.pop();

         double y=s.top();
         s.pop();
         double result = operation(token[i],y,x);
         s.push(result);
      }
      if(token[i]=='=')
      {
         if(s.empty()) cout<<"Stack Empty";
         else {
            cout.precision(2);
            cout<<setw(10)<<fixed<<s.top()<<endl;
         }
      }
   }
}

/*************************************************
 *  FUNCTION  :  unarySign
 *  INPUTS    :  const char& c, const string& token, const unsigned& i
 *  USAGE     :  checks if the character is a unary sign or not
 ***********************************************/

bool unarySign(const char& c, const string& token, const unsigned& i) {
   //cout<<"leng "<<token.length()<<endl;
   bool flag=false;
   if((c=='+'||c=='-')&&token.length()>1) {
      if(isdigit(token[i+1])){
         //cout<<token[i+1]<<endl;
         flag=true;
      }
      else flag=false;
   }
   return flag;
}

/*************************************************
 *  FUNCTION  :  isValidOperator
 *  INPUTS    :  const char& c
 *  USAGE     :  Checks if the operator is among
 standard math operators
 ***********************************************/

bool isValidOperator ( const char& c ) {
   if(c=='+'||c=='-'||c=='*'||c=='/') return true;
   else return false;
}

/*************************************************
 *  FUNCTION  :  floatPoint
 *  INPUTS    :  const char& c, const string& token, const unsigned& i
 *  USAGE     :  Tchecks if the token has deciman point and returns true
 ***********************************************/

bool floatPoint(const string& token) {
   int decPos = token.find(".");
   if(decPos == -1) return false;
   else return true;
}

/*************************************************
 *  FUNCTION  :  getNumber
 *  INPUTS    :  unsigned& k, const string& token, unsigned& i, const bool& floatPointFlag
 *  USAGE     :  it extracts the characters between
 *               two indents and returns the double value
 ***********************************************/

double getNumber(unsigned& k, const string& token, unsigned& i){
   string str= token.substr(k,i+1-k);
   //cout<<str<<"K "<<k<<" I "<<i<<endl;
   double temp=stringToDouble(str);
   return temp;
}

/*************************************************
 *  FUNCTION  :  stringToDouble
 *  INPUTS    :  string str
 *  USAGE     :  converts the given string into double value
 ***********************************************/

double stringToDouble(string str) {
   istringstream stream;
   stream.str(str);
   double value;
   stream >> value >> ws;
   if (stream.fail() || !stream.eof()) { cout<<"ERROR"<<endl;
      cout<<"stringToInteger: Illegal double format";
   }
   return value;
}

/*************************************************
 *  FUNCTION  :  operation
 *  INPUTS    :  const char& c, const double&x, const double& y
 *  USAGE     :  It takes two double numbers and an
 *               operator and performs the operation
 ***********************************************/

double operation(const char& c, const double&x, const double& y) {

   switch(c)
   {
      case '+':
         return x+y;
         break;
      case '-':
         return x-y;
         break;
      case '*':
         return x*y;
         break;
      case '/':
         return x/y;
         break;
      default: 
         cout<<"Invlaid Operaator";
         break;
   }
}

