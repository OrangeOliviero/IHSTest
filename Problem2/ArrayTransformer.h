#ifndef __ARRAYTRANSFORMER_H__
#define __ARRAYTRANSFORMER_H__

template<typename Type>
void transformArray(Type values[], size_t size, Type(*transform)(Type, Type, const Type*))
{
  if (size <= 1) return;

  // Get our initial state and transform the first value
  Type prevResult = transform(values[1], values[0], nullptr);
  Type prevValue = values[1];
  values[1] = prevResult;

  // Transform the rest of the array
  for (size_t idx = 2; idx < size; ++idx) {
    prevResult = transform(values[idx], prevValue, &prevResult);
    prevValue = values[idx];
    values[idx] = prevResult;
  }
}

template<template<typename...> class Container, typename Type>
void transformArray(Container<Type>& values, Type(*transform)(Type, Type, const Type*))
{
  if (values.empty()) return;

  auto iterator = values.begin();
  auto endIt = values.end();
  Type prevValue = *iterator++;
  if (iterator == endIt) return;

  // Get our initial state and transform the first value
  Type prevResult = transform(*iterator, prevValue, nullptr);
  prevValue = *iterator;
  *iterator++ = prevResult;

  // Transform the rest of the container
  while (iterator != endIt) {
    prevResult = transform(*iterator, prevValue, &prevResult);
    prevValue = *iterator;
    *iterator++ = prevResult;
  }
}

template<typename Type>
Type sumPrev(Type current, Type previous, const Type* prevResult)
{
  if (!prevResult) {
    return current + previous;
  }
  return current + *prevResult;
}

template<typename Type>
Type mulPrev(Type current, Type previous, const Type* prevResult)
{
  if (!prevResult) {
    return current * previous;
  }
  return current * *prevResult;
}

template<typename Type>
Type deltaPrev(Type current, Type previous, const Type* prevResult)
{
  return current - previous;
}

#endif /* __ARRAYTRANSFORMER_H__ */
