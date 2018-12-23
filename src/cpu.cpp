#include "cpu.h"

CPU::CPU() {
    this->clock = new Clock();
    this->init();
}

CPU::CPU(float frequency) {
    this->clock = new Clock(frequency);
    this->init();
}

// Constructor specific to the clock implementation on the electronic model
CPU::CPU(float Ra, float Rb, float C) {
    this->clock = new Clock(Ra, Rb, C);
    this->init();
}

CPU::~CPU() {
    delete(this->clock);
    this->clock = 0;
    delete(this->regA);
    this->regA = 0;
    delete(this->regB);
    this->regB = 0;
    delete(this->memAddrReg);
    this->memAddrReg = 0;
    delete(this->instrReg);
    this->instrReg = 0;
    delete(this->ram);
    this->ram = 0;
    delete(this->progCntr);
    this->progCntr = 0;
    delete(this->microCntr);
    this->microCntr = 0;
}

void CPU::init() {
    this->regA = new Register();
    this->regB = new Register();
    this->memAddrReg = new Register();
    this->instrReg = new Register();
    this->ram = new RAM(16);
    this->progCntr = new Counter(0xff);
    this->microCntr = new Counter(0x5);
    
    this->init_control_logic();
}

/*
    Specifies the microinstructions associated with each instructions

    'controlLogic' is the equivalent of an EEPROM where the index of the array is the address passed to the chip.
    
    Inside is stored the control word for the X instruction at the Y step.
    The address of the control word is an 8-bit word where the four most significant bits are the X instruction
    and the three least significant bits are the Y step.
    
    For instance, 'this->controlLogic[0x1 << 3 | 2]' is the control word for the 2nd step of the instruction 0x1.
*/
void CPU::init_control_logic() {
    // Each instruction starts with a fetch
    for(int i = 0; i < 16; i++) {
        this->controlLogic[i << 3] = CO | MI;
        this->controlLogic[(i << 3) | 1] = RO | II | CE;
    }

    //hlt
    this->controlLogic[(0x0 << 3) | 2] = HLT;

    //lda
    this->controlLogic[(0x1 << 3) | 2] = IO | MI;
    this->controlLogic[(0x1 << 3) | 3] = RO | AI;

    //sta
    this->controlLogic[(0x2 << 3) | 2] = IO | MI;
    this->controlLogic[(0x2 << 3) | 3] = AO | RI;
   
    //add
    this->controlLogic[(0x3 << 3) | 2] = IO | MI;
    this->controlLogic[(0x3 << 3) | 3] = RO | BI;
    this->controlLogic[(0x3 << 3) | 4] = SO | AI;
}

void CPU::run() {
    unsigned char bus = 0;

    // Gets the control word from the controlLogic array initialized above
    // The index is the address in the EEPROM, where the four most significant bits are the instruction and the three least significant bits are the microinstruction step
    int controlWord = 
            controlLogic[((this->instrReg->get() >> 4) << 3) | this->microCntr->get()];
    print_content(bus, controlWord);

    while(!this->clock->isHalted()){
        this->clock->waitForPulse();

        if((controlWord & HLT) == HLT) {
            this->clock->halt();
        } if((controlWord & RO) == RO) {
            bus = this->ram->get(this->memAddrReg->get());
        } if((controlWord & IO) == IO) {
            // Puts the content of the four least significant bits of the instruction register (the parameter of the instruction) onto the bus
            bus = (this->instrReg->get() & 0xf);
        } if((controlWord & BO) == BO) {
            bus = this->regB->get();
        } if((controlWord & SUB) == SUB) {
            bus = this->regA->get() - this->regB->get();
        } if((controlWord & SO) == SO) {
            bus = this->regA->get() + this->regB->get();
        } if((controlWord & AO) == AO) {
            bus = this->regA->get();
        } if((controlWord & CO) == CO) {
            bus = this->progCntr->get();
        } if((controlWord & RI) == RI) {
            this->ram->set(this->memAddrReg->get(), bus);
        } if((controlWord & MI) == MI) {
            this->memAddrReg->set(bus);
        } if((controlWord & II) == II) {
            this->instrReg->set(bus);
        } if((controlWord & BI) == BI) {
            this->regB->set(bus);
        } if((controlWord & AI) == AI) {
            this->regA->set(bus);
        } if((controlWord & CI) == CI) {
            this->progCntr->set(bus);
        } if((controlWord & CE) == CE) {
            this->progCntr->enable();
        }

        this->microCntr->enable();
        // Gets the next control word before updating the view for better understanding
        controlWord = 
            controlLogic[((this->instrReg->get() >> 4) << 3) | this->microCntr->get()];
        print_content(bus, controlWord);
    }
}

/*
    Prints the state of the CPU
*/
void CPU::print_content(unsigned char bus, int controlWord) {
  system("clear");

  print_ram(this->ram);
  
  print_bus(bus);
  print_pc(this->progCntr->get());
  print_rega(this->regA->get());
  print_ram(this->ram->get(this->memAddrReg->get()));
  
  if((controlWord & SUB) == SUB) {
    print_sub(this->regA->get() - this->regB->get());
  }else {
    print_sum(this->regA->get() + this->regB->get());
  }
  
  print_memaddr(this->memAddrReg->get());
  print_regb(this->regB->get());
  print_instr(this->instrReg->get());
  print_ctrlw(controlWord);
  
  print_micrcntr(this->microCntr->get());
  print_micro_instructions(controlWord);
}

/*
    Loads a program in memory
*/
void CPU::load(unsigned char program[], int size) {
    this->ram->clear();
    for(int i = 0; i < size; i++) {
        this->ram->set(i, program[i]);
    }
}