# Doom-Script Language Specification v0.1

## 1. Language Identity

Doom-Script is a C-like programming language inspired by the atmosphere and terminology of DOOM (1993) by id Software. It maintains the expressive power of a general-purpose language while adopting the lexicon of the UAC, Phobos, Deimos, and Hell.

**File Extension:** `.ds`  
**Design Philosophy:** Pragmatic C-inspired syntax with DOOM-themed vocabulary

## 2. Terminology Mapping

| DOOM Concept | Programming Concept | Notes |
|--------------|---------------------|-------|
| Map | Module/Namespace | A compilation unit containing actors and functions |
| Actor | Object/Class | An entity with state and behavior |
| Imp/Pinky/Demon | Instance/Object | An instance of an actor |
| Weapon | Function/Method | Tools of destruction (operations) |
| Ammo (Bullets/Shells/Rockets/Cells) | Function Parameters/Arguments | Fuel for weapons |
| Health/Armor | Variables/State | Vitality of entities |
| Keycard/Skull Key | Access Control/Permissions | Gates access to sealed areas |
| Sector | Scope/Block | A region with boundaries |
| Door/Barrier | Conditional/Guard | Blocks passage until conditions met |
| Switch | Trigger/Event | Activates when used |
| Teleporter | Function Call/Goto | Warps execution flow |
| Exit/End Level | Program Termination | Completes execution |
| Hell | Runtime/Execution Environment | Where the code runs |
| UAC | Standard Library/System Interface | Corporate provider of utilities |
| Cyberdemon/Spider Mastermind | Critical/Error Conditions | Powerful threats requiring attention |
| Pain Elemental | Exception/Recovery | Painful but recoverable situations |
| Barrel/Explosive | Dangerous Operations | Operations that may cause harm |
| Inventory | Collections/Containers | Storage for items |

## 3. Lexical Elements

### Keywords (DOOM-themed)

```
// Module/Import
map, import, from, export

// Types
slayer, imp, cyberdemon, cacodemon, archvile  // integer types (sizes)
hellfire, bfg9000                              // floating point types
soulsphere, megasphere                        // boolean
chainsaw, fist                                 // strings/characters
bruiser, revenant                             // arrays/structs

// Declarations
spawn, arsenal                                // variable/constant declaration
loadout                                       // function definition
avatar                                        // struct definition
plasma                                        // enum definition

// Control Flow
frag, gib                                     // if/else
wave, patrol, hunt                            // loops (for/while/do)
berserk, rage                                 // switch/case
eject, respawn                                // return/break/continue

// Memory/Scope
sector, chamber                               // blocks/scopes
hell, purgatory                               // global/local scope modifiers

// Access
redcard, bluecard, yellowcard, skullkey      // public/private/protected
```

### Operators

```
// Arithmetic
+, -, *, /, %, **

// Comparison
==, !=, <, >, <=, >=

// Logical
&&, ||, !

// Assignment
=, +=, -=, *=, /=, %=

// Bitwise
&, |, ^, <<, >>, ~

// Member/Pointer
., ->
```

### Literals

```
// Integers (decimal, hex with 0x, octal with 0o, binary with 0b)
100, 0xFF, 0o77, 0b1010

// Floats
3.14, 1.5e10

// Strings
"HELLO FROM HELL"
chainsaw "text"

// Booleans
soulsphere true
soulsphere false

// Characters
'f'
```

### Comments

```
// Single line comment - like a bullet
/* Multi-line comment 
   for longer hellfire */
```

## 4. Type System

