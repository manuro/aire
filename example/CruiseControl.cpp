#include <cstdlib>
#include <cstring>
#include <iostream>

namespace State {
enum Machine {
   ON  = 1,  // On
   OFF = 2,  // Off
   SET = 3,  // Set velocity (CRUISE)
   RES = 4,  // Resume velocity (CRUISE)
   INC = 5,  // Increase velocity (CRUISE)
   DEC = 6   // Decrease velocity (CRUISE)
};
}

namespace Signal {
enum Bus {
   ON  = 1,  // On
   OFF = 2,  // Off
   SET = 3,  // Set velocity
   RES = 4,  // Resume velocity
   INC = 5,  // Increase velocity
   DEC = 6,  // Decrease velocity
   BRK = 7,  // Brake
   NOS = 9   // NO signal
};
}

State::Machine state;
State::Machine oldState;

void display() 
{ 
   if(state == State::ON) std::cout << "Display: ON" << std::endl; 
   else std::cout << "Display: CRUISE" << std::endl; 
} 
void startCruise() { }
void stopCruise() { } 
void saveVelocity() { std::cout << "Saved velocity" << std::endl; } 
void exitCruise() { } 
void setVelocity() { }
void resVelocity() { } 
void incVelocity() { } 
void decVelocity() { } 

const char* getStateName()
{
   switch(state)
   {
      case State::ON:  return "ON";  break;
      case State::OFF: return "OFF"; break;
      case State::SET: return "SET"; break;
      case State::RES: return "RES"; break;
      case State::DEC: return "DEC"; break;
      case State::INC: return "INC"; break;
      default: return "UNKNOWN";     break;
   }
   return "UNKOWN";
}

void cruise(Signal::Bus input)
{
   switch(state)
   {
      case State::ON:
         display();
         // Freude am Fahren
         switch(input) {
            case Signal::SET: setVelocity(); state = State::SET; break;
            case Signal::RES: resVelocity(); state = State::RES; break;
            case Signal::OFF: exitCruise();  state = State::OFF; break;
         }
         std::cout << "State is " << getStateName() << std::endl;
         break;
      case State::SET:
         display();
         switch(input) {
            case Signal::INC: incVelocity(); state = State::INC; break;
            case Signal::DEC: decVelocity(); state = State::DEC; break;
            case Signal::OFF: exitCruise();  state = State::OFF; break;
            case Signal::BRK: stopCruise();  state = State::ON;  break;
         }
         if(oldState != state) saveVelocity();
         std::cout << "State is " << getStateName() << std::endl;
         break;
      case State::RES:
         display();
         switch(input) {
            case Signal::SET: setVelocity(); state = State::SET; break;
            case Signal::INC: incVelocity(); state = State::INC; break;
            case Signal::DEC: decVelocity(); state = State::DEC; break;
            case Signal::OFF: exitCruise();  state = State::OFF; break;
            case Signal::BRK: stopCruise();  state = State::ON;  break;
         }
         std::cout << "State is " << getStateName() << std::endl;
         break;
      case State::INC:
         display();
         switch(input) {
            case Signal::SET: setVelocity(); state = State::SET; break;
            case Signal::RES: resVelocity(); state = State::RES; break;
            case Signal::INC: incVelocity(); state = State::INC; break;
            case Signal::DEC: decVelocity(); state = State::DEC; break;
            case Signal::OFF: exitCruise();  state = State::OFF; break;
            case Signal::BRK: stopCruise();  state = State::ON;  break;
         }
         std::cout << "State is " << getStateName() << std::endl;
         break;
      case State::DEC:
         display();
         switch(input) {
            case Signal::SET: setVelocity(); state = State::SET; break;
            case Signal::RES: resVelocity(); state = State::RES; break;
            case Signal::INC: incVelocity(); state = State::INC; break;
            case Signal::DEC: decVelocity(); state = State::DEC; break;
            case Signal::OFF: exitCruise();  state = State::OFF; break;
            case Signal::BRK: stopCruise();  state = State::ON;  break;
         }
         std::cout << "State is " << getStateName() << std::endl;
         break;
      case State::OFF:
         switch(input) {
            case Signal::ON: startCruise(); state = State::ON; break;
         }
         std::cout << "State is " << getStateName() << std::endl;
         break;
   }
   oldState = state;
}


int main(int argc, char* argv[])
{
   state = State::OFF;
   Signal::Bus signal = Signal::OFF;

   std::cout << "Input a signal: on, off, set, res, inc, dec, brk" << std::endl;
   std::cout << "Input signal: esc to exit cruise control" << std::endl;

   while(true)
   {
      std::string input;
      getline(std::cin, input);
      std::cout << "Signal was: " << input << std::endl;
      if(input.find("on") == 0)  signal = Signal::ON;
      else if(input.find("off") == 0) signal = Signal::OFF;
      else if(input.find("dec") == 0) signal = Signal::DEC;
      else if(input.find("inc") == 0) signal = Signal::INC;
      else if(input.find("set") == 0) signal = Signal::SET;
      else if(input.find("res") == 0) signal = Signal::RES;
      else if(input.find("brk") == 0) signal = Signal::BRK;
      else if(input.find("esc") == 0) break;
      else signal = Signal::NOS;
      cruise(signal);
   }
   
   return EXIT_SUCCESS;
}
