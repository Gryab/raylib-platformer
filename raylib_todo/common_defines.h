#ifndef common_defines
#define common_defines
  
  #define s8 signed char
  #define u8 unsigned char
  #define s16 signed short
  #define u16 unsigned short
  #define s32 signed int
  #define u32 unsigned int
  #define s64 signed long long int
  #define u64 unsigned long long int

  #define r32 float
  #define r64 double

  typedef struct s_string{
    u64 size;
    char* value;
  }s_string;

  typedef struct s_byte_array{
    u64 size;
    u8* value;
  }s_byte_array;

#endif