### Primitive Types
- `slayer` - 32-bit signed integer (the Slayer's might)
- `imp` - 16-bit signed integer  
- `cyberdemon` - 64-bit signed integer
- `cacodemon` - 8-bit signed integer
- `archvile` - unsigned 32-bit integer
- `hellfire` - 32-bit float
- `bfg9000` - 64-bit double
- `soulsphere` - boolean (true/false)
- `chainsaw` - string type
- `fist` - character type
- `void` - `gib` or `none` for void returns

### Compound Types
- `bruiser[]` - arrays
- `revenant` - structs
- `plasma` - enums

### Type Modifiers
- `berserk` - const/immutable
- `corrupted` - volatile (use sparingly)
- `blessed` - static

## 5. Basic Syntax Examples

### Hello World
```doom
map helloworld import uac;

loadout main() -> gib {
    uac.printf("HELLO FROM HELLKERNEL\n");
    eject 0;
}
```

### Variables and Functions
```doom
map combat import uac;

berserk slayer MAX_HEALTH = 100;

loadout damage(slayer hp, slayer amount) -> slayer {
    hp -= amount;
    frag (hp < 0) {
        hp = 0;
    }
    eject hp;
}

loadout main() -> gib {
    slayer health = 100;
    health = damage(health, 25);
    uac.printf("Health: %d\n", health);
    eject 0;
}
```

### Control Flow
```doom
loadout check_ammo(slayer ammo) -> gib {
    frag (ammo <= 0) {
        uac.printf("OUT OF AMMO!\n");
    } gib {
        frag (ammo < 10) {
            uac.printf("LOW AMMO!\n");
        } gib {
            uac.printf("AMMO OK\n");
        }
    }
}
```

### Loops
```doom
loadout count_kills() -> gib {
    patrol slayer i = 0; i < 10; i++ {
        uac.printf("Kill %d\n", i);
    }
    
    slayer demons = 0;
    wave (demons < 5) {
        demons++;
    }
}
```

### Structs
```doom
revenant Player {
    slayer health;
    slayer armor;
    chainsaw name;
};

loadout spawn_player(chainsaw name) -> Player {
    Player p;
    p.health = 100;
    p.armor = 0;
    p.name = name;
    eject p;
}
```

### Enums
```doom
plasma WeaponType {
    FIST = 0,
    PISTOL = 1,
    SHOTGUN = 2,
    CHAINGUN = 3,
    ROCKET = 4,
    PLASMA = 5,
    BFG = 6
};
```

## 6. Module System

```doom
// In file: monsters.ds
map monsters;

loadout spawn_imp() -> gib {
    uac.printf("An imp appears!\n");
}

// In file: main.ds  
map main import monsters, uac;

loadout main() -> gib {
    monsters.spawn_imp();
    eject 0;
}
```

## 7. Standard Library (UAC)

The UAC (Union Aerospace Corporation) provides standard functions:

### I/O
- `uac.printf(format, ...)` - Formatted output
- `uac.scanf(format, ...)` - Formatted input
- `uac.puts(str)` - String output
- `uac.getchar()` - Character input

### Strings
- `uac.strlen(str)` - String length
- `uac.strcpy(dest, src)` - String copy
- `uac.strcat(dest, src)` - String concatenation
- `uac.strcmp(s1, s2)` - String comparison

### Memory
- `uac.malloc(size)` - Allocate memory
- `uac.free(ptr)` - Free memory
- `uac.memcpy(dest, src, size)` - Memory copy

### File I/O
- `uac.fopen(filename, mode)` - Open file
- `uac.fclose(file)` - Close file
- `uac.fread(...)` - Read file
- `uac.fwrite(...)` - Write file

### Conversions
- `uac.atoi(str)` - String to integer
- `uac.itoa(num, str)` - Integer to string

## 8. Semantic Rules

1. **Scoping:** Variables declared in `sector {}` blocks are local. `hell` scope is global to the map.
2. **Type Checking:** Strict type checking with implicit conversions only where safe (int to float).
3. **Functions:** Must be declared before use or forward declared.
4. **Arrays:** Zero-indexed, bounds checked in debug mode.
5. **Strings:** Null-terminated, mutable via `chainsaw`.
6. **Recursion:** Allowed with stack considerations.
7. **Main Entry:** Programs must have `loadout main() -> gib` or `loadout main() -> slayer`.
8. **Imports:** Circular imports are detected and reported as errors.

## 9. Error Messages

Doom-Script uses thematic error messages:

- Syntax Error: `"RIP AND TEAR - Syntax error at line %d, column %d: %s"`
- Type Error: `"NOT ENOUGH AMMO - Type mismatch at line %d, column %d: %s"`
- Undefined Variable: `"MONSTER NOT FOUND - '%s' undefined at line %d, column %d"`
- Division by Zero: `"BARREL EXPLOSION - Division by zero at runtime line %d"`
- Stack Overflow: `"CYBERDEMON RAMPAGE - Stack overflow detected"`

## 10. Execution Model

Doom-Script uses a **C code generation backend** for maximum portability and integration potential with HellKernel. The compiler generates C code from `.ds` source, compiles it with the system C compiler, and links against the Doom-Script runtime library.

This approach provides:
- Easy debugging with standard tools
- Excellent portability
- Simple interoperability with C
- Foundation for future native backend
- Compatible with OS kernel development

Alternative backends were considered (LLVM, custom VM) but C codegen offers the best balance for this project's goals.
