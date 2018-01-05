/**
 * @file
 * Pseudo object-oriented representation of an abstract syntax tree.
 * @ref Program is standalone.
 * @ref Instruction, @ref RepeatInstruction and @ref AtomicInstruction offer
 * heritage, macros for type checking and casting are provided. For evey object,
 * the first field is always an @ref InstructionType, so even when casted to
 * another @ref Instruction child you can still determine its real class.
 */

#ifndef AST_H
#define AST_H

#include "main.h"

/**
 * @enum InstructionType
 * Basic type system for @ref Instruction objects
 *
 * @var InstructionType::ATOMIC
 * Type for @ref AtomicInstruction class
 * @var InstructionType::REPEAT
 * Type for @ref RepeatInstruction class
 */
typedef enum {
  ATOMIC, REPEAT
} InstructionType;

 /**
 * Abstract Instruction class
 */
typedef InstructionType Instruction;


/**
 * Macro for type conversion. No type check is done!
 *
 * @returns
 * The given object as @ref Instruction object
 */
#define asInstruction(x) ((Instruction*) x)

/**
 * @struct Program
 * Representation of a program as a series of instructions
 *
 * @var Program::right
 * Pointer to the next "line" of Program
 * @var Program::instruction
 * The instruction associatd with this "line"
 */
typedef struct _Program {
  struct _Program *right;
  Instruction* instruction;
} Program;

/**
 * Constructor for @ref Program
 *
 * @param right
 * Field to be set
 * @param instruction
 * Field to be set
 *
 * @returns
 * A new object
 */
Program* newProgram(Program* right, Instruction* instruction);

/**
 * Destructor for @ref Program.
 * All attached @ref Program objects are also destructed
 *
 * @param program
 * Object to be freed
 */
void freeProgram(Program* program);

/**
* @enum AtomicInstructionType
* Subtype system for @ref AtomicInstruction objects
*
* @var AtomicInstructionType::LEFT
* Type for LEFT instructions
* @var AtomicInstructionType::RIGHT
* Type for RIGHT instructions
* @var AtomicInstructionType::FORWARD
* Type for FORWARD instructions
*/
typedef enum {
  LEFT, RIGHT, FORWARD
} AtomicInstructionType;

/**
 * @struct AtomicInstruction
 * Representation of a LEFT, RIGHT or FORWARD instruction
 *
 * @var AtomicInstruction::type
 * Identification in basic type system, should always be
 * @ref InstructionType::ATOMIC
 * @var AtomicInstruction::atomicType
 * Identification in subtype system
 * @var AtomicInstruction::value
 * Associated Value for instruction
 */
typedef struct {
  InstructionType type;
  AtomicInstructionType atomicType;
  uint value;
} AtomicInstruction;

/**
 * Macro for type check.
 *
 * @returns
 * true if the given object is an @ref AtomicInstruction, otherwise false
 */
#define isAtomicInstruction(x) (*x == ATOMIC)

/**
 * Macro for type conversion.
 *
 * @returns
 * The given object as @ref AtomicInstruction object if possible, otherwise NULL
 */
#define asAtomicInstruction(x) (isAtomicInstruction(x) ? (AtomicInstruction*) x : NULL)

/**
 * Constructor for @ref AtomicInstruction
 *
 * @param atomicType
 * Subtype to be set
 * @param value
 * Field to be set
 *
 * @returns
 * A new object
 */
AtomicInstruction* newAtomicInstruction(AtomicInstructionType atomicType, uint value);

/**
 * Destructor for @ref AtomicInstruction
 *
 * @param atomicInstruction
 * Object to be freed
 */
void freeAtomicInstruction(AtomicInstruction* atomicInstruction);


/**
 * @struct RepeatInstruction
 * Representation of a REPEAT instruction
 *
 * @var RepeatInstruction::type
 * Identification in basic type system, should always be
 * @ref InstructionType::REPEAT
 * @var RepeatInstruction::value
 * Associated Value for repetitions
 * @var RepeatInstruction::program
 * Associated program to be repeated
 */
typedef struct {
  InstructionType type;
  uint value;
  Program* program;
} RepeatInstruction;

/**
 * Macro for type check.
 *
 * @returns
 * true if the given object is an @ref RepeatInstruction, otherwise false
 */
#define isRepeatInstruction(x) (*x == REPEAT)

/**
 * Macro for type conversion.
 *
 * @returns
 * The given object as @ref RepeatInstruction object if possible, otherwise NULL
 */
#define asRepeatInstruction(x) (isRepeatInstruction(x) ? (RepeatInstruction*) x : NULL)

/**
 * Constructor for @ref RepeatInstruction
 *
 * @param value
 * Field to be set
 * @param program
 * Field to be set
 *
 * @returns
 * A new object
 */
RepeatInstruction* newRepeatInstruction(uint value, Program* program);

/**
 * Destructor for @ref RepeatInstruction.
 * The associatd @ref Program will also be freed
 *
 * @param repeatInstruction
 * Object to be freed
 */
void freeRepeatInstruction(RepeatInstruction* repeatInstruction);

#endif
