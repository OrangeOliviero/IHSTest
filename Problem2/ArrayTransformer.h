#ifndef __ARRAYTRANSFORMER_H__
#define __ARRAYTRANSFORMER_H__

template<typename Type>
void transformArray(Type values[], size_t size, Type(*transform)(Type, Type, Type*))
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

template<typename Type>
Type sumPrev(Type current, Type previous, Type* prevResult)
{
  if (!prevResult) {
    return current + previous;
  }
  return current + *prevResult;
}

template<typename Type>
Type mulPrev(Type current, Type previous, Type* prevResult)
{
  if (!prevResult) {
    return current * previous;
  }
  return current * *prevResult;
}

template<typename Type>
Type deltaPrev(Type current, Type previous, Type* prevResult)
{
  return current - previous;
}

#endif /* __ARRAYTRANSFORMER_H__ */
