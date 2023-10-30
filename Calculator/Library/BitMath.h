/*
 * BitMath.h
 *
 * Created: 10/24/2023 5:02:04 PM
 *  Author: joo
 */ 


#ifndef BITMATH_H_
#define BITMATH_H_


#define SET_BIT(REG, BIT_NUM)  REG |= (1 << BIT_NUM)

#define CLR_BIT(REG, BIT_NUM)  REG &= ~(1 << BIT_NUM)

#define TOGGLE_BIT(REG, BIT_NUM)  REG ^= (1 << BIT_NUM)

#define GET_BIT(REG, BIT_NUM)  ( REG >> BIT_NUM ) & 1

#define SET_BIT_VALUE(REG, BIT_NUM, VALUE)  REG |= (VALUE << BIT_NUM)


#endif /* BITMATH_H_ */