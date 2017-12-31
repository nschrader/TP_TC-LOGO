#ifndef AST_H
#define AST_H

#include "main.h"

/**
* Abstract Instruction and stuff
*/
typedef enum {
  ATOMIC, REPEAT
} InstructionType;

typedef InstructionType Instruction;

#define asInstruction(x) ((Instruction*) x)

/**
* Program and stuff
*/
typedef struct _Program {
  struct _Program *right;
  Instruction* instruction;
} Program;

Program* newProgram(Program* right, Instruction* instruction);
void freeProgram(Program* program);


/**
* AtomicInstruction and stuff
*/
typedef enum {
  LEFT, RIGHT, FORWARD
} AtomicInstructionType;

typedef struct {
  InstructionType type;
  AtomicInstructionType atomicType;
  uint value;
} AtomicInstruction;

#define isAtomicInstruction(x) (*x == ATOMIC)
#define asAtomicInstruction(x) (isAtomicInstruction(x) ? (AtomicInstruction*) x : NULL)

AtomicInstruction* newAtomicInstruction(AtomicInstructionType atomicType, uint value);
void freeAtomicInstruction(AtomicInstruction* atomicInstruction);


/**
* RepeatInstruction and stuff
*/
typedef struct {
  InstructionType type;
  uint value;
  Program* program;
} RepeatInstruction;

#define isRepeatInstruction(x) (*x == REPEAT)
#define asRepeatInstruction(x) (isRepeatInstruction(x) ? (RepeatInstruction*) x : NULL)

RepeatInstruction* newRepeatInstruction(uint value, Program* program);
void freeRepeatInstruction(RepeatInstruction* repeatInstruction);

#endif
