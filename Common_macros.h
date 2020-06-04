#ifndef COMMON_MACROS
#define COMMON_MACROS

#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))


#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )


#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

#endif