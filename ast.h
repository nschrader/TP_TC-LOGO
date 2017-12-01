#ifndef AST_H
#define AST_H

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
   Instruction instruction;
 } Program;

 Program* newProgram(Program* right, Instruction instruction);


/**
 * AtomicInstruction and stuff
 */
typedef enum {
  LEFT, RIGHT, FORWARD
} AtomicInstructionType;

typedef struct {
  InstructionType type;
  AtomicInstructionType atomicType;
  int value;
} AtomicInstruction;

#define isAtomicInstruction(x) (x->type == ATOMIC)
#define asAtomicInstruction(x) (isAtomicInstruction(x) ? (AtomicInstruction*) : NULL)

AtomicInstruction* newAtomicInstruction(AtomicInstructionType atomicType, int value);


/**
 * RepeatInstruction and stuff
 */
 typedef struct {
   InstructionType type;
   int value;
   Program* program;
 } RepeatInstruction;

#define isRepeatInstruction(x) (x->type == REPEAT)
#define asRepeatInstruction(x) (isRepeatInstruction(x) ? (RepeatInstruction*) : NULL)

RepeatInstruction* newRepeatInstruction(int value, Program* program);

#endif
