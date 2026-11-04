//> Chunks of Bytecode value-c
#include <stdio.h>
//> Strings value-include-string
#include <string.h>
//< Strings value-include-string

//> Strings value-include-object
#include "object.h"
//< Strings value-include-object
#include "memory.h"
#include "value.h"

static uint32_t hashDouble(double val){// gets double to convert to hash value
    union Bitcast{// union has different variables have same memory space
        double val;
        uint32_t integer[2];
    } cast;

    cast.val = val + 1;// change bit pattern before hashing - collision???
    return cast.integer[0] + cast.integer[1];// 32 bit hash  = int[0](32 bits) + int[1](32 bits) - from 64 bit double

}
uint64_t hashValue(Value val){
#ifdef NAN_BOXING
    if(IS_NUMBER(val)){// if key a number, calculate hash value
        double number = AS_NUMBER(val);
        return hashDouble(number);//hashDouble() - function above
    }
    else if (IS_BOOL(val)){
        if(AS_BOOL(val)){
            return 20;// hash value
            }
          else{
            return 30;// hash value
            }
        }
    else if(val == NIL_VAL){
        return 40;//hash value
    }
    else if(IS_STRING(val)){// if a string return string's hash value
        return AS_STRING(val)->hash;

    }
    else if(IS_EMPTY(val)){// if value empty bucket
        return 0;// hash val for empty bucket


    }
    #else
        if (IS_NUMBER(val)) {
            return hashDouble(AS_NUMBER(val));
        }
        else if (IS_BOOL(val)) {
            return AS_BOOL(val) ? 20 : 30;
        }
        else if (IS_NIL(val)) {
            return 40;
        }
        else if (IS_STRING(val)) {
            return AS_STRING(val)->hash;
        }
        else if (IS_EMPTY(val)) {
            return 0;
        }
    #endif
}


void initValueArray(ValueArray* array) {
  array->values = NULL;
  array->capacity = 0;
  array->count = 0;
}
//> write-value-array
void writeValueArray(ValueArray* array, Value value) {
  if (array->capacity < array->count + 1) {
    int oldCapacity = array->capacity;
    array->capacity = GROW_CAPACITY(oldCapacity);
    array->values = GROW_ARRAY(Value, array->values,
                               oldCapacity, array->capacity);
  }
  
  array->values[array->count] = value;
  array->count++;
}
//< write-value-array
//> free-value-array
void freeValueArray(ValueArray* array) {
  FREE_ARRAY(Value, array->values, array->capacity);
  initValueArray(array);
}
//< free-value-array
//> print-value
void printValue(Value value) {
//> Optimization print-value
#ifdef NAN_BOXING
  if (IS_BOOL(value)) {
    printf(AS_BOOL(value) ? "true" : "false");
  } else if (IS_NIL(value)) {
    printf("nil");
  } else if (IS_NUMBER(value)) {
    printf("%g", AS_NUMBER(value));
  } else if (IS_OBJ(value)) {
    printObject(value);
  }
  else if(IS_EMPTY(value)){// if value empty bucket
    printf("empty");
  }
#else
//< Optimization print-value
/* Chunks of Bytecode print-value < Types of Values print-number-value
  printf("%g", value);
*/
/* Types of Values print-number-value < Types of Values print-value
 printf("%g", AS_NUMBER(value));
 */
//> Types of Values print-value
  switch (value.type) {
    case VAL_BOOL:
      printf(AS_BOOL(value) ? "true" : "false");
      break;
    case VAL_NIL: printf("nil"); break;
    case VAL_NUMBER: printf("%g", AS_NUMBER(value)); break;
//> Strings call-print-object
    case VAL_OBJ: printObject(value); break;
    case VAL_EMPTY: printf("empty"); break;// empty
//< Strings call-print-object
  }
//< Types of Values print-value
//> Optimization end-print-value
#endif
//< Optimization end-print-value
}
//< print-value
//> Types of Values values-equal
bool valuesEqual(Value a, Value b) {
//> Optimization values-equal
#ifdef NAN_BOXING
//> nan-equality
  if (IS_NUMBER(a) && IS_NUMBER(b)) {
    return AS_NUMBER(a) == AS_NUMBER(b);
  }
  if(IS_STRING(a) && IS_STRING(b)){
    ObjString* aString = AS_STRING(a);
    ObjString* bString = AS_STRING(b);
    // checks if both strings have the same length and if the characters match
    return aString->length == bString->length && memcmp(aString->Chars, bString->Chars, aString->length) == 0;


  }
//< nan-equality
  return a == b;
#else
//< Optimization values-equal
  if (a.type != b.type) return false;
  switch (a.type) {
    case VAL_BOOL:   return AS_BOOL(a) == AS_BOOL(b);
    case VAL_NIL:    return true;
    case VAL_NUMBER: return AS_NUMBER(a) == AS_NUMBER(b);
    case VAL_EMPTY: return true;// check if type is ValEmpty
/* Strings strings-equal < Hash Tables equal
    case VAL_OBJ: {
      ObjString* aString = AS_STRING(a);
      ObjString* bString = AS_STRING(b);
      return aString->length == bString->length &&
          memcmp(aString->Char, bString->Char,
                 aString->length) == 0;
    }
 */
//> Hash Tables equal
    case VAL_OBJ:    return AS_OBJ(a) == AS_OBJ(b);
//< Hash Tables equal
    default:         return false; // Unreachable.
  }
//> Optimization end-values-equal
#endif
//< Optimization end-values-equal
}
//< Types of Values values-equal
